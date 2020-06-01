#include <iostream>

int main() {
  int S, W;
  std::cin >> S >> W;

  if (S <= W) {
    std::cout << "unsafe" << std::endl;
  } else {
    std::cout << "safe" << std::endl;
  }

  return 0;
}
