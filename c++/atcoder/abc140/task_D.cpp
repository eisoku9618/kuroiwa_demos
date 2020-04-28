#include <iostream>
#include <string>

int main() {
  unsigned long N, K;
  std::cin >> N >> K;

  std::string S;
  std::cin >> S;

  unsigned long count = 0;
  for (unsigned long i = 0; i < N - 1; ++i) {
    if (S[i] == S[i + 1]) {
      count += 1;
    }
  }

  std::cout << std::min(count + K * 2, N - 1) << std::endl;

  return 0;
}
