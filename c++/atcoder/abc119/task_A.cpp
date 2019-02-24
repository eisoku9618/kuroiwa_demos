#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

int main() {
  std::string s;
  std::cin >> s;
  std::stringstream ss(s);
  std::vector<int> v;
  std::string buffer;
  while(std::getline(ss, buffer, '/')) {
    v.push_back(atoi(buffer.c_str()));
  }

  const int year = v.at(0);
  const int month = v.at(1);
  const int day = v.at(2);

  if (year < 2019) {
    std::cout << "Heisei" << std::endl; // 2018
  } else if (year > 2019) {
    std::cout << "TBD" << std::endl; // 2020
  } else {                      // year == 2019
    if (month < 4) {
      std::cout << "Heisei" << std::endl; // 2019/03
    } else if (month > 4) {
      std::cout << "TBD" << std::endl; // 2019/05
    } else {                           // month == 4
      if (day < 30) {
        std::cout << "Heisei" << std::endl; // 2019/04/29
      } else if (day > 30) {
        std::cout << "TBD" << std::endl; // 2019/04/31 (not exist)
      } else {
        std::cout << "Heisei" << std::endl; // day == 30
      }
    }
  }

  return 0;
}
