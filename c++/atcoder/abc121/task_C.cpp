#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
  unsigned long n, m;
  std::cin >> n >> m;

  // std::map<unsigned long long, unsigned long long> ab_map;
  // for (size_t i = 0; i < n; ++i) {
  //   unsigned long long a, b;
  //   std::cin >> a >> b;
  //   ab_map.insert(std::make_pair(a, b));
  // }
  std::vector<std::pair<unsigned long long, unsigned long long>> ab_map;
  for (size_t i = 0; i < n; ++i) {
    unsigned long long a, b;
    std::cin >> a >> b;
    ab_map.push_back(std::make_pair(a, b));
  }
  std::sort(ab_map.begin(), ab_map.end());

  unsigned long long ans = 0;
  unsigned long long current = 0;
  for (auto ab : ab_map) {
    const unsigned long long a = ab.first;
    const unsigned long long b = ab.second;
    if (current + b < m) {
      ans += a * b;
      current += b;
      continue;
    } else {
      const unsigned long long num = m - current;
      ans += a * num;
      current += num;
      break;
    }
  }
  std::cout << ans << std::endl;

  return 0;
}
