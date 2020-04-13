#include <iostream>
#include <vector>
#include <cmath>

int main() {
  unsigned int N, D;
  std::cin >> N >> D;

  std::vector<std::vector<int>> data(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::vector<int> x_array;
    for (unsigned int j = 0; j < D; ++j) {
      int x;
      std::cin >> x;
      x_array.push_back(x);
    }
    data.at(i) = x_array;
  }

  unsigned int counter = 0;
  for (unsigned int i = 0; i < N - 1; ++i) {
    const std::vector<int>& y = data.at(i);
    for (unsigned int j = i + 1; j < N; ++j) {
      const std::vector<int>& z = data.at(j);
      unsigned int sum = 0.0;
      for (unsigned int k = 0; k < D; ++k) {
        sum += std::pow(y.at(k) - z.at(k), 2);
      }
      const double sqrt = std::sqrt(static_cast<double>(sum));
      const unsigned int sqrt_int = static_cast<unsigned int>(sqrt);
      const unsigned int sqrt_int_square = std::pow(sqrt_int, 2);
      if (sqrt_int_square == sum) {
        counter += 1;
      }
    }
  }

  std::cout << counter << std::endl;

  return 0;
}
