#include <iostream>
#include <cmath>
#include <numeric>

int main() {
  int N;
  std::cin >> N;

  unsigned int this_digit = 0;
  for (int digit = 5; digit >= 0; digit--) {
    if (N >= std::pow(10, digit)) {
      this_digit = digit + 1;
      break;
    }
  }
  if (this_digit == 1 || this_digit == 2) {
    std::cout << std::min(N, 9) - 1 + 1 << std::endl;
  } else if (this_digit == 3 || this_digit == 4) {
    std::cout << 9 + std::min(N, 999) - 100 + 1 << std::endl;
  } else if (this_digit == 5 || this_digit == 6) {
    std::cout << 9 + (999 - 100 + 1) + std::min(N, 99999) - 10000 + 1 << std::endl;
  }

  return 0;
}
