#include <iostream>
#include <vector>

int main() {
  unsigned int N, K;
  std::cin >> N >> K;
  const unsigned long mod = 1000000007;

  unsigned long sum = 0;
  for (unsigned long i = K; i <= N + 1; ++i) {
    // 0, 1, ..., i - 1
    const unsigned long min_sum = (i - 1) * i / 2;
    // N - i + 1, N - i + 2, ..., N
    const unsigned long max_sum = (2 * N - i + 1) * i / 2;
    const unsigned long num = (max_sum - min_sum + 1) % mod;
    sum = (sum + num) % mod;
  }

  std::cout << sum << std::endl;
  return 0;
}
