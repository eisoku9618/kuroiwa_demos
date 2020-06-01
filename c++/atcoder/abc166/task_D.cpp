#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

int main() {
  unsigned long X;
  std::cin >> X;

  std::array<unsigned long, 130> zizen;
  for (unsigned long i = 0; i < 130; ++i) {
    zizen.at(i) = std::pow(i, 5);
  }

  // case B >= 0
  for (unsigned int i = 0; i < 130; ++i) {
    unsigned long a_5 = zizen.at(i);
    if (a_5 < X) {
      continue;
    }
    // a_5 >= X
    unsigned long b_5 = a_5 - X;
    auto result = std::find(zizen.begin(), zizen.end(), b_5);
    if (result == zizen.end()) {
      continue;
    } else {
      unsigned int b_index = std::distance(zizen.begin(), result);
      std::cout << i << " " << b_index << std::endl;
      return 0;
    }
  }

  // case B < 0
  for (unsigned int i = 0; i < 130; ++i) {
    unsigned long a_5 = zizen.at(i);
    if (a_5 > X) {
      continue;
    }
    // a_5 <= X
    unsigned long b_5 = X - a_5;
    auto result = std::find(zizen.begin(), zizen.end(), b_5);
    if (result == zizen.end()) {
      continue;
    } else {
      unsigned int b_index = std::distance(zizen.begin(), result);
      std::cout << i << " -" << b_index << std::endl;
      return 0;
    }
  }
  return 0;
}
