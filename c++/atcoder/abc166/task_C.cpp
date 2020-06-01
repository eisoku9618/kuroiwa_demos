#include <iostream>
#include <vector>
#include <numeric>

int main() {
  unsigned int N, M;
  std::cin >> N >> M;
  std::vector<unsigned long> H_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> H_array.at(i);
  }

  std::vector<int> ans_array(N, 1);
  for (unsigned int i = 0; i < M; ++i) {
    unsigned int a, b;
    std::cin >> a >> b;
    a -= 1;
    b -= 1;
    if (H_array.at(a) < H_array.at(b)) {
      ans_array.at(a) = 0;
    } else if ((H_array.at(a) > H_array.at(b))) {
      ans_array.at(b) = 0;
    } else {
      ans_array.at(a) = 0;
      ans_array.at(b) = 0;
    }
  }

  std::cout << std::accumulate(ans_array.begin(), ans_array.end(), 0) << std::endl;

  return 0;
}
