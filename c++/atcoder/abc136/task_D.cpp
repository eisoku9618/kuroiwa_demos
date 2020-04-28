#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string S;
  std::cin >> S;

  std::vector<long long> key_pos_array;
  const std::string key = "RL";
  std::string::size_type pos = S.find(key);
  while (pos != std::string::npos) {
    key_pos_array.push_back(pos);
    pos = S.find(key, pos + key.length());
  }

  std::vector<long long> key_2_pos_array;
  key_2_pos_array.push_back(-1);
  const std::string key_2 = "LR";
  std::string::size_type pos_2 = S.find(key_2);
  while (pos_2 != std::string::npos) {
    key_2_pos_array.push_back(pos_2);
    pos_2 = S.find(key_2, pos_2 + key_2.length());
  }

  for (unsigned int i = 0; i < key_pos_array.size(); ++i) {
    const unsigned int num_R = key_pos_array.at(i) - key_2_pos_array.at(i);
    unsigned int num_L;
    if (i + 1 != key_pos_array.size()) {
      num_L = key_2_pos_array.at(i + 1) - key_pos_array.at(i);
    } else {
      num_L = (S.length() - 1) - key_pos_array.at(i);
    }

    const unsigned int count_R_pos = num_R / 2 + num_R % 2 + num_L / 2;
    const unsigned int count_L_pos = num_R / 2 + num_L / 2 + num_L % 2;
    for (unsigned int j = 1; j < num_R; ++j) {
      std::cout << "0 ";
    }
    std::cout << count_R_pos << " " << count_L_pos << " ";
    for (unsigned int j = 1; j < num_L; ++j) {
      if ((i + 1 != key_pos_array.size()) || (j + 1 != num_L)) {
        std::cout << "0 ";
      } else {
        std::cout << "0";
      }
    }
  }
  std::cout << std::endl;

  return 0;
}
