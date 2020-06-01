#include <iostream>
#include <map>

int main() {
  long long N;
  std::cin >> N;

  std::map<long long, long long> B_map, C_map;
  for (long long i = 0; i < N; ++i) {
    long long a;
    std::cin >> a;
    B_map[i + a] += 1;
    C_map[i - a] += 1;
  }

  unsigned long ans = 0;
  for (auto x : B_map) {
    const long long B_num = x.second;
    const long long C_num = C_map[x.first];
    ans += B_num * C_num;
  }

  std::cout << ans << std::endl;
  return 0;
}
