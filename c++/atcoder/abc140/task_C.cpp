#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;

  std::vector<unsigned int> B_array(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    std::cin >> B_array.at(i);
  }

  unsigned long sum = 0;

  for (int i = 0; i < N; ++i) {
    if (i == 0) {
      sum += B_array.at(i);
    } else if (i == N - 1) {
      sum += B_array.at(i - 1);
    } else {
      sum += std::min(B_array.at(i), B_array.at(i - 1));
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
