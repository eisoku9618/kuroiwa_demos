#include <iostream>

int main() {
  unsigned int x, a;
  std::cin >> x >> a;

  if (x < a) {
    std::cout << 0 << std::endl;
  } else {
    std::cout << 10 << std::endl;
  }

  return 0;
}
