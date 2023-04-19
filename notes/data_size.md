block_number: uint32
transaction_index: uint16
src, des: 20-byte, 273238844 addresses are used. we can use hash() to squeeze the space
* 32bit hash is too small
* 64bit hash is ok

value: uint256 
*  0x9c81f44c29ff0226f835cd0a8a2f2a7eca6db52a711f8211b566fd15d3e0e8d4 │ 0x5abfec25f74cd88437631a7731906932776356f9 │ 11901484239480000000000000 
* max < uint128
balance: uint256
* 0x00000000219ab540356cbb839cbe05303d7705fa │ 17906199168232416675747075 │
* max < uint128

trace has 1423179982 rows wher value > 0

* it takes 100 gb


