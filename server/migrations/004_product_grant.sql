-- schema 3 -> 4 : 상품 구성을 다시 짰다
--
--     mysql -u insam -p insam < server/migrations/004_product_grant.sql
--
-- 왜 바꾸는가
-- ---------------------------------------------------------------------------
-- 003 은 "한 상품이 한 재화를 준다" 였다. 스타터팩이 들어오면서 그 전제가
-- 깨졌다 - 코인도 주고 하트도 주고 패스도 건다. 그래서 지급 내역을 상품에서
-- 떼어 따로 둔다.
--
-- 그리고 1 인 1 회 상품(스타터팩, 영구 확장)을 막을 자리가 없었다.
-- uq_order 는 "같은 거래" 를 막을 뿐, "같은 사람이 다른 거래로 또 사는 것" 은
-- 안 막는다. product.kind 가 noncon 이면 서버가 그것도 막는다.
--
-- 003 을 넣은 뒤 실제 결제가 없었으므로 purchase 를 비우고 다시 만든다.
-- 결제 기록이 들어간 뒤에는 이렇게 하면 안 된다.

-- ---- 상품 ----
--
-- 무엇을 주는지가 여기서 빠졌다. product_grant 로 옮겼다.
ALTER TABLE product
    DROP COLUMN grant_kind,
    DROP COLUMN grant_amount;

-- ---- 지급 내역 ----
--
-- 상품 하나가 여러 줄을 가질 수 있다. 스타터팩이 그렇다.
--
-- kind 가 무엇을 뜻하는지는 서버의 grantColumn / grantPass 지도에 있다.
-- 여기 문자열을 SQL 에 이어붙이지 않는다 - 그 지도에 없는 이름은 못 준다.
CREATE TABLE product_grant (
    product_id   VARCHAR(64)     NOT NULL,
    seq          SMALLINT        NOT NULL,  -- 주는 차례. 화면에 그대로 쓴다
    grant_kind   VARCHAR(16)     NOT NULL,  -- coin/heart/gold/... 또는 pass_*
    grant_amount BIGINT          NOT NULL,  -- 재화면 수량, 패스면 날수
    PRIMARY KEY (product_id, seq),
    CONSTRAINT fk_grant_product FOREIGN KEY (product_id)
        REFERENCES product (product_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- ---- 원장 ----
--
-- 지급 내역을 글자로 박아 둔다("coin:2000,heart:300"). 표로 또 나누지 않는
-- 이유는, 이것이 계산에 쓰이는 값이 아니라 나중에 사람이 읽을 기록이기
-- 때문이다. 환불 문의가 오면 이 줄을 그대로 보면 된다.
--
-- 상품 표를 나중에 고쳐도 이 값은 안 변해야 한다. 그래서 여기 박는다.
ALTER TABLE purchase
    DROP COLUMN grant_kind,
    DROP COLUMN grant_amount,
    ADD COLUMN granted VARCHAR(255) NOT NULL DEFAULT '' AFTER state;

-- 1 인 1 회 상품을 막는 자물쇠.
--
-- state 를 넣지 않는 것에 주의. 거절당한 기록이 있으면 다시 못 사게 되면
-- 안 되므로, 거절은 order_id 를 비워 이 자물쇠를 피해 간다... 는 방식은
-- 헷갈린다. 대신 서버가 사기 전에 granted 상태를 확인한다. 이 키는 그
-- 확인이 경합에 졌을 때를 받아내는 두 번째 그물이다.
ALTER TABLE purchase
    ADD KEY idx_purchase_once (user_id, product_id, state);

-- ---- 패스 ----
--
-- 자동갱신 구독이 아니다. 30 일권을 사면 이 시각이 30 일 뒤로 밀린다.
-- 남아 있는 동안 또 사면 남은 기간에 이어 붙는다.
--
-- 구독으로 하지 않는 이유. 갱신 상태를 스토어에서 계속 받아와야 하고
-- (구글의 RTDN, 애플의 App Store Server Notifications), 환불과 유예기간까지
-- 다뤄야 한다. 30 일권은 지금 만든 것을 그대로 쓴다.
ALTER TABLE player
    ADD COLUMN heart_pass_until  DATETIME NULL AFTER coin,
    ADD COLUMN growth_pass_until DATETIME NULL AFTER heart_pass_until;

-- ---- 상품 다시 담기 ----
DELETE FROM purchase;
DELETE FROM product;

INSERT INTO product (product_id, kind, memo) VALUES
    ('coin_01','consumable','코인 1,000'),
    ('coin_02','consumable','코인 2,200'),
    ('coin_03','consumable','코인 6,000'),
    ('coin_04','consumable','코인 25,000'),
    ('coin_05','consumable','코인 65,000'),
    ('coin_06','consumable','코인 140,000'),
    ('heart_01','consumable','하트 100'),
    ('heart_02','consumable','하트 300'),
    ('heart_03','consumable','하트 1,000'),
    ('heart_04','consumable','하트 5,000'),
    ('heart_05','consumable','하트 15,000'),
    ('heart_06','consumable','하트 50,000'),
    ('pass_heart_30','consumable','하트 패스 30일'),
    ('pass_growth_30','consumable','성장 패스 30일'),
    ('starter','noncon','초심자 패키지 (1인 1회)'),
    ('inven_20','noncon','가방 +20칸 (1인 1회)');

INSERT INTO product_grant (product_id, seq, grant_kind, grant_amount) VALUES
    ('coin_01',0,'coin',1000),
    ('coin_02',0,'coin',2200),
    ('coin_03',0,'coin',6000),
    ('coin_04',0,'coin',25000),
    ('coin_05',0,'coin',65000),
    ('coin_06',0,'coin',140000),
    ('heart_01',0,'heart',100),
    ('heart_02',0,'heart',300),
    ('heart_03',0,'heart',1000),
    ('heart_04',0,'heart',5000),
    ('heart_05',0,'heart',15000),
    ('heart_06',0,'heart',50000),
    ('pass_heart_30',0,'pass_heart',30),
    ('pass_growth_30',0,'pass_growth',30),
    ('starter',0,'coin',2000),
    ('starter',1,'heart',300),
    ('inven_20',0,'inven',20);

INSERT INTO schema_version (version) VALUES (4)
    ON DUPLICATE KEY UPDATE applied_at = applied_at;
