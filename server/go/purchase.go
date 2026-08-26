// 결제.
//
// -----------------------------------------------------------------------------
// 지키는 것 하나
// -----------------------------------------------------------------------------
//
// 한 번 산 것은 한 번만 준다.
//
// 나머지는 다 이 한 줄에서 나온다. 왜 이것이 어려운가 하면, 같은 결제가
// 여러 번 도착하는 것이 정상이기 때문이다.
//
//   - 네트워크가 끊기면 클라이언트가 다시 보낸다.
//   - 스토어는 "소비했다"는 응답을 못 받으면 다음 실행에서 또 내놓는다.
//     (Google 의 미소비 구매, Apple 의 미완료 트랜잭션)
//   - 사용자가 앱을 껐다 켜면 대기 장부가 다시 보낸다.
//
// 그래서 "두 번 오면 안 된다" 가 아니라 "두 번 와도 한 번만 준다" 로 만든다.
// 자물쇠는 purchase 표의 uq_order (platform, order_id) 다. 스토어가 준 거래
// 고유값이라 우리가 만들지 않는다.
//
// -----------------------------------------------------------------------------
// 무엇을 줄지는 서버가 정한다
// -----------------------------------------------------------------------------
//
// 클라이언트는 "무엇을 얼마나" 를 안 보낸다. 상품 ID 만 보낸다. 지급량은
// product 표에서 찾는다. 클라이언트가 보낸 수량을 믿으면, 영수증 없이
// "코인 백만 개짜리를 샀다" 고 말하는 것을 막을 방법이 없다.
//
// -----------------------------------------------------------------------------
// 영수증 검증은 아직 자리만 있다
// -----------------------------------------------------------------------------
//
// Verifier 가 그 자리다. 지금 들어 있는 것은 통과시키기만 하는 것이라,
// 스토어를 붙이기 전까지는 이 서버를 밖에 열어두면 안 된다. 실제 검증은
// Apple 의 verifyReceipt / App Store Server API 와 Google 의
// androidpublisher.purchases.products.get 을 붙인다. 붙이는 자리가 한 곳뿐이라
// 그때 이 파일의 아래쪽만 고치면 된다.
package main

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"log"
	"strings"
)

// 지급이 가능한 재화. player 표의 어느 칸에 더할지를 여기서 정한다.
//
// 표 이름을 문자열로 받아 SQL 에 이어붙이면 주입이 된다. 그래서 이름에서
// 칸 이름으로 가는 길을 이 지도 하나로 좁힌다. 여기 없는 것은 못 준다.
var grantColumn = map[string]string{
	"gold":   "gold",
	"heart":  "heart",
	"medal":  "medal",
	"star":   "star",
	"hammer": "hammer",
	"coin":   "coin",
	"inven":  "max_inven",
}

// 패스. 수량이 아니라 날수를 준다.
//
// 남아 있는 동안 또 사면 남은 기간에 이어 붙는다. 그래서 지금 시각이 아니라
// "지금과 남은 시각 중 늦은 쪽" 에서 더한다. 안 그러면 남은 기간이 날아간다.
var grantPass = map[string]string{
	"pass_heart":  "heart_pass_ts",
	"pass_growth": "growth_pass_ts",
}

// 결제 상태.
const (
	purchaseGranted  = "granted"
	purchaseRejected = "rejected"
	purchaseRefunded = "refunded"
)

// Grant 는 지급 한 줄이다.
type GrantLine struct {
	Kind   string
	Amount int64
}

// Product 는 상품 하나다. 지급이 여러 줄일 수 있다 - 스타터팩이 그렇다.
type Product struct {
	ID      string
	Kind    string
	Enabled bool
	Grants  []GrantLine
}

// Once 는 1 인 1 회 상품인가.
func (p Product) Once() bool {
	return p.Kind == "noncon"
}

// PurchaseReq 는 클라이언트가 보낸 것이다.
//
// 지급량이 없는 것에 주목. 그건 서버가 정한다.
type PurchaseReq struct {
	Platform  string
	ProductID string
	OrderID   string
	Receipt   string
}

// PurchaseResult 는 그 결과다.
type PurchaseResult struct {
	State string

	// 무엇을 줬는지 사람이 읽을 수 있게 적은 것. "coin:2000,heart:300"
	Granted string

	Reason string

	// 이미 처리된 거래였는가. 재시도로 다시 온 경우다. 지급은 안 하지만
	// 클라이언트에게는 성공으로 답해야 한다 - 그래야 대기 장부를 지운다.
	Repeat bool
}

var errNoProduct = errors.New("그런 상품이 없다")

// Verifier 는 영수증이 진짜인지 본다.
//
// 스토어마다 방식이 다르지만 묻는 것은 같다 - 이 영수증이 우리 앱의
// 이 상품에 대한 것이 맞는가, 그리고 이 거래 ID 가 맞는가.
type Verifier interface {
	Verify(ctx context.Context, req PurchaseReq) error
}

// verifierAllow 는 다 통과시킨다. 스토어를 붙이기 전의 자리다.
//
// 이것이 켜져 있는 동안에는 아무나 아무 상품이나 받아갈 수 있다. 그래서
// 서버는 이 상태를 로그로 계속 알린다. 조용히 열려 있는 것이 제일 나쁘다.
type verifierAllow struct{}

func (verifierAllow) Verify(ctx context.Context, req PurchaseReq) error {
	return nil
}

// LoadProduct 는 상품과 그 지급 목록을 찾는다. 꺼져 있으면 없는 것으로 본다.
func (s *Store) LoadProduct(ctx context.Context, id string) (Product, error) {
	var p Product

	err := s.db.QueryRowContext(ctx, `
		SELECT product_id, kind, enabled
		  FROM product
		 WHERE product_id = ?`, id).
		Scan(&p.ID, &p.Kind, &p.Enabled)

	if err == sql.ErrNoRows {
		return p, errNoProduct
	}

	if err != nil {
		return p, fmt.Errorf("product 를 못 읽었다: %w", err)
	}

	if !p.Enabled {
		return p, errNoProduct
	}

	rows, err := s.db.QueryContext(ctx, `
		SELECT grant_kind, grant_amount
		  FROM product_grant
		 WHERE product_id = ?
		 ORDER BY seq`, id)

	if err != nil {
		return p, fmt.Errorf("product_grant 를 못 읽었다: %w", err)
	}

	defer rows.Close()

	for rows.Next() {
		var g GrantLine

		if err := rows.Scan(&g.Kind, &g.Amount); err != nil {
			return p, err
		}

		p.Grants = append(p.Grants, g)
	}

	if err := rows.Err(); err != nil {
		return p, err
	}

	// 아무것도 안 주는 상품은 팔면 안 된다. 돈만 받고 끝난다.
	if len(p.Grants) == 0 {
		return p, errNoProduct
	}

	return p, nil
}

// grantText 는 지급 내역을 사람이 읽을 글자로 만든다. 원장에 박아 둔다.
func grantText(gs []GrantLine) string {
	var b strings.Builder

	for i, g := range gs {
		if i > 0 {
			b.WriteString(",")
		}

		fmt.Fprintf(&b, "%s:%d", g.Kind, g.Amount)
	}

	return b.String()
}

// applyGrants 는 트랜잭션 안에서 실제로 준다.
//
// 칸 이름은 grantColumn / grantPass 지도에서만 온다. 바깥에서 온 문자열을
// SQL 에 이어붙이는 길이 없어야 한다.
func applyGrants(ctx context.Context, tx *sql.Tx, userID int64, gs []GrantLine) error {
	for _, g := range gs {
		if col, ok := grantColumn[g.Kind]; ok {
			_, err := tx.ExecContext(ctx, fmt.Sprintf(`
				UPDATE player SET %s = %s + ? WHERE user_id = ?`, col, col),
				g.Amount, userID)

			if err != nil {
				return fmt.Errorf("%s 를 못 줬다: %w", g.Kind, err)
			}

			continue
		}

		if col, ok := grantPass[g.Kind]; ok {
			// 남아 있으면 그 뒤에 이어 붙인다. 지났으면 지금부터.
			//
			// 게임 타임스탬프다. 서버의 NOW() 가 아니라 gameNow() 를 쓴다 -
			// 클라이언트가 보는 시계와 같아야 "언제까지" 가 맞는다.
			_, err := tx.ExecContext(ctx, fmt.Sprintf(`
				UPDATE player
				   SET %s = GREATEST(%s, ?) + ?
				 WHERE user_id = ?`, col, col),
				gameNow(), g.Amount*86400, userID)

			if err != nil {
				return fmt.Errorf("%s 를 못 걸었다: %w", g.Kind, err)
			}

			continue
		}

		return fmt.Errorf("줄 수 없는 재화다: %s", g.Kind)
	}

	// 판이 바뀌었으니 revision 을 올린다. 지급마다 올리지 않고 한 번만 올린다.
	_, err := tx.ExecContext(ctx, `
		UPDATE player SET revision = revision + 1 WHERE user_id = ?`, userID)

	return err
}

// knownGrants 는 줄 수 있는 것들인지 미리 본다.
//
// 트랜잭션을 열기 전에 본다. 절반 주고 실패하는 것보다 시작 전에 거절하는
// 편이 낫다.
func knownGrants(gs []GrantLine) bool {
	for _, g := range gs {
		_, a := grantColumn[g.Kind]
		_, b := grantPass[g.Kind]

		if !a && !b {
			return false
		}

		if g.Amount <= 0 {
			return false
		}
	}

	return true
}

// alreadyOwned 는 1 인 1 회 상품을 이미 받았는지 본다.
func (s *Store) alreadyOwned(ctx context.Context, userID int64, productID string) (
	bool, error) {

	var n int

	err := s.db.QueryRowContext(ctx, `
		SELECT COUNT(*) FROM purchase
		 WHERE user_id = ? AND product_id = ? AND state = ?`,
		userID, productID, purchaseGranted).Scan(&n)

	if err != nil {
		return false, fmt.Errorf("이미 샀는지 못 봤다: %w", err)
	}

	return n > 0, nil
}

// Grant 는 결제 하나를 처리한다.
//
// 이 함수가 이 파일의 전부다. 나머지는 여기로 오는 길이거나 여기서 나가는 길이다.
//
// 순서
//
//  1. 이미 처리한 거래인지 본다. 그렇다면 그때 결과를 그대로 돌려준다.
//  2. 상품을 찾는다.
//  3. 영수증을 확인한다.
//  4. 한 트랜잭션 안에서 원장에 적고 재화를 준다.
//
// 1번과 4번 사이에 다른 요청이 끼어들 수 있다. 같은 결제가 동시에 두 번
// 도착하는 경우다 - 재시도와 스토어 복원이 겹치면 실제로 일어난다. 그래서
// 1번의 확인만으로는 부족하고, 4번의 INSERT 가 uq_order 에 걸려 실패하는
// 것까지 받아내야 한다. 자물쇠는 확인이 아니라 표에 있다.
func (s *Store) Grant(ctx context.Context, v Verifier, userID int64,
	req PurchaseReq) (PurchaseResult, error) {

	var res PurchaseResult

	req.Platform = strings.TrimSpace(req.Platform)
	req.ProductID = strings.TrimSpace(req.ProductID)
	req.OrderID = strings.TrimSpace(req.OrderID)

	if req.Platform == "" || req.ProductID == "" || req.OrderID == "" {
		res.State = purchaseRejected
		res.Reason = "빠진 값이 있다"
		return res, nil
	}

	//---- 1. 이미 처리했는가 ----
	if got, ok, err := s.findPurchase(ctx, req.Platform, req.OrderID); err != nil {
		return res, err
	} else if ok {
		got.Repeat = true
		return got, nil
	}

	//---- 2. 상품 ----
	p, err := s.LoadProduct(ctx, req.ProductID)

	if err == errNoProduct {
		//원장에는 남긴다. 없는 상품을 사려는 시도가 잦으면 알아야 한다.
		res.State = purchaseRejected
		res.Reason = "없는 상품"
		s.logRejected(ctx, userID, req, res.Reason)
		return res, nil
	}

	if err != nil {
		return res, err
	}

	if !knownGrants(p.Grants) {
		res.State = purchaseRejected
		res.Reason = "줄 수 없는 재화"
		s.logRejected(ctx, userID, req, res.Reason)
		return res, nil
	}

	//---- 2-1. 1 인 1 회 상품이면 이미 받았는지 ----
	//
	// uq_order 는 "같은 거래" 를 막을 뿐, 같은 사람이 다른 거래로 또 사는
	// 것은 안 막는다. 스타터팩과 영구 확장이 그 경우다.
	//
	// 스토어 쪽에서도 비소비성으로 등록하면 한 번만 팔리지만, 그것만 믿지
	// 않는다. 여기서 막아야 어느 스토어를 쓰든 같게 동작한다.
	if p.Once() {
		owned, err := s.alreadyOwned(ctx, userID, req.ProductID)

		if err != nil {
			return res, err
		}

		if owned {
			res.State = purchaseRejected
			res.Reason = "이미 산 상품"
			s.logRejected(ctx, userID, req, res.Reason)
			return res, nil
		}
	}

	//---- 3. 영수증 ----
	if err := v.Verify(ctx, req); err != nil {
		res.State = purchaseRejected
		res.Reason = "영수증 확인 실패"
		s.logRejected(ctx, userID, req, res.Reason)
		return res, nil
	}

	//---- 4. 원장과 지급을 함께 ----
	//
	// 둘 중 하나만 되면 안 된다. 원장만 적히면 돈은 받고 안 준 것이고,
	// 지급만 되면 다음 재시도에 또 준다.
	tx, err := s.db.BeginTx(ctx, nil)

	if err != nil {
		return res, fmt.Errorf("트랜잭션을 못 열었다: %w", err)
	}

	defer tx.Rollback()

	text := grantText(p.Grants)

	_, err = tx.ExecContext(ctx, `
		INSERT INTO purchase
			(user_id, platform, product_id, order_id, state,
			 granted, receipt, granted_at)
		VALUES (?, ?, ?, ?, ?, ?, ?, NOW())`,
		userID, req.Platform, req.ProductID, req.OrderID, purchaseGranted,
		text, nullIfEmpty(req.Receipt))

	if err != nil {
		//uq_order 에 걸렸다. 1번과 여기 사이에 다른 요청이 먼저 끝냈다.
		//그쪽이 준 것이 맞으므로 그 결과를 읽어 돌려준다.
		if isDupKey(err) {
			got, ok, err2 := s.findPurchase(ctx, req.Platform, req.OrderID)

			if err2 != nil {
				return res, err2
			}

			if ok {
				got.Repeat = true
				return got, nil
			}
		}

		return res, fmt.Errorf("purchase 를 못 적었다: %w", err)
	}

	if err := applyGrants(ctx, tx, userID, p.Grants); err != nil {
		return res, err
	}

	if err := tx.Commit(); err != nil {
		return res, fmt.Errorf("커밋을 못 했다: %w", err)
	}

	res.State = purchaseGranted
	res.Granted = text

	return res, nil
}

// findPurchase 는 이미 처리한 거래를 찾는다.
func (s *Store) findPurchase(ctx context.Context, platform, orderID string) (
	PurchaseResult, bool, error) {

	var res PurchaseResult
	var reason sql.NullString

	err := s.db.QueryRowContext(ctx, `
		SELECT state, granted, reason
		  FROM purchase
		 WHERE platform = ? AND order_id = ?`, platform, orderID).
		Scan(&res.State, &res.Granted, &reason)

	if err == sql.ErrNoRows {
		return res, false, nil
	}

	if err != nil {
		return res, false, fmt.Errorf("purchase 를 못 읽었다: %w", err)
	}

	res.Reason = reason.String

	return res, true, nil
}

// logRejected 는 거절도 남긴다.
//
// 남기는 이유. 거절이 잦으면 무언가 잘못된 것이다 - 상품 ID 를 잘못 넣었거나,
// 누가 두드려 보고 있거나. 안 남기면 둘 다 안 보인다.
//
// 여기서 나는 오류는 삼킨다. 거절을 기록하다 실패했다고 해서 거절이라는
// 사실이 바뀌지는 않는다.
func (s *Store) logRejected(ctx context.Context, userID int64,
	req PurchaseReq, reason string) {

	_, err := s.db.ExecContext(ctx, `
		INSERT IGNORE INTO purchase
			(user_id, platform, product_id, order_id, state, granted, reason, receipt)
		VALUES (?, ?, ?, ?, ?, '', ?, ?)`,
		userID, req.Platform, req.ProductID, req.OrderID, purchaseRejected,
		reason, nullIfEmpty(req.Receipt))

	if err != nil {
		log.Printf("purchase: 거절을 못 남겼다: %v", err)
	}
}

// isDupKey 는 UNIQUE 에 걸렸는지 본다.
//
// 드라이버 타입을 끌어오지 않으려고 글자로 본다. MariaDB 의 1062 다.
func isDupKey(err error) bool {
	return err != nil && strings.Contains(err.Error(), "1062")
}
