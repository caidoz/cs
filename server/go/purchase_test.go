package main

import (
	"context"
	"sync"
	"testing"
)

// 결제에서 틀리면 안 되는 것은 하나다 - 한 번 산 것을 한 번만 주는가.
//
// 말로는 당연한데 코드로는 안 당연하다. 같은 결제가 두 번 오는 것이 정상이라
// (재시도, 스토어 복원, 앱 재시작) 그때마다 주면 재화가 무한히 늘어난다.
// 눈으로 읽어 넘길 자리가 아니라서 시험을 둔다.
//
//	INSAM_TEST_DSN='insam:암호@tcp(127.0.0.1:3306)/insam' go test -run Purchase

// 시험용 상품을 넣고, 끝나면 지운다.
func tempProduct(t *testing.T, s *Store, grant string, amount int64) string {
	t.Helper()

	id := "test-" + randomHex(t, 8)

	if _, err := s.db.Exec(`
		INSERT INTO product (product_id, kind, memo)
		VALUES (?, 'consumable', '시험용')`, id); err != nil {
		t.Fatal(err)
	}

	if _, err := s.db.Exec(`
		INSERT INTO product_grant (product_id, seq, grant_kind, grant_amount)
		VALUES (?, 0, ?, ?)`, id, grant, amount); err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() {
		s.db.Exec(`DELETE FROM product WHERE product_id = ?`, id)
	})

	return id
}

// 시험용 계정에 player 행을 만든다. 지급은 그 행을 고치는 일이라 없으면 안 된다.
func tempPlayer(t *testing.T, s *Store) int64 {
	t.Helper()

	id := tempAccount(t, s)

	_, err := s.db.Exec(`
		INSERT INTO player (user_id, revision, gold, heart, coin)
		VALUES (?, 1, 0, 0, 0)`, id)

	if err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() {
		s.db.Exec(`DELETE FROM purchase WHERE user_id = ?`, id)
		s.db.Exec(`DELETE FROM player WHERE user_id = ?`, id)
	})

	return id
}

func coinOf(t *testing.T, s *Store, userID int64) int64 {
	t.Helper()

	var n int64

	if err := s.db.QueryRow(
		`SELECT coin FROM player WHERE user_id = ?`, userID).Scan(&n); err != nil {
		t.Fatal(err)
	}

	return n
}

// 같은 거래를 두 번 보내도 한 번만 준다.
func TestPurchaseGrantsOnce(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)
	prod := tempProduct(t, s, "coin", 100)
	order := "order-" + randomHex(t, 10)

	req := PurchaseReq{
		Platform:  "ios",
		ProductID: prod,
		OrderID:   order,
		Receipt:   "받은-영수증",
	}

	first, err := s.Grant(ctx, verifierAllow{}, user, req)

	if err != nil {
		t.Fatal(err)
	}

	if first.State != purchaseGranted || first.Granted != "coin:100" {
		t.Fatalf("첫 결제가 이상하다: %+v", first)
	}

	if first.Repeat {
		t.Fatal("첫 결제인데 재시도로 봤다")
	}

	if got := coinOf(t, s, user); got != 100 {
		t.Fatalf("코인이 100 이어야 하는데 %d", got)
	}

	//---- 같은 것을 다시 ----
	second, err := s.Grant(ctx, verifierAllow{}, user, req)

	if err != nil {
		t.Fatal(err)
	}

	if !second.Repeat {
		t.Fatal("두 번째인데 재시도로 안 봤다")
	}

	if second.State != purchaseGranted {
		t.Fatalf("두 번째도 granted 로 답해야 한다: %+v", second)
	}

	//여기가 핵심이다.
	if got := coinOf(t, s, user); got != 100 {
		t.Fatalf("두 번 줬다. 코인이 %d", got)
	}
}

// 같은 거래가 동시에 여러 번 도착해도 한 번만 준다.
//
// 확인하고 넣는 사이에 다른 요청이 끼어드는 경우다. 확인만으로는 못 막고
// uq_order 가 막아야 한다. 그것이 실제로 도는지 본다.
func TestPurchaseConcurrent(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)
	prod := tempProduct(t, s, "coin", 7)
	order := "order-" + randomHex(t, 10)

	req := PurchaseReq{Platform: "android", ProductID: prod, OrderID: order}

	const n = 8

	var wg sync.WaitGroup
	errs := make([]error, n)

	wg.Add(n)

	for i := 0; i < n; i++ {
		go func(i int) {
			defer wg.Done()
			_, errs[i] = s.Grant(ctx, verifierAllow{}, user, req)
		}(i)
	}

	wg.Wait()

	for i, err := range errs {
		if err != nil {
			t.Fatalf("%d 번째가 실패했다: %v", i, err)
		}
	}

	if got := coinOf(t, s, user); got != 7 {
		t.Fatalf("%d 번 동시에 보냈는데 코인이 %d (7 이어야 한다)", n, got)
	}
}

// 없는 상품은 거절한다. 그리고 아무것도 안 준다.
func TestPurchaseUnknownProduct(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)

	res, err := s.Grant(ctx, verifierAllow{}, user, PurchaseReq{
		Platform:  "ios",
		ProductID: "그런-상품-없다",
		OrderID:   "order-" + randomHex(t, 10),
	})

	if err != nil {
		t.Fatal(err)
	}

	if res.State != purchaseRejected {
		t.Fatalf("거절해야 한다: %+v", res)
	}

	if got := coinOf(t, s, user); got != 0 {
		t.Fatalf("없는 상품에 %d 를 줬다", got)
	}
}

// 빠진 값이 있으면 거절한다.
func TestPurchaseMissingFields(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)

	for _, req := range []PurchaseReq{
		{Platform: "", ProductID: "x", OrderID: "y"},
		{Platform: "ios", ProductID: "", OrderID: "y"},
		{Platform: "ios", ProductID: "x", OrderID: ""},
	} {
		res, err := s.Grant(ctx, verifierAllow{}, user, req)

		if err != nil {
			t.Fatal(err)
		}

		if res.State != purchaseRejected {
			t.Fatalf("%+v 는 거절해야 한다", req)
		}
	}
}

// 1 인 1 회 상품은 두 번 못 산다.
//
// uq_order 로는 못 막는다. 거래 ID 가 다르기 때문이다. 스토어를 두 개 쓰거나
// 스토어가 다시 팔아버리는 경우가 실제로 있어서, 서버가 따로 막아야 한다.
func TestPurchaseOnceOnly(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)
	prod := "test-" + randomHex(t, 8)

	if _, err := s.db.Exec(`
		INSERT INTO product (product_id, kind, memo)
		VALUES (?, 'noncon', '시험용 1회')`, prod); err != nil {
		t.Fatal(err)
	}

	if _, err := s.db.Exec(`
		INSERT INTO product_grant (product_id, seq, grant_kind, grant_amount)
		VALUES (?, 0, 'coin', 500)`, prod); err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() { s.db.Exec(`DELETE FROM product WHERE product_id = ?`, prod) })

	first, err := s.Grant(ctx, verifierAllow{}, user, PurchaseReq{
		Platform: "ios", ProductID: prod, OrderID: "o1-" + randomHex(t, 8)})

	if err != nil {
		t.Fatal(err)
	}

	if first.State != purchaseGranted {
		t.Fatalf("첫 구매가 되어야 한다: %+v", first)
	}

	//거래 ID 가 다르다. uq_order 로는 안 걸린다.
	second, err := s.Grant(ctx, verifierAllow{}, user, PurchaseReq{
		Platform: "ios", ProductID: prod, OrderID: "o2-" + randomHex(t, 8)})

	if err != nil {
		t.Fatal(err)
	}

	if second.State != purchaseRejected {
		t.Fatalf("두 번째는 거절해야 한다: %+v", second)
	}

	if got := coinOf(t, s, user); got != 500 {
		t.Fatalf("두 번 줬다. 코인이 %d", got)
	}
}

// 스타터팩처럼 여러 개를 주는 상품.
func TestPurchaseMultiGrant(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)
	prod := "test-" + randomHex(t, 8)

	if _, err := s.db.Exec(`
		INSERT INTO product (product_id, kind, memo)
		VALUES (?, 'consumable', '시험용 묶음')`, prod); err != nil {
		t.Fatal(err)
	}

	if _, err := s.db.Exec(`
		INSERT INTO product_grant (product_id, seq, grant_kind, grant_amount)
		VALUES (?, 0, 'coin', 111), (?, 1, 'heart', 222)`, prod, prod); err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() { s.db.Exec(`DELETE FROM product WHERE product_id = ?`, prod) })

	res, err := s.Grant(ctx, verifierAllow{}, user, PurchaseReq{
		Platform: "ios", ProductID: prod, OrderID: "m-" + randomHex(t, 8)})

	if err != nil {
		t.Fatal(err)
	}

	if res.Granted != "coin:111,heart:222" {
		t.Fatalf("지급 내역이 이상하다: %q", res.Granted)
	}

	var coin, heart int64

	if err := s.db.QueryRow(`SELECT coin, heart FROM player WHERE user_id = ?`,
		user).Scan(&coin, &heart); err != nil {
		t.Fatal(err)
	}

	if coin != 111 || heart != 222 {
		t.Fatalf("coin=%d heart=%d (111/222 여야 한다)", coin, heart)
	}
}

// 패스는 남은 기간에 이어 붙는다.
func TestPurchasePassStacks(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempPlayer(t, s)
	prod := "test-" + randomHex(t, 8)

	if _, err := s.db.Exec(`
		INSERT INTO product (product_id, kind, memo)
		VALUES (?, 'consumable', '시험용 패스')`, prod); err != nil {
		t.Fatal(err)
	}

	if _, err := s.db.Exec(`
		INSERT INTO product_grant (product_id, seq, grant_kind, grant_amount)
		VALUES (?, 0, 'pass_heart', 30)`, prod); err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() { s.db.Exec(`DELETE FROM product WHERE product_id = ?`, prod) })

	days := func() int64 {
		var n int64

		if err := s.db.QueryRow(`
			SELECT COALESCE(DATEDIFF(heart_pass_until, NOW()), -1)
			  FROM player WHERE user_id = ?`, user).Scan(&n); err != nil {
			t.Fatal(err)
		}

		return n
	}

	for i := 1; i <= 2; i++ {
		if _, err := s.Grant(ctx, verifierAllow{}, user, PurchaseReq{
			Platform: "ios", ProductID: prod,
			OrderID: "p-" + randomHex(t, 8)}); err != nil {
			t.Fatal(err)
		}

		//DATEDIFF 는 날짜 차라 경계에서 하루 덜 나올 수 있다.
		want := int64(30 * i)

		if got := days(); got != want && got != want-1 {
			t.Fatalf("%d번 산 뒤 남은 날이 %d (%d 여야 한다)", i, got, want)
		}
	}
}
