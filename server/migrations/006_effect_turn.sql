-- schema 5 -> 6 : 상태이상의 남은 턴 수와 히어로 상태이상
--
--     mysql -u insam -p insam < server/migrations/006_effect_turn.sql
--
-- [남은 턴 수]
--
-- battle_enemy_effect 는 remain(프레임)만 담고 있었다. 그런데 화면에 숫자로
-- 보이는 것도, 턴이 돌 때마다 하나씩 줄어 상태이상이 풀리는 기준도 턴 수다.
-- 둘은 다른 값이다. 그래서 재접속하면 아이콘은 남는데 숫자가 0 으로 돌아가고,
-- 다음 턴에 곧바로 풀렸다.
--
-- [히어로 상태이상]
--
-- 적의 것만 담고 히어로 것은 아예 안 담았다. CHARDATA 에 buff/debuf 칸이
-- 주석으로 막혀 있었고 "RefreshStat 한 번 하면 다시 채워지는 임시값" 이라는
-- 이유가 적혀 있었다. 버프는 장비와 스킬에서 다시 계산되니 맞는 말이지만,
-- 상태이상은 맞은 결과라 어디서도 다시 나오지 않는다. 그래서 재접속하면
-- 히어로만 멀쩡해졌다.
--
-- 적 쪽과 달리 buff 를 담지 않는다. 히어로의 버프는 정말로 다시 계산된다.
--
-- 옛 행에는 remain_turn 이 없으므로 0 이 들어간다. 클라이언트가 그때는 1 턴으로
-- 읽는다. 0 으로 두면 다음 턴에 곧바로 풀려 걸려 있던 것이 사라지기 때문이다.

ALTER TABLE battle_enemy_effect
    ADD COLUMN remain_turn TINYINT UNSIGNED NOT NULL DEFAULT 0 AFTER owner;

CREATE TABLE hero_effect (
    user_id     BIGINT UNSIGNED   NOT NULL,
    hero_idx    TINYINT UNSIGNED  NOT NULL,  -- 0=로빈 1=디아나 2=맥스
    eff_idx     SMALLINT UNSIGNED NOT NULL,  -- TOTALDEBUF 안의 번호
    remain      INT               NOT NULL,  -- 남은 프레임
    owner       TINYINT UNSIGNED  NOT NULL DEFAULT 0,  -- 건 사람
    remain_turn TINYINT UNSIGNED  NOT NULL DEFAULT 0,  -- 남은 턴 수
    PRIMARY KEY (user_id, hero_idx, eff_idx),
    CONSTRAINT fk_heffect_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO schema_version (version) VALUES (6)
    ON DUPLICATE KEY UPDATE applied_at = applied_at;
