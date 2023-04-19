#include <boost/multiprecision/cpp_int.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace boost::multiprecision;
using namespace boost::algorithm;
using namespace std;

struct MyHash {
  uint64_t operator()(const uint64_t& k) const {
    return k;
  }
};

int main(int argc, char **argv) {
  uint64_t seed = stoull(argv[1]);
  uint128_t amount = uint128_t(argv[2]) * uint128_t(1e18);

  uint32_t blk_num;
  uint16_t tx_index;
  uint64_t src;
  uint64_t des;
  uint128_t value;
  uint128_t balance;

  cin.tie(nullptr);
  cin.sync_with_stdio(false);

  cout.tie(nullptr);
  cout.sync_with_stdio(false);

  unordered_map<uint64_t, uint128_t, MyHash> tainted{{seed, amount}};

  while (cin >> blk_num >> tx_index  >> src >> des >> value >> balance) {
    if (tainted.contains(src) == false || tainted[src] == 0) {
      continue;
    }

    uint128_t taint_amount = min(value, tainted[src]);
    if (taint_amount == 0)
      continue;
    tainted[des] += taint_amount;
    tainted[src] -= taint_amount;

    cout << blk_num << "\t"
         << tx_index << "\t"
         << src << "\t"
         << des << "\t"
         << taint_amount << "\t"
         << tainted[src] << "\t"
         << tainted[des] << endl;
    cout.flush();
    if (tainted[src] == 0)
      tainted.erase(src);
  }

  return 0;
}
