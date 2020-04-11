#include <iostream>
#include <vector>

std::vector<std::vector<unsigned long>> comb(unsigned long n, unsigned long r) {
  std::vector<std::vector<unsigned long>> v(n + 1, std::vector<unsigned long>(n + 1, 0));

  for (unsigned long i = 0; i < v.size(); ++i) {
    v[i][0] = 1;
    v[i][i] = 1;
  }

  for (unsigned long i = 1; i < v.size(); ++i) {
    for (unsigned long j = 1; j < i; ++j) {
      v[i][j] = ((v[i - 1][j - 1] % 1000000007) + (v[i - 1][j] % 1000000007)) % 1000000007;
    }
  }

  return v;
}

int main() {
  unsigned long N, K;
  std::cin >> N >> K;

  const unsigned long max = std::max(K, N - K + 1);
  const std::vector<std::vector<unsigned long>> my_comb = comb(max, K);
  for (unsigned long i = 1; i <= K; ++i) {
    const unsigned long blue = my_comb[K - 1][i - 1];
    const unsigned long red = my_comb[N - K + 1][i];
    std::cout << ((blue % 1000000007) * (red % 1000000007)) % 1000000007 << std::endl;
  }
  return 0;
}
