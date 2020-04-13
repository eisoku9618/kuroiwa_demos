#include <iostream>

int main() {
  std::string S;
  std::cin >> S;

  if (S[0] == '7' || S[1] == '7' || S[2] == '7') {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }

  return 0;
}
