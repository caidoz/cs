package main

import (
	"context"
	"crypto/rand"
	"database/sql"
	"encoding/hex"
	"errors"
	"os"
	"testing"

	_ "github.com/go-sql-driver/mysql"
)

// 진짜 DB 를 상대로 돈다. INSAM_TEST_DSN 이 있을 때만 돌고, 없으면 건너뛴다.
//
//	INSAM_TEST_DSN='insam:암호@tcp(127.0.0.1:3306)/insam' go test -run Link
//
// 붙이는 규칙이 말로는 간단한데 경우가 갈린다. 같은 것을 두 번 붙이면
// 성공이어야 하고(답을 못 받고 다시 보내는 일이 흔하다), 남의 것에 붙어
// 있으면 거절이어야 한다. 그 갈래를 눈으로 읽어 넘길 자리가 아니다.
func linkTestStore(t *testing.T) *Store {
	t.Helper()

	dsn := os.Getenv("INSAM_TEST_DSN")

	if dsn == "" {
		t.Skip("INSAM_TEST_DSN 이 없다")
	}

	db, err := sql.Open("mysql", dsn)

	if err != nil {
		t.Fatal(err)
	}

	if err := db.Ping(); err != nil {
		t.Fatal(err)
	}

	// 닫는 것도 t.Cleanup 으로 건다.
	//
	// defer 로 닫으면 안 된다. t.Cleanup 은 시험 함수의 defer 가 다 돌고 난
	// 뒤에 도는데, 그때 DB 가 이미 닫혀 있으면 계정을 지우는 뒷정리가 조용히
	// 실패한다. 같은 Cleanup 에 걸어두면 나중에 건 것부터 도니 순서가 맞는다.
	t.Cleanup(func() { db.Close() })

	return NewStore(db)
}

// 시험용 계정을 만들고, 끝나면 지운다.
func tempAccount(t *testing.T, s *Store) int64 {
	t.Helper()

	key := "test-" + randomHex(t, 12)
	res, err := s.db.Exec(`INSERT INTO account (guest_key) VALUES (?)`, key)

	if err != nil {
		t.Fatal(err)
	}

	id, err := res.LastInsertId()

	if err != nil {
		t.Fatal(err)
	}

	t.Cleanup(func() {
		s.db.Exec(`DELETE FROM account WHERE user_id = ?`, id)
	})

	return id
}

func randomHex(t *testing.T, n int) string {
	t.Helper()

	b := make([]byte, n)

	if _, err := rand.Read(b); err != nil {
		t.Fatal(err)
	}

	return hex.EncodeToString(b)
}

func TestLinkAndFind(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempAccount(t, s)
	uid := "google-sub-" + randomHex(t, 8)

	// 붙기 전에는 못 찾아야 한다.
	if _, err := s.FindLinked(ctx, ProviderGoogle, uid); !errors.Is(err, ErrNoLink) {
		t.Fatalf("안 붙였는데 찾았다: %v", err)
	}

	if err := s.Link(ctx, user, ProviderGoogle, uid); err != nil {
		t.Fatalf("못 붙였다: %v", err)
	}

	got, err := s.FindLinked(ctx, ProviderGoogle, uid)

	if err != nil {
		t.Fatalf("붙였는데 못 찾는다: %v", err)
	}

	if got != user {
		t.Fatalf("%d 를 찾아야 하는데 %d 다", user, got)
	}
}

// 같은 것을 두 번 붙이는 것은 성공이다. 클라이언트가 답을 못 받고 다시
// 보내는 일이 흔한데, 그때마다 실패로 보이면 붙일 방법이 없다.
func TestLinkTwiceIsFine(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempAccount(t, s)
	uid := "google-sub-" + randomHex(t, 8)

	if err := s.Link(ctx, user, ProviderGoogle, uid); err != nil {
		t.Fatal(err)
	}

	if err := s.Link(ctx, user, ProviderGoogle, uid); err != nil {
		t.Fatalf("같은 것을 다시 붙였는데 실패했다: %v", err)
	}
}

// 남에게 붙어 있는 구글로 또 붙이려 하면 거절해야 한다. 합치는 것은
// 코드가 정할 일이 아니다.
func TestLinkTakenByOther(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	a := tempAccount(t, s)
	b := tempAccount(t, s)
	uid := "google-sub-" + randomHex(t, 8)

	if err := s.Link(ctx, a, ProviderGoogle, uid); err != nil {
		t.Fatal(err)
	}

	if err := s.Link(ctx, b, ProviderGoogle, uid); !errors.Is(err, ErrLinkTaken) {
		t.Fatalf("남의 것에 붙였는데 %v 다", err)
	}

	// 원래 주인은 그대로여야 한다.
	got, err := s.FindLinked(ctx, ProviderGoogle, uid)

	if err != nil || got != a {
		t.Fatalf("주인이 %d 여야 하는데 %d (%v)", a, got, err)
	}
}

// 한 계정에 구글을 둘 붙일 수는 없다. (user_id, provider) 가 기본키다.
func TestOneProviderPerAccount(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempAccount(t, s)

	if err := s.Link(ctx, user, ProviderGoogle, "sub-a-"+randomHex(t, 8)); err != nil {
		t.Fatal(err)
	}

	if err := s.Link(ctx, user, ProviderGoogle, "sub-b-"+randomHex(t, 8)); !errors.Is(err, ErrLinkTaken) {
		t.Fatalf("한 계정에 구글을 둘 붙였는데 %v 다", err)
	}
}

// 구글과 애플은 같은 계정에 같이 붙을 수 있다.
func TestGoogleAndAppleTogether(t *testing.T) {
	s := linkTestStore(t)

	ctx := context.Background()
	user := tempAccount(t, s)

	if err := s.Link(ctx, user, ProviderGoogle, "g-"+randomHex(t, 8)); err != nil {
		t.Fatal(err)
	}

	if err := s.Link(ctx, user, ProviderApple, "a-"+randomHex(t, 8)); err != nil {
		t.Fatalf("애플을 못 붙였다: %v", err)
	}

	links, err := s.Links(ctx, user)

	if err != nil || len(links) != 2 {
		t.Fatalf("둘이어야 하는데 %v (%v)", links, err)
	}
}
