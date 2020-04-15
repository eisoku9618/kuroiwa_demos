#include <iostream>

int main() {
  unsigned int A, B;
  std::cin >> A >> B;

  if ((A + B) % 2 == 0) {
    std::cout << (A + B) / 2 << std::endl;
  } else {
    std::cout << "IMPOSSIBLE" << std::endl;
  }

  return 0;
}
