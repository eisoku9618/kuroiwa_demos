#include <iostream>
#include <vector>

std::vector<std::vector<long long>> dp(200005, std::vector<long long>(2, 0));
std::vector<std::vector<std::vector<long long>>> dp_skip(200005,
                                                         std::vector<std::vector<long long>>(2,
                                                                                             std::vector<long long>(2, 0)));

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<long long> A_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> A_array.at(i);
  }

  if (N % 2 == 0) {
    // initialization
    dp.at(0).at(0) = A_array.at(0);
    dp.at(0).at(1) = A_array.at(1);
    // dp loop
    for (unsigned int i = 1; i < N / 2; ++i) {
      dp.at(i).at(0) = dp.at(i - 1).at(0) + A_array.at(i * 2);
      dp.at(i).at(1) = std::max(dp.at(i - 1).at(0), dp.at(i - 1).at(1)) + A_array.at(i * 2 + 1);
    }
    // get answer
    std::cout << std::max(dp.at(N / 2 - 1).at(0), dp.at(N / 2 - 1).at(1)) << std::endl;
  } else {
    // initialization
    dp_skip.at(0).at(0).at(0) = A_array.at(0);
    dp_skip.at(0).at(1).at(0) = A_array.at(1);
    dp_skip.at(0).at(0).at(1) = 0;
    dp_skip.at(0).at(1).at(1) = 0;
    // dp loop
    for (unsigned int i = 1; i < N / 2; ++i) {
      dp_skip.at(i).at(0).at(0) = dp_skip.at(i - 1).at(0).at(0) + A_array.at(i * 2);
      dp_skip.at(i).at(1).at(0) = std::max(dp_skip.at(i - 1).at(0).at(0),
                                           dp_skip.at(i - 1).at(1).at(0))
        + A_array.at(i * 2 + 1);
      const long long prev_max = std::max(dp_skip.at(i - 1).at(0).at(0),
                                          dp_skip.at(i - 1).at(1).at(0));
      dp_skip.at(i).at(0).at(1) = std::max(dp_skip.at(i - 1).at(0).at(1) + A_array.at(i * 2),
                                           prev_max);
      dp_skip.at(i).at(1).at(1) = std::max(std::max(dp_skip.at(i - 1).at(0).at(1),
                                                    dp_skip.at(i - 1).at(1).at(1))
                                           + A_array.at(i * 2 + 1),
                                           prev_max);
    }
    // get answer
    dp_skip.at(N / 2 - 1).at(0).at(1) += A_array.at(N - 1);
    const long long no_skip_max = std::max(dp_skip.at(N / 2 - 1).at(0).at(0), dp_skip.at(N / 2 - 1).at(1).at(0));
    std::cout << std::max(no_skip_max, dp_skip.at(N / 2 - 1).at(0).at(1)) << std::endl;
  }

  return 0;
}
