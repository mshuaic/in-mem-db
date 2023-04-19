SELECT *
FROM benchmark.all_data
ORDER BY (block_number, transaction_index) ASC
FORMAT RowBinary
