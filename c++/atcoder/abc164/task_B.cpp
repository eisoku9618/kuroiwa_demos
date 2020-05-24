#include <iostream>
#include <vector>
#include <numeric>

int main() {
  int A, B, C, D;
  std::cin >> A >> B >> C >> D;

  bool turn = true;
  while (A > 0 && C > 0) {
    if (turn) {
      C -= B;
    } else {
      A -= D;
    }
    turn = !turn;
  }

  if (A > 0) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
  return 0;
}
