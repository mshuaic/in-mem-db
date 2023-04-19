#!/usr/bin/env python3

import sys
import re
from collections import Counter
import traceback

if __name__ == "__main__":
    fd = open("/tmp/debug.log", "w")
    seed = int(sys.argv[1])
    amount = int(sys.argv[2]) * 10**18
    tainted = Counter({seed: amount})
    # tainted_txs = []

    try:
        for line in sys.stdin:
            line_split = re.split(r"\t+", line.strip())
            blk, txindex, src, des, value, balance = line_split
            src = int(src)
            des = int(des)
            balance = int(balance)
            value = int(value)
            if src not in tainted.keys() or tainted[src] == 0:
                continue

            taint_amount = min(value, tainted[src])
            if taint_amount == 0:
                continue
            tainted[des] += taint_amount
            tainted[src] -= taint_amount
            if tainted[src] == 0:
                del tainted[src]

            print(
                "\t".join(
                    map(
                        str,
                        [
                            blk,
                            txindex,
                            src,
                            des,
                            taint_amount,
                            tainted[src],
                            tainted[des],
                        ],
                    )
                )
                + "\n",
                end="",
            )
            sys.stdout.flush()

    except Exception as e:
        traceback.print_exc(file=fd)
        fd.close()
