#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  int A, B, H, M;
  std::cin >> A >> B >> H >> M;

  const double hour_theta = static_cast<double>(H * 60 + M) / (12 * 60) * 2 * M_PI;
  const double minute_theta = static_cast<double>(M) / 60 * 2 * M_PI;

  const double diff_cos = A * std::cos(hour_theta) - B * std::cos(minute_theta);
  const double diff_sin = A * std::sin(hour_theta) - B * std::sin(minute_theta);
  std::cout << std::fixed << std::setprecision(10) << std::sqrt(diff_cos * diff_cos + diff_sin * diff_sin) << std::endl;

  return 0;
}
