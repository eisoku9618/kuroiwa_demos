#include <iostream>
#include <vector>

int main() {
  int N, L;
  std::cin >> N >> L;

  const int taste_zero_index = 1 - L;
  const int taste_sum = (L + L + N - 1) * N / 2; // 20, 0, -1065

  int answer = 0;
  if (taste_zero_index < 1) {
    answer = taste_sum - (L + 1 - 1);
  } else if (taste_zero_index > N) {
    answer = taste_sum - (L + N - 1);
  } else {
    answer = taste_sum;
  }

  std::cout << answer << std::endl;

  return 0;
}
