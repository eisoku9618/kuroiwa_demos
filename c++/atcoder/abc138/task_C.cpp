#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int N;
  std::cin >> N;
  std::vector<int> v_array(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> v_array.at(i);
  }

  std::sort(v_array.begin(), v_array.end(), std::greater<int>());

  double sum = 0.0;
  double pow = 1.0;
  for (int i = 0; i < N; ++i) {
    if (i != N - 1) {
      pow *= 0.5;
    }
    sum += v_array.at(i) * pow;
  }
  std::cout << sum << std::endl;

  return 0;
}
