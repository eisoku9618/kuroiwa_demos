#include <iostream>
#include <vector>

const unsigned long mod = 1000000007;

// exponentiation by squaring: n^k
long long mod_pow(long long n, long long k) {
  if (k == 1) {
    return n % mod;
  } else if (k % 2 == 1) {
    return (n * mod_pow(n, k - 1)) % mod;
  } else {
    long long half_pow = mod_pow(n, k / 2);
    return (half_pow * half_pow) % mod;
  }
}

int main() {
  unsigned int N, K;
  std::cin >> N >> K;

  std::vector<long long> dp(K + 1, 0);

  for (unsigned int i = K; i >= 1; --i) {
    const unsigned long candidate_num = K / i;
    dp.at(i) = mod_pow(K / i, N);
    unsigned long subtract = 0;
    for (unsigned int j = 2; j <= candidate_num; ++j) {
      subtract = (subtract + dp.at(j * i)) % mod;
    }
    dp.at(i) = (dp.at(i) - subtract + mod) % mod;
  }

  unsigned long sum = 0;
  for (unsigned int i = 1; i <= K; ++i) {
    sum = (sum + (i * dp.at(i)) % mod) % mod;
  }

  std::cout << sum << std::endl;
  return 0;
}
