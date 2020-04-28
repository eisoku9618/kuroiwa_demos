#include <iostream>

int main() {
  int N;
  std::cin >> N;

  double denominator = 0;
  for (int i = 0; i < N; ++i) {
    unsigned int a;
    std::cin >> a;
    denominator += 1.0 / a;
  }

  std::cout << 1.0 / denominator << std::endl;

  return 0;
}
