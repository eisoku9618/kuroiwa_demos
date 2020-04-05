#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;

  if (s[0] == s[1] || s[1] == s[2] || s[2] == s[3]) {
    std::cout << "Bad" << std::endl;
  } else {
    std::cout << "Good" << std::endl;
  }

  return 0;
}
