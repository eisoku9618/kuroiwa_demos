#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> A_array(N + 1);
  for (unsigned int i = 0; i < N + 1; ++i) {
    std::cin >> A_array.at(i);
  }

  std::vector<unsigned int> B_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> B_array.at(i);
  }

  unsigned long sum = 0;

  if (N == 1) {
    sum += std::min(A_array.at(0) + A_array.at(1), B_array.at(0));
    std::cout << sum << std::endl;
    return 0;
  }

  // left
  const unsigned int left_val = std::min(A_array.at(0), B_array.at(0));
  sum += left_val;
  B_array.at(0) -= left_val;
  // right
  const unsigned int right_val = std::min(A_array.at(N), B_array.at(N - 1));
  sum += right_val;
  B_array.at(N - 1) -= right_val;

  for (unsigned int i = 1; i < N; ++i) {
    const unsigned int first = std::min(A_array.at(i), B_array.at(i - 1));
    sum += first;
    A_array.at(i) -= first;
    const unsigned int second = std::min(A_array.at(i), B_array.at(i));
    sum += second;
    B_array.at(i) -= second;
  }

  std::cout << sum << std::endl;

  return 0;
}
