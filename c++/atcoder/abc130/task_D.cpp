#include <iostream>
#include <vector>

int main() {
  unsigned long n, k;
  std::cin >> n >> k;

  std::vector<unsigned long> a_array;
  for (unsigned long i = 0; i < n; ++i) {
    unsigned long ai;
    std::cin >> ai;
    a_array.push_back(ai);
  }

  unsigned long counter = 0;
  unsigned long sum = 0;
  long head = 0;
  for (long tail = 0; tail < n; ++tail) {
    while (sum < k) {
      if (head == n) {
        break;
      }
      sum += a_array.at(head);
      head++;
    }
    if (sum < k) {
      break;
    }
    counter += n - head + 1;
    sum -= a_array.at(tail);
  }

  std::cout << counter << std::endl;

  return 0;
}
