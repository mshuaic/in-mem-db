SELECT *
FROM executable('fifo 2564672921035037144 342000', TabSeparated, 'block_number UInt64, tx_index UInt16, src UInt64, des UInt64, tainted_value UInt128, tainted_src UInt128, tainted_des UInt128', (
    SELECT *
    FROM benchmark.upbithack
    WHERE (block_number >= 9007863) AND (block_number <= 9124596)
    ORDER BY (block_number, transaction_index) ASC
)) as t1
ANTI LEFT JOIN
(
  SELECT *
    FROM executable('fifo.py 2564672921035037144 342000', TabSeparated, 'block_number UInt64, tx_index UInt16, src UInt64, des UInt64, tainted_value UInt128, tainted_src UInt128, tainted_des UInt128', (
        SELECT *
        FROM benchmark.upbithack
        WHERE (block_number >= 9007863) AND (block_number <= 9124596)
        ORDER BY (block_number, transaction_index) ASC
    ))
) as t2 USING (block_number, tx_index, src, des, tainted_value, tainted_src, tainted_des)
FORMAT PrettyCompact
