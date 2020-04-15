#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string S;
  std::cin >> S;

  const unsigned int digit = S.size();

  const unsigned int mod = 13;
  const unsigned int large_mod = 1e+9 + 7;
  std::vector<std::vector<long long>> dp(digit + 1, std::vector<long long>(mod, 0));
  dp.at(0).at(0) = 1;

  for (unsigned int i = 0; i < digit; ++i) {
    size_t keta_amari;
    const int i_amari = i % 6;
    if (i_amari == 0) {
      keta_amari = 1;
    } else if (i_amari == 1) {
      keta_amari = 10;
    } else if (i_amari == 2) {
      keta_amari = 9;
    } else if (i_amari == 3) {
      keta_amari = 12;
    } else if (i_amari == 4) {
      keta_amari = 3;
    } else if (i_amari == 5) {
      keta_amari = 4;
    }

    const char x = S[digit - 1 - i];
    if (x != '?') {
      const unsigned int number = x - '0';
      for (size_t j = 0; j < mod; ++j) {
        const unsigned int amari = (keta_amari * number) % mod;
        const unsigned int target_index = (j + amari) % mod;
        dp.at(i + 1).at(target_index) = dp.at(i).at(j);
      }
    } else {
      for (unsigned int number = 0; number < 10; ++number) {
        for (size_t j = 0; j < mod; ++j) {
          const unsigned int amari = (keta_amari * number) % mod;
          const unsigned int target_index = (j + amari) % mod;
          dp.at(i + 1).at(target_index) = (dp.at(i + 1).at(target_index) + dp.at(i).at(j)) % large_mod;
        }
      }
    }
  }

  std::cout << dp.at(digit).at(5) << std::endl;

  return 0;
}
