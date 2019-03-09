#include <iostream>
#include <vector>

int main() {
  std::string s;

  std::cin >> s;

  unsigned int zero_size = 0;
  unsigned int one_size = 0;

  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '0') {
      zero_size += 1;
    } else {
      one_size += 1;
    }
  }

  std::cout << std::min(zero_size, one_size) * 2 << std::endl;

  return 0;
}
