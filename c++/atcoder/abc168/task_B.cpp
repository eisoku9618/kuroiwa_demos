#include <iostream>
#include <string>

int main() {
  int K;
  std::cin >> K;
  std::string S;
  std::cin >> S;

  if (S.size() <= K) {
    std::cout << S << std::endl;
  } else {
    std::cout << S.substr(0, K) << "..." << std::endl;
  }

  return 0;
}
