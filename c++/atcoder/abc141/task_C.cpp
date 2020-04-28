#include <iostream>
#include <vector>

int main() {
  unsigned int N, K, Q;
  std::cin >> N >> K >> Q;
  std::vector<unsigned int> correct_array(N, 0);
  for (unsigned int i = 0; i < Q; ++i) {
    unsigned int a;
    std::cin >> a;
    correct_array.at(a - 1) += 1;
  }

  for (unsigned int i = 0; i < N; ++i) {
    const unsigned int others_correct_num = Q - correct_array.at(i);
    if (K > others_correct_num) {
      std::cout << "Yes" << std::endl;
    } else {
      std::cout << "No" << std::endl;
    }
  }

  return 0;
}
