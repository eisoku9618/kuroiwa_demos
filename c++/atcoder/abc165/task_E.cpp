#include <iostream>

int main() {
  unsigned long N, M;
  std::cin >> N >> M;

  unsigned long diff = N - 1;
  for (unsigned long i = 0; i < M; ++i) {
    unsigned long cur = i + 1;
    std::cout << cur << " " << cur + diff << std::endl;
    diff -= 1;
  }
  return 0;
}
