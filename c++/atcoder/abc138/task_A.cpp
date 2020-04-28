#include <iostream>
#include <string>

int main() {
  int a;
  std::cin >> a;
  std::string s;
  std::cin >> s;

  if (a >= 3200) {
    std::cout << s << std::endl;
  } else {
    std::cout << "red" << std::endl;
  }
  return 0;
}
