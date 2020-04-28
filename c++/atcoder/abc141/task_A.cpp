#include <iostream>
#include <string>

int main() {
  std::string S;
  std::cin >> S;

  if (S == "Sunny") {
    std::cout << "Cloudy" << std::endl;
  } else if (S == "Cloudy") {
    std::cout << "Rainy" << std::endl;
  } else {
    std::cout << "Sunny" << std::endl;
  }

  return 0;
}
