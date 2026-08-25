// 저장을 지켜본다. 아직 막지는 않는다.
//
// 지금 구조는 클라이언트를 믿는다. 골드 999999999 를 보내면 그대로 들어간다.
// 이것은 버그가 아니라 설계의 성질이고, 완전한 서버 권위는 전투·룰렛·가챠를
// 전부 서버로 옮기는 일이라 지금 하지 않는다.
//
// 그래서 단계로 좁힌다. 이 파일은 그 첫 걸음 — 기록만 남긴다.
//
// 왜 곧바로 막지 않는가.
//
//   - 단조성 검사(줄어들 수 없는 값이 줄면 거른다)를 지금 걸 수 없다.
//     NewGame() 이 memset(&robin, 0, ...) 으로 전부 0 으로 민다. 새 게임을
//     한 유저는 lv 도 playtime 도 내려간다. 거르면 그 사람이 막힌다.
//   - 델타 상한도 마찬가지다. 상한을 잘못 잡으면 정상 유저가 게임을 못 하게
//     되고, 그 사실을 아무도 모른 채 이탈만 는다.
//
// 그러니 먼저 본다. 여기 쌓인 것이 기준을 만들 재료다. 기준이 서면 그때
// 클램프로 넘어간다 — 거절이 아니라 클램프인 이유는, 잘못 잡았을 때 유저를
// 막지 않기 위해서다.
package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"strconv"
	"strings"
)

// 지켜보는 칸들. 줄어들 수 없어 보이는 것과, 재화다.
var watchCols = []string{
	"lv", "playtime", "max_inven",
	"gold", "heart", "medal", "star", "hammer", "coin",
}

// 줄어들면 눈에 띄어야 하는 것들. 막지는 않는다 — 새 게임이면 정상이다.
var watchMonotonic = map[string]bool{
	"lv": true, "playtime": true, "max_inven": true,
}

// 이만큼 늘면 사람 손으로는 어려운 수준이다. 넉넉히 잡았다.
// 여기 걸린 것을 모아 보고 진짜 기준을 정한다.
var watchJump = map[string]int64{
	"gold": 100000000, "heart": 10000, "medal": 1000000,
	"star": 1000000, "hammer": 1000000, "coin": 1000000,
}

// WatchSave 는 이번 저장이 지난번과 얼마나 다른지 본다.
//
// 막지 않는다. 눈에 띄는 것만 한 줄 남긴다. 실패해도 저장을 흔들지 않는다.
func (s *Store) WatchSave(ctx context.Context, tx *sql.Tx, userID int64, player *Table) {
	meta := s.schema.Tables["player"]

	if meta == nil {
		return
	}

	cols := make([]string, 0, len(watchCols))

	for _, c := range watchCols {
		if meta.Has(c) {
			cols = append(cols, c)
		}
	}

	if len(cols) == 0 {
		return
	}

	quoted := make([]string, len(cols))

	for i, c := range cols {
		quoted[i] = "`" + c + "`"
	}

	q := fmt.Sprintf(
		"SELECT %s, TIMESTAMPDIFF(SECOND, updated_at, NOW()) FROM `player` WHERE user_id = ?",
		strings.Join(quoted, ", "))

	vals := make([]int64, len(cols))
	ptr := make([]any, len(cols)+1)

	for i := range vals {
		ptr[i] = &vals[i]
	}

	var elapsed int64
	ptr[len(cols)] = &elapsed

	if err := tx.QueryRowContext(ctx, q, userID).Scan(ptr...); err != nil {
		// 첫 저장이면 지난 행이 없다. 견줄 것이 없으니 그냥 지나간다.
		return
	}

	// 들어온 값을 이름으로 찾는다. 컬럼 순서는 클라이언트가 정한다.
	sent := map[string]int64{}

	for i, c := range player.Cols {
		if _, ok := watchJump[c]; !ok && !watchMonotonic[c] {
			continue
		}

		if v := player.Rows[0][i]; v != nil {
			if n, err := strconv.ParseInt(strings.TrimSpace(*v), 10, 64); err == nil {
				sent[c] = n
			}
		}
	}

	notes := []string{}

	for i, c := range cols {
		now, ok := sent[c]

		if !ok {
			continue
		}

		was := vals[i]
		diff := now - was

		if watchMonotonic[c] && diff < 0 {
			notes = append(notes, fmt.Sprintf("%s %d->%d", c, was, now))
			continue
		}

		if limit, ok := watchJump[c]; ok && diff > limit {
			notes = append(notes, fmt.Sprintf("%s +%d(%d초)", c, diff, elapsed))
		}
	}

	if len(notes) > 0 {
		log.Printf("watch: user=%d %s", userID, strings.Join(notes, " "))
	}
}
