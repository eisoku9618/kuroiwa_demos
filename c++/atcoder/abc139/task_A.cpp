#include <iostream>
#include <string>

int main() {
  std::string S;
  std::cin >> S;
  std::string T;
  std::cin >> T;

  int count = 0;
  for (size_t i = 0; i < 3; ++i) {
    if (S.at(i) == T.at(i)) {
      count += 1;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
