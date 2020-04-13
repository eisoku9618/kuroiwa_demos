#include <iostream>

int main() {
  unsigned int N, D;
  std::cin >> N >> D;

  const unsigned int x = 2 * D + 1;
  const unsigned int amari = N % x;
  if (amari == 0) {
    std::cout << N / x << std::endl;
  } else {
    std::cout << N / x + 1 << std::endl;
  }

  return 0;
}
