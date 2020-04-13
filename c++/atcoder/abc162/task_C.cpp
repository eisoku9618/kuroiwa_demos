#include <iostream>
#include <numeric>
#include <vector>

int main() {
  unsigned int K;
  std::cin >> K;

  std::vector<std::vector<unsigned int>> gcd_array(K + 1, std::vector<unsigned int>(K + 1, 0));
  for (size_t i = 1; i <= K; ++i) {
    for (size_t j = i; j >= 1; --j) {
      gcd_array.at(i).at(j) = std::gcd(i, j);
    }
  }

  unsigned long sum = 0;
  for (unsigned int a = 1; a <= K; ++a) {
    for (unsigned int b = 1; b <= K; ++b) {
      const unsigned int ab_gcd = gcd_array.at(std::max(a, b)).at(std::min(a, b));
      for (unsigned int c = 1; c <= K; ++c) {
        const unsigned int gcd = gcd_array.at(std::max(ab_gcd, c)).at(std::min(ab_gcd, c));
        sum += gcd;
      }
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
