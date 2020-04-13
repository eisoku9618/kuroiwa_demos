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

  std::vector<unsigned int> A_array_sorted = A_array;

  std::sort(A_array_sorted.begin(), A_array_sorted.end(), std::greater<unsigned int>());

  const unsigned int first = A_array_sorted.at(0);
  const unsigned int second = A_array_sorted.at(1);

  for (unsigned int i = 0; i < N; ++i) {
    if (A_array.at(i) == first) {
      std::cout << second << std::endl;
    } else {
      std::cout << first << std::endl;
    }
  }

  return 0;
}
