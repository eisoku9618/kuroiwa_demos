#include <iostream>

int main() {
  int A, B;
  std::cin >> A >> B;
  const int want = B - 1;
  if (want % (A - 1) == 0) {
    std::cout << want / (A - 1) << std::endl;
  } else {
    std::cout << want / (A - 1) + 1 << std::endl;
  }

  return 0;
}
