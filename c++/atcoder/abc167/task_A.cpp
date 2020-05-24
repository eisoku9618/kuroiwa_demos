#include <iostream>
#include <string>

int main() {
  std::string S, T;
  std::cin >> S;
  std::cin >> T;

  if (S.size() + 1 != T.size()) {
    std::cout << "No" << std::endl;
  }

  if (T.substr(0, S.size()) == S) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
  return 0;
}
