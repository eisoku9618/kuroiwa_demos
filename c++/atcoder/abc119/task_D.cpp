#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

int main() {
  unsigned int a, b, q;
  std::cin >> a >> b >> q;

  std::vector<long> s_array(a);
  for (size_t i = 0; i < a; ++i) {
    std::cin >> s_array.at(i);
  }
  std::vector<long> t_array(b);
  for (size_t i = 0; i < b; ++i) {
    std::cin >> t_array.at(i);
  }
  std::vector<long> x_array(q);
  for (size_t i = 0; i < q; ++i) {
    std::cin >> x_array.at(i);
  }
  s_array.insert(s_array.begin(), -1 * 1e+10);
  t_array.insert(t_array.begin(), -1 * 1e+10);
  s_array.push_back(2 * 1e+10);
  t_array.push_back(2 * 1e+10);

  // for (size_t i = 0; i < s_array.size(); ++i) {
  //   std::cout << s_array.at(i) << " ";
  // }
  // std::cout << std::endl;

  // for (size_t i = 0; i < t_array.size(); ++i) {
  //   std::cout << t_array.at(i) << " ";
  // }
  // std::cout << std::endl;

  // for (size_t i = 0; i < x_array.size(); ++i) {
  //   std::cout << x_array.at(i) << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "" << std::endl;

  for (const long& x : x_array) {
    std::vector<long>::const_iterator s_east_itr = std::lower_bound(s_array.begin(), s_array.end(), x);
    const long s_east = *s_east_itr;
    const long s_west = *(s_east_itr - 1);
    std::vector<long>::const_iterator t_east_itr = std::lower_bound(t_array.begin(), t_array.end(), x);
    const long t_east = *t_east_itr;
    const long t_west = *(t_east_itr - 1);

    std::vector<long> ans_array;
    for (const long& s : {s_east, s_west}) {
      for (const long& t : {t_east, t_west}) {
        const long cand_1 = std::abs(s - x) + std::abs(t - s);
        const long cand_2 = std::abs(t - x) + std::abs(s - t);
        ans_array.push_back(std::min(cand_1, cand_2));
      }
    }
    std::cout << *std::min_element(std::begin(ans_array), std::end(ans_array)) << std::endl;
  }

  return 0;
}
