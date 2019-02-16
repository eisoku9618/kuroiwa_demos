#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  unsigned int n;
  std::cin >> n;
  std::vector<unsigned int> A(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> A.at(i);
  }

  std::sort(A.begin(), A.end());
  while (true) {
    const unsigned int min = A.at(0);
    for (size_t i = 1; i < A.size(); ++i) {
      A.at(i) = A.at(i) % min;
    }

    A.erase(std::remove(A.begin(), A.end(), 0), A.end());

    std::sort(A.begin(), A.end());
    if (A.at(0) == min) {
      break;
    }
  }

  std::cout << A.at(0) << std::endl;
  return 0;
}
