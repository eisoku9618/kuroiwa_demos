#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  unsigned int N;
  std::cin >> N;
  std::vector<unsigned int> A_array;
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int a;
    std::cin >> a;
    A_array.push_back(a);
  }

  std::vector<unsigned int> min_val;
  min_val.push_back(A_array.at(N - 1));

  for (unsigned int i = N - 1; i >= 1; --i) {
    const unsigned int& a = A_array.at(i - 1);
    std::vector<unsigned int>::iterator itr = std::upper_bound(min_val.begin(), min_val.end(), a);
    if (itr == min_val.end()) {
      min_val.push_back(a);
    } else {
      *itr = a;
    }
  }

  std::cout << min_val.size() << std::endl;

  return 0;
}
