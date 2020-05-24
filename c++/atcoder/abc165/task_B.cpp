#include <iostream>

int main() {
  unsigned long X;
  std::cin >> X;

  unsigned long current = 100;

  unsigned long year = 0;
  while (current < X) {
    current += static_cast<unsigned long>(current * 0.01);
    year += 1;
  }

  std::cout << year << std::endl;
  return 0;
}
