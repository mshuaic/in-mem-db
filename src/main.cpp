#include <boost/multiprecision/cpp_int.hpp>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

#pragma pack(push, 1)
struct Row {
  uint32_t blk_num;
  uint16_t tx_index;
  uint64_t src;
  uint64_t des;
  boost::multiprecision::uint128_t value;
  boost::multiprecision::uint128_t balance; //src balance
};
#pragma pack(pop)

using namespace boost::multiprecision;
using namespace std;

struct nohash {
  uint64_t operator()(const uint64_t &k) const { return k; }
};

int main(int argc, char** argv) {
  uint64_t seed = stoull(argv[1]);
  uint128_t amount = uint128_t(argv[2]) * uint128_t(1e18);

  // the file is in /dev/shm
  const char* filename = argv[3];
  int fd = open(filename, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  size_t size = st.st_size;
  Row* row = (Row*)mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
  Row* end = row + size/sizeof(Row);

  unordered_map<uint64_t, uint128_t, nohash> tainted{{seed, amount}};

  while (row < end) {
    if (tainted.contains(row->src) == false || tainted[row->src] == 0) {
      row += 1;
      continue;
    }

    uint128_t taint_amount = min(row->value, tainted[row->src]);
    if (taint_amount == 0)
      continue;
    tainted[row->des] += taint_amount;
    tainted[row->src] -= taint_amount;
    if (tainted[row->src] == 0)
      tainted.erase(row->src);

    std::cout
      << row->blk_num << "\t"
      << row->tx_index << "\t"
      << row->src << "\t"
      << row->des << "\t"
      << taint_amount << "\t"
      << tainted[row->src] << "\t"
      << tainted[row->des] << endl;
    row += 1;
  }

  munmap(row, size);
  close(fd);

  return 0;
}


