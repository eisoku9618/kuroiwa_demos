#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int N;
  long long K;
  std::cin >> N >> K;

  std::vector<int> A_array(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> A_array[i];
    A_array[i] -= 1;
  }

  if (N > K) {
    int index = 0;
    for (int i = 0; i < K; ++i) {
      index = A_array[index];
    }
    std::cout << index + 1 << std::endl;
    return 0;
  }

  std::vector<bool> seen(N, false);

  int next_index = 0;
  bool loop_found = false;
  for (int i = 0; i < N; ++i) {
    if (seen[next_index]) {
      loop_found = true;
      break;
    }
    seen[next_index] = true;
    next_index = A_array[next_index];
  }

  const int loop_start_index = next_index;
  const int loop_end_count = std::count(seen.begin(), seen.end(), true);

  int count = 0;
  next_index = 0;
  for (int i = 0; i < N; ++i) {
    if (next_index == loop_start_index) {
      break;
    }
    count += 1;
    next_index = A_array[next_index];
  }

  const long long loop_num = loop_end_count - count;

  const long long target_index_from_loop_start = (K - count) % loop_num;

  for (int i = 0; i < target_index_from_loop_start; ++i) {
    next_index = A_array[next_index];
  }

  std::cout << next_index + 1 << std::endl;
  return 0;
}
