#include <iostream>
#include <vector>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> A_array;
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int A;
    std::cin >> A;
    A_array.push_back(A);
  }

  std::vector<long> x_array(N, 0);
  // x_array.at(0)
  for (unsigned int i = 0; i < N; ++i) {
    if (i % 2 == 0) {
      x_array.at(0) += A_array.at(i);
    } else {
      x_array.at(0) -= A_array.at(i);
    }
  }
  for (unsigned int i = 1; i < N; ++i) {
    x_array.at(i) = x_array.at(i - 1) * -1 + 2 * A_array.at(i - 1);
  }

  for (unsigned int i = 0; i < N; ++i) {
    if (i != N - 1) {
      std::cout << x_array.at(i) << " ";
    } else {
      std::cout << x_array.at(i) << std::endl;
    }
  }

  return 0;
}
