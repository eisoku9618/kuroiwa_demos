#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool pairCompare(const std::pair<long long, long long>& firstElof, const std::pair<long long, long long>& secondElof) {
  if (firstElof.first == secondElof.first) {
    return firstElof.second > secondElof.second;
  } else {
    return firstElof.first > secondElof.first;
  }
}

int main() {
  int N;
  std::cin >> N;

  std::vector<std::pair<long long, long long>> hoge(N);

  for (int i = 0; i < N; ++i) {
    std::string S;
    std::cin >> S;
    long long level = 0;
    long long min = 0;
    for (const char c : S) {
      if (c == '(') {
        level += 1;
      } else {
        level -= 1;
      }
      min = std::min(level, min);
    }

    hoge[i] = std::make_pair(min, level);
  }

  std::sort(hoge.begin(), hoge.end(), pairCompare);

  long long level = 0;
  for (int i = 0; i < N; ++i) {
    const auto x = hoge[i];
    if (level + x.first < 0) {
      std::cout << "No" << std::endl;
      return 0;
    }
    level += x.second;
    if (level < 0) {
      std::cout << "No" << std::endl;
      return 0;
    }
  }

  if (level != 0) {
    std::cout << "No" << std::endl;
  } else {
    std::cout << "Yes" << std::endl;
  }


  return 0;
}
