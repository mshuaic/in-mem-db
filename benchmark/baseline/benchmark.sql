DROP TABLE IF EXISTS benchmark.fifo;
CREATE TABLE benchmark.fifo
(
    `block_number` UInt32,
    `transaction_index` UInt16,
    `src` UInt64,
    `des` UInt64,
    `tainted_value` UInt128,
    `tainted_src` UInt128,
    `tainted_des` UInt128
)
ENGINE = Executable('benchmark 2564672921035037144 342000', TabSeparated, (
    SELECT *
    FROM benchmark.upbithack
    ORDER BY (block_number, transaction_index) ASC
))
SETTINGS command_read_timeout = 100000, command_write_timeout = 100000;
