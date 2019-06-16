#include <iostream>

int main() {
  unsigned long w, h, x, y;
  std::cin >> w >> h >> x >> y;

  const double half_area = w / 2.0 * h;
  if (x * 2 == w && y * 2 == h) {
    std::cout << half_area << " 1" << std::endl;
  } else {
    std::cout << half_area << " 0" << std::endl;
  }

  return 0;
}
