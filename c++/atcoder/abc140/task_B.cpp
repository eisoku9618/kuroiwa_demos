#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;
  std::vector<int> A_array(N), B_array(N), C_array(N - 1);
  for (int i = 0; i < N; ++i) {
    std::cin >> A_array.at(i);
  }
  for (int i = 0; i < N; ++i) {
    std::cin >> B_array.at(i);
  }
  for (int i = 0; i < N - 1; ++i) {
    std::cin >> C_array.at(i);
  }

  int prev_index = -100;
  int sum_point = 0;
  for (int i = 0; i < N; ++i) {
    const int index = A_array.at(i) - 1;
    const int point = B_array.at(index);
    sum_point += point;
    if (prev_index + 1 == index) {
      const int bonus = C_array.at(prev_index);
      sum_point += bonus;
    }
    prev_index = index;
  }
  std::cout << sum_point << std::endl;
  return 0;
}
