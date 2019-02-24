#include <iostream>
#include <vector>

int main() {
  unsigned int n;
  std::cin >> n;

  double sum = 0.0;
  for (size_t i = 0; i < n; ++i) {
    double x;
    std::string u;
    std::cin >> x >> u;
    if (u == "JPY") {
      sum += x;
    } else {
      sum += x * 380000;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
