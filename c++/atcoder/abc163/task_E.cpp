#include <iostream>
#include <vector>
#include <queue>

int main() {
  int N;
  std::cin >> N;
  std::vector<int> A_array(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> A_array.at(i);
  }

  std::priority_queue<std::pair<int, int>> que;
  for (int i = 0; i < N; ++i) {
    que.emplace(A_array[i], i);
  }

  // dp[x][y]: 強い順に(x+y)人を選び，左にx人，右にy人おいたときの最大値
  std::vector<std::vector<long long>> dp(N + 1, std::vector<long long>(N + 1, 0));
  for (int sum = 1; sum <= N; ++sum) {
    const auto current = que.top();
    que.pop();
    for (int i = 0; i <= sum; ++i) {
      const int x = i;
      const int y = sum - i;
      if (x > 0) {
        dp[x][y] = std::max(dp[x][y], dp[x - 1][y] + current.first * std::abs(current.second - (x - 1)));
      }
      if (y > 0) {
        dp[x][y] = std::max(dp[x][y], dp[x][y - 1] + current.first * std::abs(N - 1 - (y - 1) - current.second));
      }
    }
  }

  long long ans = 0;
  for (int i = 0; i <= N; ++i) {
    ans = std::max(ans, dp[i][N - i]);
  }

  std::cout << ans << std::endl;

  return 0;
}
