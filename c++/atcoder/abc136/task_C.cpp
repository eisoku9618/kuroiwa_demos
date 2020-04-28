#include <iostream>
#include <vector>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> H_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> H_array.at(i);
  }

  unsigned int min_val = 0;
  for (unsigned int i = 0; i < N; ++i) {
    const unsigned int& H = H_array.at(i);
    if (H < min_val) {
      std::cout << "No" << std::endl;
      return 0;
    }
    if (min_val < H - 1) {
      min_val = H - 1;
    }
  }
  std::cout << "Yes" << std::endl;

  return 0;
}
