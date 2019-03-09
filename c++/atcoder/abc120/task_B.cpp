#include <iostream>
#include <algorithm>

int main() {
  unsigned int a, b, k;
  std::cin >> a >> b >> k;

  unsigned int counter = 1;
  unsigned int ans = std::__gcd(a, b);

  while (counter != k) {
    ans -= 1;
    if (a % ans == 0 && b % ans == 0) {
      counter += 1;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
