-- schema 2 -> 3 : 결제
--
-- 살아 있는 DB 에 거는 것이다. schema.sql 은 처음부터 만드는 스크립트라
-- 이미 도는 서버에는 못 쓴다. 그래서 바뀐 것만 따로 적어 둔다.
--
--     mysql -u insam -p insam < server/migrations/003_purchase.sql
--
-- 되돌리려면 아래 두 표를 지우고 schema_version 에서 3 을 빼면 된다.
-- 결제 기록이 들어간 뒤에는 되돌리지 마라.

-- =============================================================================
-- 결제
-- =============================================================================
--
-- 돈이 오간다. 다른 표와 지켜야 할 것이 다르다.
--
--   1. 한 번 산 것은 한 번만 준다. 같은 영수증이 두 번 와도 마찬가지다.
--      네트워크는 재시도하고 스토어도 재시도한다. 두 번 오는 것이 정상이다.
--      그래서 uq_order 가 이 표의 심장이다.
--
--   2. 무엇을 얼마나 줄지는 서버가 정한다. 클라이언트가 보낸 값을 쓰면
--      영수증 없이 "코인 백만 개짜리를 샀다"고 말하는 것을 막을 수 없다.
--
--   3. 기록은 안 지운다. 환불과 문의가 들어온다. 탈퇴해도 남긴다
--      (전자상거래법상 대금결제 기록은 5년 보존이다).

-- 상품 목록. 스토어의 상품 ID 와 "무엇을 얼마나 주는가" 를 잇는다.
--
-- 값(가격)은 여기 없다. 가격은 스토어가 정하고 나라마다 다르다. 서버가
-- 아는 것은 "이 상품 ID 가 팔리면 무엇을 준다" 뿐이다.
CREATE TABLE product (
    product_id   VARCHAR(64)     NOT NULL,  -- 스토어에 등록한 그 ID 와 같아야 한다
    kind         VARCHAR(16)     NOT NULL,  -- consumable / noncon / subscription
    grant_kind   VARCHAR(16)     NOT NULL,  -- coin / gold / heart / star / hammer
    grant_amount BIGINT          NOT NULL,
    enabled      TINYINT(1)      NOT NULL DEFAULT 1,
    memo         VARCHAR(128)    NULL,
    created_at   DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (product_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 결제 원장. 한 줄이 거래 하나다.
--
-- grant_kind/grant_amount 를 여기에도 박아 둔다. product 표를 나중에 고쳐도
-- "그때 무엇을 줬는가" 는 안 변해야 한다. 환불 처리할 때 그 값이 필요하다.
CREATE TABLE purchase (
    seq          BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
    user_id      BIGINT UNSIGNED NOT NULL,
    platform     VARCHAR(16)     NOT NULL,  -- ios / android
    product_id   VARCHAR(64)     NOT NULL,
    order_id     VARCHAR(128)    NOT NULL,  -- 스토어가 준 거래 고유값
    state        VARCHAR(16)     NOT NULL,  -- granted / rejected / refunded
    grant_kind   VARCHAR(16)     NOT NULL,
    grant_amount BIGINT          NOT NULL,
    reason       VARCHAR(64)     NULL,      -- 거절이면 왜인지
    receipt      TEXT            NULL,      -- 스토어가 준 원문. 대조에 쓴다
    created_at   DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    granted_at   DATETIME        NULL,
    PRIMARY KEY (seq),

    -- 두 번 주지 않는 자물쇠. 같은 스토어의 같은 거래는 하나뿐이다.
    UNIQUE KEY uq_order (platform, order_id),

    KEY idx_purchase_user (user_id, created_at)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 시험용 상품. 실제 상품은 스토어에 등록한 뒤 여기에 넣는다.
INSERT INTO product (product_id, kind, grant_kind, grant_amount, memo) VALUES
    ('test_coin_100',  'consumable', 'coin',  100,  '시험용'),
    ('test_gold_10k',  'consumable', 'gold',  10000, '시험용'),
    ('test_heart_50',  'consumable', 'heart', 50,   '시험용');

INSERT INTO schema_version (version) VALUES (3)
    ON DUPLICATE KEY UPDATE applied_at = applied_at;
