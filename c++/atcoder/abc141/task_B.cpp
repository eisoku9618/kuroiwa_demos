#include <iostream>
#include <string>

int main() {
  std::string S;
  std::cin >> S;

  for (size_t i = 0; i < S.size(); ++i) {
    if (i % 2 == 0) {
      if (S.at(i) == 'L') {
        std::cout << "No" << std::endl;
        return 0;
      }
    } else {
      if (S.at(i) == 'R') {
        std::cout << "No" << std::endl;
        return 0;
      }
    }
  }
  std::cout << "Yes" << std::endl;

  return 0;
}
