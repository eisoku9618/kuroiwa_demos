#include <iostream>
#include <vector>
#include <map>

int main() {
  unsigned long N;
  std::cin >> N;

  std::multimap<unsigned long, unsigned long, std::less<unsigned long>> BA_map;
  for (unsigned long i = 0; i < N; ++i) {
    unsigned long A, B;
    std::cin >> A >> B;
    BA_map.emplace(B, A);
  }

  unsigned long current_time = 0;

  for (const auto BA : BA_map) {
    const unsigned long B = BA.first;
    const unsigned long A = BA.second;
    current_time += A;
    if (B < current_time) {
      std::cout << "No" << std::endl;
      return 0;
    }
  }

  std::cout << "Yes" << std::endl;
  return 0;
}
