package main

import (
	"os"
	"strings"
	"testing"
)

// 진짜 세이브 파일로 돌린다. 경로는 INSAM_TEST_DUMP 로 준다.
// 없으면 건너뛴다 — 이 파일은 기기마다 다른 곳에 있다.
func TestParseRealSave(t *testing.T) {
	path := os.Getenv("INSAM_TEST_DUMP")

	if path == "" {
		t.Skip("INSAM_TEST_DUMP 가 없다")
	}

	raw, err := os.ReadFile(path)

	if err != nil {
		t.Fatalf("파일을 못 읽었다: %v", err)
	}

	d, err := ParseDump(string(raw))

	if err != nil {
		t.Fatalf("파싱 실패: %v", err)
	}

	if d.User == 0 || d.Revision == 0 {
		t.Fatalf("#user=%d #revision=%d — 둘 다 있어야 한다", d.User, d.Revision)
	}

	total := 0

	for _, tb := range d.Tables {
		total += len(tb.Rows)
	}

	t.Logf("user=%d revision=%d 표 %d개 행 %d개",
		d.User, d.Revision, len(d.Tables), total)

	if len(d.Tables) == 0 {
		t.Fatal("표가 하나도 없다")
	}
}

// 만든 것을 다시 읽으면 같아야 한다. 체크섬도 이때 같이 검증된다
// (ParseDump 가 #end 를 확인하므로).
func TestRoundTrip(t *testing.T) {
	path := os.Getenv("INSAM_TEST_DUMP")

	if path == "" {
		t.Skip("INSAM_TEST_DUMP 가 없다")
	}

	raw, err := os.ReadFile(path)

	if err != nil {
		t.Fatal(err)
	}

	first, err := ParseDump(string(raw))

	if err != nil {
		t.Fatal(err)
	}

	second, err := ParseDump(first.Build())

	if err != nil {
		t.Fatalf("우리가 만든 덤프를 우리가 못 읽는다: %v", err)
	}

	if len(first.Tables) != len(second.Tables) {
		t.Fatalf("표 개수가 %d -> %d 로 변했다", len(first.Tables), len(second.Tables))
	}

	for i := range first.Tables {
		a, b := first.Tables[i], second.Tables[i]

		if a.Name != b.Name {
			t.Fatalf("%d번째 표 이름이 %s -> %s", i, a.Name, b.Name)
		}

		if strings.Join(a.Cols, ",") != strings.Join(b.Cols, ",") {
			t.Fatalf("표 %s 의 컬럼이 변했다", a.Name)
		}

		if len(a.Rows) != len(b.Rows) {
			t.Fatalf("표 %s 의 행이 %d -> %d", a.Name, len(a.Rows), len(b.Rows))
		}

		for r := range a.Rows {
			for c := range a.Rows[r] {
				x, y := a.Rows[r][c], b.Rows[r][c]

				if (x == nil) != (y == nil) {
					t.Fatalf("표 %s %d행 %s: NULL 여부가 변했다", a.Name, r+1, a.Cols[c])
				}

				if x != nil && *x != *y {
					t.Fatalf("표 %s %d행 %s: %q -> %q", a.Name, r+1, a.Cols[c], *x, *y)
				}
			}
		}
	}
}

// 값 안에 특수문자가 있어도 왕복해야 한다. 이스케이프가 깨지면 컬럼 수가
// 어긋나면서 저장이 통째로 400 이 되므로, 여기가 형식의 급소다.
func TestEscapeRoundTrip(t *testing.T) {
	nick := "폴\t립\n두\\줄\r끝"
	empty := ""

	d := &Dump{
		Schema: 1, User: 1001, Revision: 42, Now: 1,
		Tables: []Table{{
			Name: "player",
			Cols: []string{"user_id", "nickname", "memo", "gone"},
			Rows: [][]*string{{strptr("1001"), &nick, &empty, nil}},
		}},
	}

	got, err := ParseDump(d.Build())

	if err != nil {
		t.Fatalf("우리가 만든 것을 못 읽는다: %v", err)
	}

	row := got.Tables[0].Rows[0]

	if *row[1] != nick {
		t.Fatalf("닉네임이 %q -> %q", nick, *row[1])
	}

	if row[2] == nil || *row[2] != "" {
		t.Fatal("빈 문자열이 NULL 로 변했다. 둘은 다른 값이다")
	}

	if row[3] != nil {
		t.Fatal("NULL 이 빈 문자열로 변했다")
	}
}

// 체크섬이 안 맞으면 잘린 파일이다. 받아들이면 안 된다.
func TestChecksumMismatch(t *testing.T) {
	d := &Dump{Schema: 1, User: 7, Revision: 1}
	text := strings.Replace(d.BuildMeta(), "#user\t7", "#user\t8", 1)

	if _, err := ParseDump(text); err == nil {
		t.Fatal("체크섬이 틀렸는데 통과했다")
	}
}

// #rows 가 실제보다 크면 다음 블록의 메타행을 데이터로 먹는다.
// 컬럼 수 오류로 흘려보내지 않고 여기서 잡아야 원인이 보인다.
func TestRowCountLie(t *testing.T) {
	body := "#insamdb\t1\n#schema\t1\n#user\t1\n#revision\t1\n" +
		"\n#table\tplayer\n#cols\tuser_id\n#rows\t3\n1\n" +
		"\n#table\thero\n#cols\tuser_id\n#rows\t0\n"

	_, err := ParseDump(body + "#end\t00000000\n")

	if err == nil {
		t.Fatal("행 수가 거짓인데 통과했다")
	}

	if !strings.Contains(err.Error(), "메타행") {
		t.Fatalf("메타행을 먹었다고 말해야 하는데: %v", err)
	}
}

// 행 구분은 LF 다. CRLF 로 들어오면 그 시점에 이미 규격 위반이다.
func TestCRLFRejected(t *testing.T) {
	d := &Dump{Schema: 1, User: 1, Revision: 1}

	if _, err := ParseDump(strings.ReplaceAll(d.BuildMeta(), "\n", "\r\n")); err == nil {
		t.Fatal("CRLF 인데 통과했다")
	}
}

func strptr(s string) *string { return &s }
