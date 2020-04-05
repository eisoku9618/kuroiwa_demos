#include <iostream>
#include <algorithm>

unsigned long my_func(unsigned long A, unsigned long B, unsigned long div) {
  const unsigned long A_div = A / div;
  const unsigned long B_div = B / div;

  unsigned long div_min = A_div;
  if (A % div != 0) {
    div_min += 1;
  }
  const unsigned long div_max = B_div;

  return div_max - div_min + 1;
}

int main() {
  unsigned long A, B, C, D;
  std::cin >> A >> B >> C >> D;

  const unsigned long C_num = my_func(A, B, C);
  const unsigned long D_num = my_func(A, B, D);
  const unsigned long gcd = std::__gcd(C, D);
  const unsigned long lcm = (C / gcd) * (D / gcd) * gcd;
  const unsigned long CD_num = my_func(A, B, lcm);

  std::cout << (B - A + 1) - (C_num + D_num - CD_num) << std::endl;

  return 0;
}
