#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

bool check_anagram(std::string a, std::string b) {
  std::array<unsigned int, 'z' - 'a' + 1> alphabet_counter_a;
  std::array<unsigned int, 'z' - 'a' + 1> alphabet_counter_b;
  alphabet_counter_a.fill(0);
  alphabet_counter_b.fill(0);
  for (int i = 0; i < 10; ++i) {
    alphabet_counter_a.at(a[i] - 'a') += 1;
    alphabet_counter_b.at(b[i] - 'a') += 1;
  }

  if (alphabet_counter_a == alphabet_counter_b) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int N;
  std::cin >> N;
  std::vector<std::string> s_array(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> s_array.at(i);
  }

  std::unordered_map<std::string, long> s_map;
  for (int i = 0; i < N; ++i) {
    std::string s = s_array.at(i);
    std::array<unsigned int, 'z' - 'a' + 1> alphabet_counter;
    alphabet_counter.fill(0);
    for (int i = 0; i < 10; ++i) {
      alphabet_counter.at(s[i] - 'a') += 1;
    }
    std::string key_string = "";
    for (const auto x : alphabet_counter) {
      key_string += std::to_string(x);
    }

    if (s_map.count(key_string) == 0) {
      s_map.emplace(key_string, 1);
    } else {
      s_map.at(key_string) += 1;
    }
  }

  long long sum = 0;
  for (auto x : s_map) {
    const long long n = x.second;
    sum += n * (n - 1) / 2;
  }

  std::cout << sum << std::endl;

  return 0;
}
