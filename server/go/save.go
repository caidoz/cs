// 저장. 서버에서 가장 조심할 곳이다.
//
// 클라이언트는 저장할 때마다 전체를 보낸다 (dumpformat.md 규칙 4). 그래서
// 여기서 하는 일은 부분 갱신이 아니라 그 유저의 행을 전부 갈아끼우는 것이다.
// 수 KB라 그래도 된다.
//
// 규약은 schema.sql 머리주석에 있다 — 나중에 온 저장을 거절한다.
package main

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"strconv"
	"strings"
)

// ErrConflict 는 다른 기기가 먼저 저장한 것이다. 409 로 답한다.
var ErrConflict = errors.New("다른 기기가 먼저 저장했다")

// ErrNotYours 는 남의 세이브를 덮으려 한 것이다.
var ErrNotYours = errors.New("자기 것이 아닌 세이브다")

// 클라이언트가 보내와도 쓰지 않는 표.
//
// account 는 계정 자체다. 클라이언트는 #cols 에 user_id 하나만 실어 보내는데,
// 그것을 지우고 다시 넣으면 guest_key 가 날아가 계정을 통째로 잃는다.
// account_link 도 같은 이유로 서버만 건드린다.
var writeSkipTables = map[string]bool{
	"account":      true,
	"account_link": true,
}

// 한 번에 넣을 행 수. 자리표시자가 너무 많아지지 않게 끊는다.
const insertChunk = 100

// SaveDump 는 덤프 한 벌을 그 유저의 행으로 갈아끼운다.
//
// 성공하면 새 revision 을 준다. 거절이면 ErrConflict 와 함께 서버가 들고
// 있던 revision 을 준다.
func (s *Store) SaveDump(ctx context.Context, userID int64, d *Dump) (int64, int64, error) {
	// 남의 것을 덮으려는 것인지 먼저 본다. 헤더의 열쇠로 정해진 유저가
	// 정답이고, 몸통에 적힌 #user 는 참고일 뿐이다.
	if d.User != 0 && d.User != userID {
		return 0, 0, ErrNotYours
	}

	tables, err := s.checkTables(d)

	if err != nil {
		return 0, 0, err
	}

	player := findTable(tables, "player")

	if player == nil {
		return 0, 0, dumpErr("player 표가 없다. 저장할 것이 없다")
	}

	if len(player.Rows) != 1 {
		return 0, 0, dumpErr("player 표가 %d행이다. 한 행이어야 한다", len(player.Rows))
	}

	tx, err := s.db.BeginTx(ctx, nil)

	if err != nil {
		return 0, 0, err
	}

	defer tx.Rollback()

	// ---- 낙관적 잠금 ----
	newRev, serverRev, err := s.bumpPlayer(ctx, tx, userID, d.Revision, player)

	if err != nil {
		return 0, serverRev, err
	}

	// ---- 자식 표를 갈아끼운다 ----
	//
	// 지우는 것은 자식부터, 넣는 것은 부모부터. 외래키가 그 순서를 요구한다.
	for i := len(TableOrder) - 1; i >= 0; i-- {
		name := TableOrder[i]

		if writeSkipTables[name] || name == "player" || serverOnlyTables[name] {
			continue
		}

		t := s.schema.Tables[name]

		if t == nil {
			continue
		}

		if err := s.clearTable(ctx, tx, t, userID); err != nil {
			return 0, 0, fmt.Errorf("표 %s 를 못 비웠다: %w", name, err)
		}
	}

	// 클라이언트가 매긴 item_uid 와 서버가 준 item_uid 를 잇는 표.
	// inventory 를 넣을 때 만들어지고, 그것을 참조하는 표들이 쓴다.
	var uid map[int64]int64

	for _, name := range TableOrder {
		if writeSkipTables[name] || name == "player" || serverOnlyTables[name] {
			continue
		}

		tab := findTable(tables, name)

		if tab == nil || len(tab.Rows) == 0 {
			continue
		}

		meta := s.schema.Tables[name]
		var err error

		if name == "inventory" {
			uid, err = s.insertInventory(ctx, tx, meta, tab, userID)
		} else {
			err = s.insertRows(ctx, tx, meta, tab, userID, uid)
		}

		if err != nil {
			return 0, 0, fmt.Errorf("표 %s 를 못 넣었다: %w", name, err)
		}
	}

	if err := tx.Commit(); err != nil {
		return 0, 0, err
	}

	return newRev, 0, nil
}

// checkTables 는 쓸 표만 골라내면서 규격을 검사한다.
//
// 여기가 화이트리스트다. #cols 는 클라이언트가 보낸 문자열이고 그것이 곧
// INSERT 의 괄호 안이 되므로, 스키마에 있는 이름인지 여기서 확인하지 않으면
// 그 자리가 인젝션 통로가 된다.
func (s *Store) checkTables(d *Dump) ([]Table, error) {
	out := make([]Table, 0, len(d.Tables))
	seen := map[string]bool{}

	for _, t := range d.Tables {
		if seen[t.Name] {
			return nil, dumpErr("표 %s 가 두 번 나온다", t.Name)
		}

		seen[t.Name] = true

		meta := s.schema.Tables[t.Name]

		if meta == nil || serverOnlyTables[t.Name] {
			return nil, dumpErr("모르는 표다: %s", t.Name)
		}

		for _, c := range t.Cols {
			col, ok := meta.ColSet[c]

			if !ok {
				return nil, dumpErr("표 %s 에 %s 컬럼이 없다", t.Name, c)
			}

			// 운영용 시각은 서버가 NOW() 로만 채운다. 클라이언트가 기기
			// 시계로 만든 값을 지표에 섞으면 안 된다.
			if col.IsTime() {
				return nil, dumpErr("표 %s 의 %s 는 서버가 채우는 컬럼이다", t.Name, c)
			}
		}

		if writeSkipTables[t.Name] {
			// 받기는 하되 쓰지 않는다. 클라이언트가 account 를 실어 보내는
			// 것은 규격에 맞고, 그것을 무시하는 것은 서버의 사정이다.
			continue
		}

		if t.Name != "player" && !meta.Has("user_id") && !meta.Has("item_uid") {
			return nil, dumpErr("표 %s 는 누구 것인지 알 수 없다", t.Name)
		}

		out = append(out, t)
	}

	return out, nil
}

// bumpPlayer 는 revision 을 올리면서 player 를 갱신한다. 충돌이 여기서 갈린다.
func (s *Store) bumpPlayer(ctx context.Context, tx *sql.Tx,
	userID, sentRev int64, player *Table) (int64, int64, error) {

	meta := s.schema.Tables["player"]
	sets := make([]string, 0, len(player.Cols))
	args := make([]any, 0, len(player.Cols)+2)

	for i, c := range player.Cols {
		// revision 은 서버가 정한다. user_id 는 열쇠로 이미 정해져 있다.
		if c == "revision" || c == "user_id" {
			continue
		}

		sets = append(sets, "`"+c+"` = ?")
		args = append(args, value(player.Rows[0][i]))
	}

	sets = append(sets, "`revision` = `revision` + 1")

	if meta.Has("updated_at") {
		sets = append(sets, "`updated_at` = NOW()")
	}

	args = append(args, userID, sentRev)

	q := "UPDATE `player` SET " + strings.Join(sets, ", ") +
		" WHERE `user_id` = ? AND `revision` = ?"

	res, err := tx.ExecContext(ctx, q, args...)

	if err != nil {
		return 0, 0, err
	}

	n, err := res.RowsAffected()

	if err != nil {
		return 0, 0, err
	}

	if n == 1 {
		return sentRev + 1, 0, nil
	}

	// 안 맞았다. 아직 세이브가 없는 것인지, 정말 충돌인지 가른다.
	var serverRev int64

	err = tx.QueryRowContext(ctx,
		"SELECT revision FROM player WHERE user_id = ?", userID).Scan(&serverRev)

	if err == sql.ErrNoRows {
		// 첫 저장이다. 넣을 행이 아직 없었을 뿐이라 충돌이 아니다.
		if sentRev != 0 {
			return 0, 0, ErrConflict
		}

		if err := s.insertPlayer(ctx, tx, userID, player); err != nil {
			return 0, 0, err
		}

		return 1, 0, nil
	}

	if err != nil {
		return 0, 0, err
	}

	return 0, serverRev, ErrConflict
}

// insertPlayer 는 첫 저장에서 player 행을 만든다.
func (s *Store) insertPlayer(ctx context.Context, tx *sql.Tx,
	userID int64, player *Table) error {

	cols := []string{"user_id", "revision"}
	marks := []string{"?", "?"}
	args := []any{userID, int64(1)}

	for i, c := range player.Cols {
		if c == "revision" || c == "user_id" {
			continue
		}

		cols = append(cols, "`"+c+"`")
		marks = append(marks, "?")
		args = append(args, value(player.Rows[0][i]))
	}

	// 앞의 둘은 이미 따옴표가 없다. 여기서 맞춰준다.
	cols[0] = "`user_id`"
	cols[1] = "`revision`"

	q := fmt.Sprintf("INSERT INTO `player` (%s) VALUES (%s)",
		strings.Join(cols, ", "), strings.Join(marks, ", "))

	_, err := tx.ExecContext(ctx, q, args...)

	return err
}

// clearTable 은 그 유저의 행을 지운다. 갈아끼우기의 앞 절반이다.
func (s *Store) clearTable(ctx context.Context, tx *sql.Tx,
	t *TableMeta, userID int64) error {

	var q string

	switch {
	case t.Has("user_id"):
		q = "DELETE FROM `" + t.Name + "` WHERE `user_id` = ?"

	case t.Has("item_uid"):
		q = "DELETE FROM `" + t.Name + "`" +
			" WHERE `item_uid` IN (SELECT item_uid FROM inventory WHERE user_id = ?)"

	default:
		return nil
	}

	_, err := tx.ExecContext(ctx, q, userID)

	return err
}

// insertInventory 는 inventory 를 넣고, 번호를 잇는 표를 만들어 준다.
//
// item_uid 는 클라이언트가 매긴 번호다. 임시 서버 시절에는 그 기기에 유저가
// 하나뿐이라 1부터 붙여도 됐지만, 서버에서는 이 컬럼이 표 전체의 기본키다.
// 두 사람이 다 1번을 들고 오면 부딪힌다. 그래서 클라이언트가 보낸 번호는
// 버리고 AUTO_INCREMENT 가 발급하게 한다 — dumpformat.md 규칙 3도 "서버로
// 넘어가면 이 번호는 서버가 발급한다" 고 적고 있다.
//
// 그러면 inventory_option / inventory_socket 이 가리키던 번호가 떠버린다.
// 그것을 자연키(uq_inventory = user_id + item_type + detail + grade)로 다시
// 잇는다. AUTO_INCREMENT 가 연달아 준다는 가정에 기대지 않으려고 그렇게 한다.
//
// (dumpformat.md 는 hero_equip 이 이 번호를 참조한다고 적고 있는데, 실제
// 스키마에서는 아니다. item_type/detail/grade 를 제 안에 들고 있다.)
func (s *Store) insertInventory(ctx context.Context, tx *sql.Tx,
	meta *TableMeta, t *Table, userID int64) (map[int64]int64, error) {

	uidAt := indexOf(t.Cols, "item_uid")

	// 번호를 뺀 채로 넣는다.
	if err := s.insertRows(ctx, tx, meta, t, userID, nil); err != nil {
		return nil, err
	}

	if uidAt < 0 {
		// 클라이언트가 번호를 안 보냈다. 이어줄 것이 없다.
		return map[int64]int64{}, nil
	}

	typeAt := indexOf(t.Cols, "item_type")
	detailAt := indexOf(t.Cols, "detail")
	gradeAt := indexOf(t.Cols, "grade")

	if typeAt < 0 || detailAt < 0 || gradeAt < 0 {
		// 자연키가 모자라서 이을 수 없다. 참조하는 표가 있으면 그때 걸린다.
		return map[int64]int64{}, nil
	}

	rows, err := tx.QueryContext(ctx,
		`SELECT item_uid, item_type, detail, grade FROM inventory WHERE user_id = ?`, userID)

	if err != nil {
		return nil, err
	}

	defer rows.Close()

	fresh := map[string]int64{}

	for rows.Next() {
		var uid, it, de, gr int64

		if err := rows.Scan(&uid, &it, &de, &gr); err != nil {
			return nil, err
		}

		fresh[natKey(it, de, gr)] = uid
	}

	if err := rows.Err(); err != nil {
		return nil, err
	}

	out := make(map[int64]int64, len(t.Rows))

	for _, row := range t.Rows {
		old, ok := asInt(row[uidAt])

		if !ok {
			continue
		}

		it, ok1 := asInt(row[typeAt])
		de, ok2 := asInt(row[detailAt])
		gr, ok3 := asInt(row[gradeAt])

		if !ok1 || !ok2 || !ok3 {
			continue
		}

		if nu, ok := fresh[natKey(it, de, gr)]; ok {
			out[old] = nu
		}
	}

	return out, nil
}

// insertRows 는 표 하나를 넣는다.
//
// uid 가 있으면 item_uid 칸을 그 표로 옮겨 적는다. inventory 를 넣으면서
// 번호가 바뀌었기 때문이다. inventory 자신을 넣을 때는 nil 을 주고, 그러면
// item_uid 컬럼을 통째로 뺀다(서버가 발급한다).
func (s *Store) insertRows(ctx context.Context, tx *sql.Tx,
	meta *TableMeta, t *Table, userID int64, uid map[int64]int64) error {

	userAt := -1
	uidAt := -1
	skip := -1

	if meta.Name == "inventory" {
		skip = indexOf(t.Cols, "item_uid")
	}

	quoted := make([]string, 0, len(t.Cols))

	for i, c := range t.Cols {
		if i == skip {
			continue
		}

		quoted = append(quoted, "`"+c+"`")

		if c == "user_id" {
			userAt = i
		}

		if c == "item_uid" {
			uidAt = i
		}
	}

	head := fmt.Sprintf("INSERT INTO `%s` (%s) VALUES ",
		meta.Name, strings.Join(quoted, ", "))

	one := "(" + strings.TrimSuffix(strings.Repeat("?, ", len(quoted)), ", ") + ")"

	for from := 0; from < len(t.Rows); from += insertChunk {
		to := from + insertChunk

		if to > len(t.Rows) {
			to = len(t.Rows)
		}

		marks := make([]string, 0, to-from)
		args := make([]any, 0, (to-from)*len(quoted))

		for _, row := range t.Rows[from:to] {
			marks = append(marks, one)

			for i, v := range row {
				if i == skip {
					continue
				}

				// 몸통에 적힌 user_id 를 믿지 않는다. 열쇠로 정해진
				// 유저만 쓴다. 이것이 없으면 남의 행을 만들 수 있다.
				if i == userAt {
					args = append(args, userID)
					continue
				}

				// 가리키던 번호를 서버가 발급한 번호로 바꿔 적는다.
				if i == uidAt && uid != nil {
					old, ok := asInt(v)

					if !ok {
						return dumpErr("표 %s: item_uid 가 숫자가 아니다", meta.Name)
					}

					nu, ok := uid[old]

					if !ok {
						// 없는 아이템을 가리킨다. 그대로 넣으면 외래키가
						// 막거나, 더 나쁘게는 남의 아이템에 붙는다.
						return dumpErr("표 %s: %d번 아이템이 인벤토리에 없다",
							meta.Name, old)
					}

					args = append(args, nu)
					continue
				}

				args = append(args, value(v))
			}
		}

		if _, err := tx.ExecContext(ctx, head+strings.Join(marks, ", "), args...); err != nil {
			return err
		}
	}

	return nil
}

func indexOf(cols []string, name string) int {
	for i, c := range cols {
		if c == name {
			return i
		}
	}

	return -1
}

func natKey(itemType, detail, grade int64) string {
	return fmt.Sprintf("%d|%d|%d", itemType, detail, grade)
}

func asInt(v *string) (int64, bool) {
	if v == nil {
		return 0, false
	}

	n, err := strconv.ParseInt(strings.TrimSpace(*v), 10, 64)

	return n, err == nil
}

// LogConflict 는 거절한 저장을 남긴다.
//
// 이 표가 잦아지면 클라이언트의 저장 시점이 잘못됐다는 뜻이다. 표 주석이
// 이미 그렇게 적고 있다.
func (s *Store) LogConflict(ctx context.Context, userID, sentRev, serverRev int64, hint string) {
	if len(hint) > 64 {
		hint = hint[:64]
	}

	_, err := s.db.ExecContext(ctx,
		`INSERT INTO save_conflict_log (user_id, sent_rev, server_rev, device_hint)
		 VALUES (?, ?, ?, ?)`, userID, sentRev, serverRev, nullIfEmpty(hint))

	if err != nil {
		// 기록에 실패했다고 저장 처리를 흔들지는 않는다. 남기기만 한다.
		fmt.Printf("save_conflict_log 를 못 남겼다: %v\n", err)
	}
}

func findTable(tables []Table, name string) *Table {
	for i := range tables {
		if tables[i].Name == name {
			return &tables[i]
		}
	}

	return nil
}

// value 는 덤프의 칸 하나를 바인딩 인자로 바꾼다. nil 은 NULL 이다.
func value(v *string) any {
	if v == nil {
		return nil
	}

	return *v
}

func nullIfEmpty(s string) any {
	if s == "" {
		return nil
	}

	return s
}
