#include <iostream>

int main() {
  int A, B, C;
  std::cin >> A >> B >> C;

  std::cout << std::max(C - (A - B), 0) << std::endl;

  return 0;
}
