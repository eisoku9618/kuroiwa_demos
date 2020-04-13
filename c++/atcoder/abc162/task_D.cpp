#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  unsigned int N;
  std::string S;
  std::cin >> N;
  std::cin >> S;

  std::vector<char> S_array;
  for (size_t i = 0; i < N; ++i) {
    S_array.push_back(S[i]);
  }

  const unsigned long r_num = std::count(S_array.begin(), S_array.end(), 'R');
  const unsigned long g_num = std::count(S_array.begin(), S_array.end(), 'G');
  const unsigned long b_num = std::count(S_array.begin(), S_array.end(), 'B');

  unsigned long sum = r_num * g_num * b_num;

  for (unsigned int i = 0; i < N; ++i) {
    for (unsigned int j = i + 1; j < N; ++j) {
      const unsigned int k = 2 * j - i;
      if (k >= N) {
        continue;
      }
      if (S[i] != S[j] && S[j] != S[k] && S[k] != S[i]) {
        sum -= 1;
      }
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
