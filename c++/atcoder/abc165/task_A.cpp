#include <iostream>

int main() {
  int K;
  std::cin >> K;
  int A, B;
  std::cin >> A >> B;

  for (int i = A; i <= B; ++i) {
    if (i % K == 0) {
      std::cout << "OK" << std::endl;
      return 0;
    }
  }

  std::cout << "NG" << std::endl;

  return 0;
}
