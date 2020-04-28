#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<int> H_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> H_array.at(i);
  }

  unsigned int max = 0;
  unsigned int current = 0;

  for (unsigned int i = 0; i < N - 1; ++i) {
    const unsigned int h = H_array.at(i);
    const unsigned int next = H_array.at(i + 1);
    if (h >= next) {
      current += 1;
    } else {
      max = std::max(max, current);
      current = 0;
    }
  }

  std::cout << std::max(max, current) << std::endl;

  return 0;
}
