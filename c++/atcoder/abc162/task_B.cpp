#include <iostream>

int main() {
  unsigned int N;
  std::cin >> N;

  unsigned long sum = 0;
  for (unsigned int i = 1; i < N + 1; ++i) {
    if (i % 3 != 0 && i % 5 != 0) {
      sum += i;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
