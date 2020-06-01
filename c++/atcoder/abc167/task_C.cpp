#include <iostream>
#include <vector>

void vector_sum(const std::vector<int>& a, std::vector<int>& sum) {
  for (int i = 0; i < a.size(); ++i) {
    sum[i] += a[i];
  }
}

int main() {
  int N, M, X;
  std::cin >> N >> M >> X;

  std::vector<int> C_array(N);
  std::vector<std::vector<int>> A_array(N, std::vector<int>(M, 0));

  for (int i = 0; i < N; ++i) {
    std::cin >> C_array[i];
    for (int j = 0; j < M; ++j) {
      std::cin >> A_array[i][j];
    }
  }

  const int inf = 100000000;
  int max_cost = inf;
  for (int bit = 0; bit < (1 << N); ++bit) {
    std::vector<int> sum(M, 0);
    int cost = 0;
    for (int i = 0; i < N; ++i) {
      if (bit & (1 << i)) {
        vector_sum(A_array[i], sum);
        cost += C_array[i];
      }
    }
    bool ok = true;
    for (int i = 0; i < M; ++i) {
      if (sum[i] < X) {
        ok = false;
        break;
      }
    }
    if (ok) {
      max_cost = std::min(max_cost, cost);
    }
  }

  if (max_cost == inf) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << max_cost << std::endl;
  }

  return 0;
}
