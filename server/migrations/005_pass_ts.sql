-- schema 4 -> 5 : 패스 기간을 게임 타임스탬프로
--
--     mysql -u insam -p insam < server/migrations/005_pass_ts.sql
--
-- 004 에서 패스 기간을 DATETIME 으로 만들었는데, 그러면 클라이언트에 안 간다.
-- 이 스키마의 규칙이 파일 맨 위에 적혀 있다.
--
--     *_ts  : 게임 안 타임스탬프(BIGINT). 덤프에 실려 클라이언트로 간다
--     *_at  : 운영용 DATETIME. 사람이 보는 것이고 덤프에서 빠진다
--
-- 패스는 게임이 "지금 켜져 있는가" 를 봐야 하는 값이라 앞쪽이다. 규칙을
-- 어긴 쪽을 고친다.
--
-- 아직 아무도 패스를 안 샀으므로 값을 옮길 것이 없다.

ALTER TABLE player
    DROP COLUMN heart_pass_until,
    DROP COLUMN growth_pass_until,
    ADD COLUMN heart_pass_ts  BIGINT NOT NULL DEFAULT 0 AFTER coin,
    ADD COLUMN growth_pass_ts BIGINT NOT NULL DEFAULT 0 AFTER heart_pass_ts;

INSERT INTO schema_version (version) VALUES (5)
    ON DUPLICATE KEY UPDATE applied_at = applied_at;
