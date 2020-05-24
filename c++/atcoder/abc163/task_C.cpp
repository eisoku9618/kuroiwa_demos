#include <iostream>
#include <numeric>
#include <vector>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> answer(N, 0);
  for (unsigned int i = 1; i < N; ++i) {
    unsigned int A;
    std::cin >> A;
    answer.at(A - 1) += 1;
  }

  for (auto x : answer) {
    std::cout << x << std::endl;
  }

  return 0;
}
