#include <iostream>
#include <vector>
#include <numeric>

int main() {
  int A, B, C, K;
  std::cin >> A >> B >> C >> K;

  if (A >= K) {
    std::cout << K << std::endl;
  } else if (A + B >= K) {
    std::cout << A << std::endl;
  } else {
    std::cout << A - (K - A - B) << std::endl;
  }

  return 0;
}
