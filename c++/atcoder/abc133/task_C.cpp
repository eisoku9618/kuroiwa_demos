#include <iostream>
#include <algorithm>

int main() {
  long L, R;
  std::cin >> L >> R;

  const unsigned long R_max = R;
  const unsigned long R_min = std::max(R - 2019, L + 1);
  const unsigned long L_max = std::min(L + 2019, R - 1);
  const unsigned long L_min = L;

  unsigned long min_val = 2019;

  for (unsigned long r = R_min; r <= R_max; ++r) {
    for (unsigned long l = L_min; l <= L_max; ++l) {
      min_val = std::min((r * l) % 2019, min_val);
      if (min_val == 0) {
        std::cout << 0 << std::endl;
        return 0;
      }
    }
  }
  std::cout << min_val << std::endl;

  return 0;
}
