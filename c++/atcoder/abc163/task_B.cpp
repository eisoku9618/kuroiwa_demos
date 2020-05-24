#include <iostream>
#include <vector>
#include <numeric>

int main() {
  long long N, M;
  std::cin >> N >> M;

  std::vector<long long> A_array(M);
  for (unsigned int i = 0; i < M; ++i) {
    std::cin >> A_array.at(i);
  }

  std::cout << std::max(N - std::accumulate(A_array.begin(), A_array.end(), 0), -1LL) << std::endl;
  return 0;
}
