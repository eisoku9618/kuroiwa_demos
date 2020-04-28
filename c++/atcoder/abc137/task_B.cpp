#include <iostream>
#include <cmath>
#include <numeric>

int main() {
  int K, X;
  std::cin >> K >> X;

  const int min = X - K + 1;
  const int max = X + K - 1;

  for (int i = min; i <= max; ++i) {
    std::cout << i;
    if (i != max) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;

  return 0;
}
