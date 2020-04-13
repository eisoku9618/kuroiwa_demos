#include <iostream>
#include <vector>
#include <numeric>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> A_array;
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int A;
    std::cin >> A;
    A_array.push_back(A);
  }

  std::vector<unsigned int> B_array(N, 0);
  std::vector<unsigned int> index_array;

  for (long long m = N - 1; m >=0; --m) {
    const unsigned int candidate_num = N / (m + 1);
    unsigned int sum = 0;
    for (unsigned int i = candidate_num; i >= 1; --i) {
      sum += B_array.at(i * (m + 1) - 1);
    }
    if (sum % 2 == A_array.at(m)) {
      B_array.at(m) = 0;
    } else {
      B_array.at(m) = 1;
      index_array.push_back(m + 1);
    }
  }

  const unsigned int M = std::accumulate(B_array.begin(), B_array.end(), 0);

  std::cout << M << std::endl;
  if (M == 0) {
    return 0;
  }

  for (unsigned int i = M; i >= 1; --i) {
    if (i != 1) {
      std::cout << index_array.at(i - 1) << " ";
    } else {
      std::cout << index_array.at(i - 1) << std::endl;
    }
  }

  return 0;
}
