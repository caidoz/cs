// insamdb 덤프 형식. 규격은 server/dumpformat.md 이고, 기준 구현은
// server/tools/split_dump.py 다. 이 파일은 그것을 Go 로 옮긴 것이다.
//
// 형식을 새로 만들지 않는다는 것이 이 프로젝트의 축이라, 여기서 하는 일은
// LOAD DATA INFILE 의 기본 동작을 그대로 흉내내는 것뿐이다.
package main

import (
	"fmt"
	"hash/crc32"
	"strconv"
	"strings"
)

// 파일 형식 버전. #insamdb 줄에 적힌다.
const FormatVersion = 1

// 게임 안 타임스탬프의 기준점.
//
// 클라이언트의 MC_knlRawTimeStamp() 와 같은 축이어야 한다. 그런데 그 함수는
// mktime() 으로 2000-01-01 을 만든다 (Core.cpp). mktime 은 인자를 지역시로
// 읽으므로, 기준점이 "2000-01-01 00:00:00 UTC" 가 아니라 "기기가 있는 지역의
// 2000-01-01 00:00:00" 이다. 한국이면 UTC 보다 9시간 이르다.
//
// 그래서 기본값이 946652400 (= 2000-01-01 00:00:00 +09:00) 이다. UTC 기준인
// 946684800 을 쓰면 #now 가 32400초 낮게 나가고, NetSetServerTime() 이 그
// 차이를 그대로 오프셋으로 잡아 하트 회복과 일일 초기화가 9시간 밀린다.
//
// 이건 서버를 맞춰서 덮은 것이지 고친 것이 아니다. 클라이언트 쪽 기준점이
// 기기 표준시를 타는 한, 다른 표준시에 있는 유저의 *_ts 는 서로 다른 축에
// 실린다. 제대로 닫으려면 클라이언트가 기준점을 UTC 로 잡아야 하고, 그러면
// 이미 저장된 *_ts 를 전부 옮겨야 한다.
var GameEpoch int64 = 946652400

// 외래키 때문에 부모가 먼저 와야 하는 것들. 여기 없는 표는 뒤에 붙는다.
// split_dump.py 의 TABLE_ORDER 와 같은 순서를 지킨다.
var TableOrder = []string{
	"account",
	"account_link",
	"player",
	"player_castle",
	"player_flag",
	"player_consumable",
	"inventory",
	"inventory_option",
	"inventory_socket",
	"hero",
	"hero_equip",
	"hero_hotkey",
	"hero_skill",
	"hero_skill_slot",
	"crew_slot",
	"quest_progress",
	"game_event",
	"calendar_day",
	"battle_session",
	"battle_enemy",
	"battle_enemy_effect",
	"pvp_house",
	"pvp_house_crew",
	"pvp_house_look",
}

// 서버가 저 혼자 쓰는 표. 유저 덤프에 넣지 않는다.
var serverOnlyTables = map[string]bool{
	"save_conflict_log": true,
	"product":           true,
	"purchase":          true,
	"schema_version":    true,
}

// Table 은 덤프 안의 표 하나다. Rows 의 값은 이스케이프가 풀린 상태이고,
// NULL 은 nil 로 둔다. 빈 문자열과 NULL 은 다른 값이라 구분해야 한다.
type Table struct {
	Name string
	Cols []string
	Rows [][]*string
}

// Dump 는 덤프 한 벌이다.
type Dump struct {
	Schema   int64
	User     int64
	Revision int64
	Written  int64
	Now      int64 // 서버가 실어 보내는 지금 시각. 요청 덤프에는 없다.
	Tables   []Table

	// 로그인 답에만 실린다. 그 뒤로는 클라이언트가 이것을 보낸다.
	Token    string
	TokenExp int64

	// 이 유저가 동의한 약관 판. 0 이면 아직 안 받았다.
	TermsOK int64
	// 탈퇴가 예약돼 있으면 그 시각(게임 타임스탬프). 0 이면 없다.
	DeleteAt int64

	// 결제 결과. /v1/purchase 의 답에만 실린다.
	//
	// 클라이언트는 이것을 보고 대기 장부를 지운다. 지급이 됐든 거절이 됐든
	// "그 거래는 끝났다" 는 뜻이라 둘 다 장부에서 빠져야 한다. 답이 아예
	// 안 오는 것만 다시 보낸다.
	PurchaseState   string
	PurchaseGranted string
}

// DumpError 는 규격 위반이다. 이것이 나오면 400 으로 거절한다.
type DumpError struct{ msg string }

func (e *DumpError) Error() string { return e.msg }

func dumpErr(format string, a ...any) error {
	return &DumpError{msg: fmt.Sprintf(format, a...)}
}

// -----------------------------------------------------------------------------
// 값 표기
// -----------------------------------------------------------------------------

// Escape 는 값 하나를 덤프에 쓸 꼴로 바꾼다. dumpformat.md 의 표 그대로다.
func Escape(s string) string {
	// 대개는 바꿀 것이 없다. 그럴 때 새 문자열을 만들지 않는다.
	if !strings.ContainsAny(s, "\\\t\n\r\x00\x1a") {
		return s
	}

	var b strings.Builder
	b.Grow(len(s) + 8)

	for i := 0; i < len(s); i++ {
		switch s[i] {
		case '\\':
			b.WriteString(`\\`)
		case '\t':
			b.WriteString(`\t`)
		case '\n':
			b.WriteString(`\n`)
		case '\r':
			b.WriteString(`\r`)
		case 0:
			b.WriteString(`\0`)
		case 0x1a:
			b.WriteString(`\Z`)
		default:
			b.WriteByte(s[i])
		}
	}

	return b.String()
}

// Unescape 는 그 반대다. LOAD DATA 와 같이, 모르는 이스케이프는 역슬래시를
// 떼고 글자만 남긴다.
func Unescape(s string) string {
	if !strings.Contains(s, `\`) {
		return s
	}

	var b strings.Builder
	b.Grow(len(s))

	for i := 0; i < len(s); i++ {
		if s[i] != '\\' || i+1 >= len(s) {
			b.WriteByte(s[i])
			continue
		}

		i++

		switch s[i] {
		case '0':
			b.WriteByte(0)
		case 'b':
			b.WriteByte('\b')
		case 'n':
			b.WriteByte('\n')
		case 'r':
			b.WriteByte('\r')
		case 't':
			b.WriteByte('\t')
		case 'Z':
			b.WriteByte(0x1a)
		default:
			b.WriteByte(s[i])
		}
	}

	return b.String()
}

// field 는 이스케이프를 풀되 \N 은 NULL 로 본다.
func field(s string) *string {
	if s == `\N` {
		return nil
	}

	v := Unescape(s)
	return &v
}

// cell 은 그 반대다.
func cell(v *string) string {
	if v == nil {
		return `\N`
	}

	return Escape(*v)
}

// -----------------------------------------------------------------------------
// 읽기
// -----------------------------------------------------------------------------

// ParseDump 는 덤프 텍스트를 읽는다. 규격에 안 맞으면 DumpError 를 준다.
//
// 검사 순서는 split_dump.py 와 같다. 체크섬 -> 행 수 -> 컬럼 수. 앞의 것이
// 틀리면 뒤의 것은 볼 필요가 없기 때문이다.
func ParseDump(text string) (*Dump, error) {
	if strings.Contains(text, "\r\n") {
		return nil, dumpErr("행 구분이 CRLF다. LF여야 한다")
	}

	lines := strings.Split(text, "\n")

	// 마지막 개행 뒤의 빈 줄은 버린다.
	if len(lines) > 0 && lines[len(lines)-1] == "" {
		lines = lines[:len(lines)-1]
	}

	// 블록 사이의 빈 줄은 읽기 좋으라고 넣는 것이라 무시한다.
	// 데이터 줄은 #rows 로 세므로 빈 줄과 헷갈릴 일이 없다.
	skipBlank := func(k int) int {
		for k < len(lines) && strings.TrimSpace(lines[k]) == "" {
			k++
		}
		return k
	}

	d := &Dump{}
	head := map[string]string{}
	i := skipBlank(0)

	// ---- 헤더 ----
	for i < len(lines) && strings.HasPrefix(lines[i], "#") {
		f := strings.Split(lines[i], "\t")
		key := f[0][1:]

		// #end 도 여기서 멈춰야 한다. 표가 하나도 없는 메타행 덤프
		// (로그인 응답이 그렇다) 는 헤더 다음이 바로 #end 라, 이것을
		// 메타행으로 삼켜버리면 체크섬을 아예 안 보고 지나간다.
		if key == "table" || key == "end" {
			break
		}

		if len(f) > 1 {
			head[key] = f[1]
		} else {
			head[key] = ""
		}

		i = skipBlank(i + 1)
	}

	if _, ok := head["insamdb"]; !ok {
		return nil, dumpErr("#insamdb 줄이 없다. insamdb 덤프가 아니다")
	}

	ver, err := strconv.ParseInt(strings.TrimSpace(head["insamdb"]), 10, 64)

	if err != nil || ver != FormatVersion {
		return nil, dumpErr("형식 버전이 %s다. 이 서버는 %d만 안다",
			head["insamdb"], FormatVersion)
	}

	d.Schema = num(head["schema"])
	d.User = num(head["user"])
	d.Revision = num(head["revision"])
	d.Written = num(head["written"])
	d.Now = num(head["now"])

	// ---- 표들 ----
	for {
		i = skipBlank(i)

		if i >= len(lines) {
			break
		}

		line := lines[i]

		if strings.HasPrefix(line, "#end") {
			// 체크섬은 #insamdb 줄부터 #end 직전까지가 대상이다.
			body := strings.Join(lines[:i], "\n") + "\n"
			want := ""

			if f := strings.Split(line, "\t"); len(f) > 1 {
				want = strings.TrimSpace(f[1])
			}

			if want != "" {
				got := fmt.Sprintf("%08x", crc32.ChecksumIEEE([]byte(body)))

				if !strings.EqualFold(got, want) {
					return nil, dumpErr("체크섬이 안 맞는다. 기록=%s 계산=%s", want, got)
				}
			}

			break
		}

		if !strings.HasPrefix(line, "#table") {
			return nil, dumpErr("%d번째 줄: #table이 와야 하는데 %.40q", i+1, line)
		}

		f := strings.Split(line, "\t")

		if len(f) < 2 {
			return nil, dumpErr("%d번째 줄: #table에 이름이 없다", i+1)
		}

		t := Table{Name: strings.TrimSpace(f[1])}
		i++

		if i >= len(lines) || !strings.HasPrefix(lines[i], "#cols") {
			return nil, dumpErr("표 %s: #cols 줄이 없다", t.Name)
		}

		t.Cols = strings.Split(lines[i], "\t")[1:]

		if len(t.Cols) == 0 {
			return nil, dumpErr("표 %s: 컬럼이 하나도 없다", t.Name)
		}

		i++

		if i >= len(lines) || !strings.HasPrefix(lines[i], "#rows") {
			return nil, dumpErr("표 %s: #rows 줄이 없다", t.Name)
		}

		rc := strings.Split(lines[i], "\t")

		if len(rc) < 2 {
			return nil, dumpErr("표 %s: #rows에 개수가 없다", t.Name)
		}

		count, err := strconv.Atoi(strings.TrimSpace(rc[1]))

		if err != nil || count < 0 {
			return nil, dumpErr("표 %s: #rows 값이 이상하다 (%s)", t.Name, rc[1])
		}

		i++

		if i+count > len(lines) {
			return nil, dumpErr("표 %s: %d행이라고 했는데 %d행뿐이다",
				t.Name, count, len(lines)-i)
		}

		for n := 0; n < count; n++ {
			row := lines[i+n]

			// #rows 가 실제보다 크면 다음 블록의 메타행을 데이터로 먹는다.
			// 컬럼 수 오류로 흘려보내면 원인이 안 보이므로 여기서 먼저 잡는다.
			if strings.HasPrefix(row, "#") {
				return nil, dumpErr("표 %s: %d행이라고 했는데 %d행에서 메타행(%s)이 나왔다",
					t.Name, count, n+1, strings.Split(row, "\t")[0])
			}

			// 값 안의 탭은 \t 로 이스케이프돼 있어야 하므로, 탭으로 자른
			// 개수가 컬럼 수와 같아야 한다.
			raw := strings.Split(row, "\t")

			if len(raw) != len(t.Cols) {
				return nil, dumpErr("표 %s %d행: 컬럼이 %d개여야 하는데 %d개다",
					t.Name, n+1, len(t.Cols), len(raw))
			}

			vals := make([]*string, len(raw))

			for k, v := range raw {
				vals[k] = field(v)
			}

			t.Rows = append(t.Rows, vals)
		}

		i += count
		d.Tables = append(d.Tables, t)
	}

	return d, nil
}

func num(s string) int64 {
	v, _ := strconv.ParseInt(strings.TrimSpace(s), 10, 64)
	return v
}

// -----------------------------------------------------------------------------
// 쓰기
// -----------------------------------------------------------------------------

// Build 는 덤프 전문을 만든다. #end 의 체크섬까지 붙인다.
func (d *Dump) Build() string {
	var b strings.Builder

	b.WriteString(d.metaLines())

	for _, t := range d.Tables {
		b.WriteString("\n#table\t")
		b.WriteString(t.Name)
		b.WriteString("\n#cols\t")
		b.WriteString(strings.Join(t.Cols, "\t"))
		b.WriteString("\n#rows\t")
		b.WriteString(strconv.Itoa(len(t.Rows)))
		b.WriteByte('\n')

		for _, row := range t.Rows {
			for k, v := range row {
				if k > 0 {
					b.WriteByte('\t')
				}

				b.WriteString(cell(v))
			}

			b.WriteByte('\n')
		}
	}

	body := b.String()

	return body + fmt.Sprintf("#end\t%08x\n", crc32.ChecksumIEEE([]byte(body)))
}

// BuildMeta 는 메타행만 있는 덤프를 만든다. 로그인 응답과 저장 성공 응답이
// 이 꼴이다. 표가 없을 뿐 형식은 같으므로 클라이언트가 같은 파서로 읽는다.
func (d *Dump) BuildMeta() string {
	body := d.metaLines()

	return body + fmt.Sprintf("#end\t%08x\n", crc32.ChecksumIEEE([]byte(body)))
}

// metaLines 는 머리의 메타행들이다.
//
// #now 는 응답하는 모든 길목에 실어야 한다. 하트 회복과 일일 초기화가 전부
// 이 값 위에 서 있고, 클라이언트의 NetSetServerTime() 이 이것을 기다린다.
func (d *Dump) metaLines() string {
	out := fmt.Sprintf("#insamdb\t%d\n#schema\t%d\n#user\t%d\n#revision\t%d\n#now\t%d\n",
		FormatVersion, d.Schema, d.User, d.Revision, d.Now)

	// 토큰은 로그인 답에만 있다. 없으면 줄 자체를 안 쓴다 — 클라이언트는
	// 모르는 메타행을 그냥 지나치므로 있고 없고가 문제되지 않는다.
	if d.Token != "" {
		out += fmt.Sprintf("#token\t%s\n#token_exp\t%d\n", d.Token, d.TokenExp)
	}

	// 이 유저가 동의한 약관 판. 클라이언트는 이것과 지금 판을 견줘서
	// 낮으면 약관을 다시 띄운다.
	if d.TermsOK > 0 {
		out += fmt.Sprintf("#terms_ok\t%d\n", d.TermsOK)
	}

	// 탈퇴가 걸려 있으면 반드시 알려야 한다. 모르고 지나가면 그날 계정이
	// 사라진다. 취소할 기회를 주는 것이 이 한 줄이다.
	if d.DeleteAt > 0 {
		out += fmt.Sprintf("#delete_at\t%d\n", d.DeleteAt)
	}

	if d.PurchaseState != "" {
		out += fmt.Sprintf("#purchase\t%s\n#granted\t%s\n",
			d.PurchaseState, d.PurchaseGranted)
	}

	return out
}
