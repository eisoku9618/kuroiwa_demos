#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> d_vec;
  for (size_t i = 0; i < N; ++i) {
    unsigned int d;
    std::cin >> d;
    d_vec.push_back(d);
  }

  std::sort(d_vec.begin(), d_vec.end(), std::less<unsigned int>());

  const unsigned int abc_max = d_vec.at(N / 2 - 1);
  const unsigned int arc_min = d_vec.at(N / 2);

  std::cout << arc_min - (abc_max + 1) + 1 << std::endl;

  return 0;
}
