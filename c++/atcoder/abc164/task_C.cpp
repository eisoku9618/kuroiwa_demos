#include <iostream>
#include <unordered_map>

int main() {
  unsigned int N;
  std::cin >> N;

  std::unordered_map<std::string, bool> map;
  for (unsigned int i = 0; i < N; ++i) {
    std::string S;
    std::cin >> S;
    map.emplace(S, true);
  }

  std::cout << map.size() << std::endl;

  return 0;
}
