#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
  std::string S;
  std::cin >> S;
  const unsigned int mod = 2019;

  std::vector<unsigned int> dp(S.size());
  unsigned int pow = 10;
  for (unsigned int i = S.size(); i > 0; --i) {
    if (i == S.size()) {
      dp.at(i - 1) = S[i - 1] - '0';
    } else {
      dp.at(i - 1) = (dp.at(i) + (S[i - 1] - '0') * pow) % mod;
      pow = (pow * 10) % mod;
    }
  }

  std::unordered_map<unsigned int, unsigned long> map;
  map.emplace(0, 1);
  for (unsigned int i = 0; i < S.size(); ++i) {
    if (map.count(dp.at(i)) == 0) {
      map.emplace(dp.at(i), 1);
    } else {
      map.at(dp.at(i)) += 1;
    }
  }

  unsigned long ans = 0;
  for (const auto& x : map) {
    const unsigned long num = x.second;
    ans += num * (num - 1) / 2;
  }

  std::cout << ans << std::endl;
  return 0;
}
