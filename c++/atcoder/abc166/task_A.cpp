#include <iostream>
#include <string>

int main() {
  int N, K;
  std::cin >> N >> K;
  std::vector<int> has_candy(N, 0);
  for (int i = 0; i < K; ++i) {
    int d;
    std::cin >> d;
    for (int j = 0; j < d; ++j) {
      int a;
      std::cin >> a;
      a -= 1;
      if (has_candy.at(a) == 0) {
        has_candy.at(a) = 1;
      }
    }
  }

  std::cout << N - std::accumulate(has_candy.begin(), has_candy.end(), 0) << std::endl;

  return 0;
}
