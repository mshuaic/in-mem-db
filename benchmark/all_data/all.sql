DROP TABLE IF EXISTS benchmark.all_data;
CREATE TABLE benchmark.all_data
(
    `block_number` UInt32,
    `transaction_index` UInt16,
    `src` UInt64,
    `des` UInt64,
    `value` UInt128,
    `balance` UInt128
)
ENGINE = MergeTree
ORDER BY (block_number, transaction_index) AS
SELECT
    toUInt32(block_number),
    toUInt16(transaction_index),
    cityHash64(from_address),
    cityHash64(to_address),
    toUInt128(value),
    toUInt128(balance)
FROM ethereum.tx_balance
WHERE (balance > 0) AND (value > 0);
