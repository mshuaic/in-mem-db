#!/bin/bash

CLICKHOUSE_CLIENT=/usr/bin/clickhouse-client
sql="
  SELECT \
    block_number, \
    transaction_index, \
    from_address, \
    to_address, \
    value, \
    balance \
  FROM ethereum.tx_balance \
  WHERE value > 0  AND balance > 0 \
  LIMIT 100000 \
"

$CLICKHOUSE_CLIENT \
    --query="$sql" \
    --format=CSV
