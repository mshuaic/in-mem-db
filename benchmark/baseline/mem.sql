DROP TABLE IF EXISTS benchmark.upbithack;
CREATE TABLE benchmark.upbithack
(
    `block_number` UInt32,
    `transaction_index` UInt16,
    `src` UInt64,
    `des` UInt64,
    `value` UInt128,
    `balance` UInt128
)
ENGINE = Memory AS
SELECT
    toUInt32(block_number),
    toUInt16(transaction_index),
    cityHash64(from_address),
    cityHash64(to_address),
    toUInt128(value),
    toUInt128(balance)
FROM ethereum.tx_balance
WHERE (block_number >= 9007863) AND (block_number <= 10364596) AND (balance > 0) AND (value > 0)
ORDER BY (block_number, transaction_index) ASC;
