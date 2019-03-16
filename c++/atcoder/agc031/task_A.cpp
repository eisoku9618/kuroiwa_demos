#include <iostream>
#include <map>

int main() {
  const unsigned long mod = 1000000000 + 7;
  unsigned long n;
  std::string s;
  std::cin >> n;
  std::cin >> s;

  std::map<char, unsigned long> alphabet_map;
  for (unsigned long i = 0; i < n; ++i) {
    alphabet_map[s[i]] += 1;
  }

  unsigned long sum = 1;
  for (const auto pair : alphabet_map) {
    sum *= ((pair.second + 1) % mod);
    sum %= mod;
  }

  std::cout << (sum - 1) % mod << std::endl;
  return 0;
}
