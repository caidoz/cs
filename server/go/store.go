// DB 쪽. 표와 컬럼 목록을 information_schema 에서 읽어 화이트리스트를 만들고,
// 그 목록으로만 질의를 짓는다.
//
// 이것이 중요한 이유는 저장 경로에 있다. 클라이언트가 보낸 #cols 가 곧
// INSERT 의 괄호 안이 되므로, 그대로 이어 붙이면 그 자리가 인젝션 통로다.
// 그래서 이름은 여기서 만든 목록에 있는 것만 쓰고 값은 전부 바인딩한다.
package main

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"strings"
)

// ErrNoSave 는 계정은 있는데 세이브가 없는 것이다. 404 로 답한다.
// 클라이언트는 이것을 받으면 새 게임을 시작한다.
var ErrNoSave = errors.New("세이브가 없다")

// ErrBanned 는 banned_until 이 아직 안 지난 계정이다.
var ErrBanned = errors.New("차단된 계정이다")

// ColMeta 는 컬럼 하나에 대해 우리가 알아야 하는 것들이다.
type ColMeta struct {
	Name     string
	DataType string
	AutoInc  bool
}

// IsTime 은 운영용 DATETIME 컬럼인지 본다.
//
// 이런 컬럼은 덤프에 넣지 않는다. 클라이언트가 기기 시계로 만든 시각을
// 운영 지표에 섞으면 안 되기 때문이고, 그래서 created_at / updated_at 은
// 서버가 NOW() 로만 채운다. 게임 로직이 쓰는 시간은 전부 *_ts (BIGINT) 라
// 그것들은 그대로 덤프에 들어간다.
func (c ColMeta) IsTime() bool {
	switch c.DataType {
	case "datetime", "timestamp", "date", "time":
		return true
	}

	return false
}

// TableMeta 는 표 하나의 생김새다.
type TableMeta struct {
	Name   string
	Cols   []ColMeta
	ColSet map[string]ColMeta
	PK     []string
}

// Has 는 그런 이름의 컬럼이 있는지 본다. 화이트리스트가 이것이다.
func (t *TableMeta) Has(col string) bool {
	_, ok := t.ColSet[col]
	return ok
}

// DumpCols 는 덤프에 실을 컬럼들이다. 순서는 스키마에 적힌 순서다.
func (t *TableMeta) DumpCols() []string {
	out := make([]string, 0, len(t.Cols))

	for _, c := range t.Cols {
		if c.IsTime() {
			continue
		}

		out = append(out, c.Name)
	}

	return out
}

// Schema 는 DB 전체의 생김새다. 서버가 뜰 때 한 번 읽는다.
type Schema struct {
	Tables  map[string]*TableMeta
	Version int64
}

// Store 는 DB 손잡이다.
type Store struct {
	db     *sql.DB
	schema *Schema
}

func NewStore(db *sql.DB) *Store {
	return &Store{db: db}
}

// LoadSchema 는 information_schema 에서 표와 컬럼을 읽어 화이트리스트를 만든다.
//
// 서버가 뜰 때 한 번만 한다. 스키마를 바꾸면 서버를 다시 띄워야 한다는 뜻인데,
// 컬럼은 더하기만 하고 빼지 않는 것이 규칙이므로 (dumpformat.md 규칙 2)
// 옛 서버가 새 컬럼을 모르는 동안에도 DEFAULT 가 들어갈 뿐 깨지지 않는다.
func (s *Store) LoadSchema(ctx context.Context, dbName string) error {
	sc := &Schema{Tables: map[string]*TableMeta{}}

	rows, err := s.db.QueryContext(ctx, `
		SELECT table_name, column_name, data_type, extra
		  FROM information_schema.columns
		 WHERE table_schema = ?
		 ORDER BY table_name, ordinal_position`, dbName)

	if err != nil {
		return fmt.Errorf("컬럼 목록을 못 읽었다: %w", err)
	}

	defer rows.Close()

	for rows.Next() {
		var tname, cname, dtype, extra string

		if err := rows.Scan(&tname, &cname, &dtype, &extra); err != nil {
			return err
		}

		t := sc.Tables[tname]

		if t == nil {
			t = &TableMeta{Name: tname, ColSet: map[string]ColMeta{}}
			sc.Tables[tname] = t
		}

		c := ColMeta{
			Name:     cname,
			DataType: strings.ToLower(dtype),
			AutoInc:  strings.Contains(strings.ToLower(extra), "auto_increment"),
		}

		t.Cols = append(t.Cols, c)
		t.ColSet[cname] = c
	}

	if err := rows.Err(); err != nil {
		return err
	}

	if len(sc.Tables) == 0 {
		return fmt.Errorf("%s 에 표가 하나도 없다. DB 이름이 맞나", dbName)
	}

	// 기본키. 덤프의 행 순서를 정하는 데 쓴다. 순서가 매번 같아야
	// 두 응답을 눈으로 비교할 수 있고, 체크섬도 같아진다.
	pk, err := s.db.QueryContext(ctx, `
		SELECT table_name, column_name
		  FROM information_schema.statistics
		 WHERE table_schema = ? AND index_name = 'PRIMARY'
		 ORDER BY table_name, seq_in_index`, dbName)

	if err != nil {
		return fmt.Errorf("기본키를 못 읽었다: %w", err)
	}

	defer pk.Close()

	for pk.Next() {
		var tname, cname string

		if err := pk.Scan(&tname, &cname); err != nil {
			return err
		}

		if t := sc.Tables[tname]; t != nil {
			t.PK = append(t.PK, cname)
		}
	}

	if err := pk.Err(); err != nil {
		return err
	}

	// schema_version 은 덤프의 #schema 줄에 그대로 실린다.
	if err := s.db.QueryRowContext(ctx,
		`SELECT MAX(version) FROM schema_version`).Scan(&sc.Version); err != nil {
		return fmt.Errorf("schema_version 을 못 읽었다: %w", err)
	}

	s.schema = sc
	return nil
}

// Schema 는 읽어둔 스키마다.
func (s *Store) Schema() *Schema { return s.schema }

// -----------------------------------------------------------------------------
// 로그인
// -----------------------------------------------------------------------------

// Login 은 guest_key 로 계정을 찾고, 없으면 만든다.
//
// 1단계에서는 이 열쇠 하나로 로그인된다. 유출되면 계정을 통째로 잃는다는
// 것을 스키마 주석이 이미 경고하고 있고, 3단계에서 세션 토큰으로 바꾼다.
func (s *Store) Login(ctx context.Context, guestKey string) (userID, revision int64, err error) {
	var banned sql.NullString

	err = s.db.QueryRowContext(ctx,
		`SELECT user_id, IFNULL(DATE_FORMAT(banned_until, '%Y-%m-%d %H:%i:%s'), '')
		   FROM account WHERE guest_key = ?`, guestKey).Scan(&userID, &banned)

	switch {
	case err == sql.ErrNoRows:
		// 처음 온 손님. 계정을 만든다. user_id 는 AUTO_INCREMENT 가 준다.
		res, ierr := s.db.ExecContext(ctx,
			`INSERT INTO account (guest_key, last_login_at) VALUES (?, NOW())`, guestKey)

		if ierr != nil {
			return 0, 0, fmt.Errorf("계정을 못 만들었다: %w", ierr)
		}

		id, ierr := res.LastInsertId()

		if ierr != nil {
			return 0, 0, ierr
		}

		return id, 0, nil

	case err != nil:
		return 0, 0, err
	}

	if banned.Valid && banned.String != "" {
		var still bool

		if qerr := s.db.QueryRowContext(ctx,
			`SELECT banned_until > NOW() FROM account WHERE user_id = ?`,
			userID).Scan(&still); qerr == nil && still {
			return 0, 0, ErrBanned
		}
	}

	if _, err = s.db.ExecContext(ctx,
		`UPDATE account SET last_login_at = NOW() WHERE user_id = ?`, userID); err != nil {
		return 0, 0, err
	}

	// 세이브가 아직 없으면 revision 은 0 이다.
	err = s.db.QueryRowContext(ctx,
		`SELECT revision FROM player WHERE user_id = ?`, userID).Scan(&revision)

	if err == sql.ErrNoRows {
		return userID, 0, nil
	}

	if err != nil {
		return 0, 0, err
	}

	return userID, revision, nil
}

// -----------------------------------------------------------------------------
// 세이브 내려주기
// -----------------------------------------------------------------------------

// LoadDump 는 그 유저의 행을 전부 긁어 덤프 한 벌을 만든다.
//
// 표 하나를 질의 하나로 읽는다. 20여 번의 왕복이지만 전부 기본키나
// user_id 인덱스를 타는 작은 질의이고, DB 가 같은 기계에 있다.
func (s *Store) LoadDump(ctx context.Context, userID int64) (*Dump, error) {
	var revision int64

	err := s.db.QueryRowContext(ctx,
		`SELECT revision FROM player WHERE user_id = ?`, userID).Scan(&revision)

	if err == sql.ErrNoRows {
		return nil, ErrNoSave
	}

	if err != nil {
		return nil, err
	}

	d := &Dump{
		Schema:   s.schema.Version,
		User:     userID,
		Revision: revision,
	}

	for _, name := range TableOrder {
		if serverOnlyTables[name] {
			continue
		}

		t := s.schema.Tables[name]

		if t == nil {
			// 스키마에 없는 표는 건너뛴다. TableOrder 가 스키마보다
			// 앞서 나갈 수 있어서 이쪽을 관대하게 둔다.
			continue
		}

		tab, err := s.loadTable(ctx, t, userID)

		if err != nil {
			return nil, fmt.Errorf("표 %s: %w", name, err)
		}

		d.Tables = append(d.Tables, *tab)
	}

	return d, nil
}

// loadTable 은 표 하나를 읽는다.
func (s *Store) loadTable(ctx context.Context, t *TableMeta, userID int64) (*Table, error) {
	cols := t.DumpCols()

	if len(cols) == 0 {
		return &Table{Name: t.Name}, nil
	}

	quoted := make([]string, len(cols))

	for i, c := range cols {
		quoted[i] = "`" + c + "`"
	}

	// 어디에 매달린 표인지에 따라 조건이 갈린다.
	//   user_id 가 있으면      그것으로 곧장 고른다
	//   item_uid 만 있으면     inventory 를 거쳐 고른다
	//                          (inventory_option / inventory_socket 이 그렇다)
	var where string

	switch {
	case t.Has("user_id"):
		where = "WHERE `user_id` = ?"
	case t.Has("item_uid"):
		where = "WHERE `item_uid` IN (SELECT item_uid FROM inventory WHERE user_id = ?)"
	default:
		return nil, fmt.Errorf("user_id 도 item_uid 도 없어서 누구 것인지 알 수 없다")
	}

	order := ""

	if len(t.PK) > 0 {
		keys := make([]string, len(t.PK))

		for i, k := range t.PK {
			keys[i] = "`" + k + "`"
		}

		order = " ORDER BY " + strings.Join(keys, ", ")
	}

	// 이름은 전부 information_schema 에서 온 것이고 값은 바인딩이다.
	q := fmt.Sprintf("SELECT %s FROM `%s` %s%s",
		strings.Join(quoted, ", "), t.Name, where, order)

	rows, err := s.db.QueryContext(ctx, q, userID)

	if err != nil {
		return nil, err
	}

	defer rows.Close()

	out := &Table{Name: t.Name, Cols: cols}
	buf := make([][]byte, len(cols))
	ptr := make([]any, len(cols))

	for i := range buf {
		ptr[i] = &buf[i]
	}

	for rows.Next() {
		if err := rows.Scan(ptr...); err != nil {
			return nil, err
		}

		vals := make([]*string, len(cols))

		for i, b := range buf {
			// nil 은 NULL 이다. 길이 0 인 슬라이스는 빈 문자열이라 다르다.
			if b == nil {
				continue
			}

			v := string(b)
			vals[i] = &v
		}

		out.Rows = append(out.Rows, vals)
	}

	return out, rows.Err()
}
