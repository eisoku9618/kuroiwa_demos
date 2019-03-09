#include <iostream>

int main() {
  unsigned int row_num, col_num;
  std::cin >> row_num >> col_num;
  unsigned int h, w;
  std::cin >> h >> w;

  std::cout << row_num * col_num - (h * col_num + w * row_num - h * w) << std::endl;

  return 0;
}
