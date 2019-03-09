#include <bitset>
#include <iostream>
#include <cmath>

std::bitset<64> hoge(unsigned long long x) {
  const unsigned long long start = (x / 4) * 4;
  std::bitset<64> ans(0);
  for (unsigned long long i = start; i <= x; ++i) {
    ans = ans ^ std::bitset<64>(i);
  }
  return ans;
}

int main() {
  const unsigned int bit = 64;
  unsigned long long a, b;
  std::cin >> a >> b;

  std::bitset<bit> ans(0);
  if (a == 0) {
    ans = hoge(b);
  } else {
    std::bitset<64> a_hoge = hoge(a - 1);
    std::bitset<64> b_hoge = hoge(b);
    ans = a_hoge ^ b_hoge;
  }

  std::cout << ans.to_ullong() << std::endl;

  return 0;
}
