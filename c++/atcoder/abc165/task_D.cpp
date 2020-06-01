#include <iostream>

int main() {
  unsigned long A, B, N;
  std::cin >> A >> B >> N;

  const unsigned long x = std::min(B - 1, N);
  std::cout << A * x / B << std::endl;
  return 0;
}
