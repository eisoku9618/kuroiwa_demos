#include <iostream>

int main() {
  std::string S;
  std::cin >> S;

  const char a = S[0];
  const char b = S[1];
  const char c = S[2];
  const char d = S[3];

  if ((a == b && c == d && a != c) || (a == c && b == d && a != b) || (a == d && b == c && a != b)) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }

  return 0;
}
