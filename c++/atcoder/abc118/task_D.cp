#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main() {
  constexpr std::array<unsigned int, 9> num_matchstick_list{{2, 5, 5, 4, 5, 6, 3, 7, 6}};

  unsigned int n, m;
  std::cin >> n >> m;
  std::vector<unsigned int> A(m);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> A.at(i);
  }

  // dp.at(i): i本で出来る最大の桁数
  std::vector<unsigned int> dp(n + 1, 0);

  for (size_t i = 1; i < dp.size(); ++i) {
    for (size_t j = 0; j < A.size(); ++j) {
      const unsigned int& num_matchstick = num_matchstick_list.at(A.at(j) - 1);
      if (i >= num_matchstick) {
        const unsigned int& new_digit = dp.at(i - num_matchstick) + 1;
        if (dp.at(i) < new_digit) {
          dp.at(i) = new_digit;
        }
      }
    }
  }
  const unsigned int max_digit = dp.at(n);

  std::sort(A.begin(), A.end(), std::greater<unsigned int>());
  unsigned int residual = n;
  std::string ans = "";
  for (size_t d = max_digit; d > 0; --d) {
    for (unsigned int a : A) {
      const unsigned int& num_matchstick = num_matchstick_list.at(a - 1);
      // 残りの本数より下回っていたらNG
      if (residual < num_matchstick) {
        continue;
      }
      // 最後の桁なのに残る予定の本数が0でなかったらNG
      if (dp.at(residual - num_matchstick) == 0 && residual - num_matchstick != 0) {
        continue;
      }
      if (dp.at(residual - num_matchstick) + 1 == dp.at(residual)) {
        residual -= num_matchstick;
        ans += std::to_string(a);
        break;
      }
    }
  }
  std::cout << ans << std::endl;

  return 0;
}
