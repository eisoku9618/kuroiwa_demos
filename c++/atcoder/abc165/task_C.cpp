#include <iostream>
#include <vector>

int N, M, Q;

unsigned long max = 0;

std::vector<int> A_array;
std::vector<int> B_array;
std::vector<int> C_array;
std::vector<unsigned long> D_array;

unsigned long calc_point(const std::vector<int>& my_array) {
  unsigned long sum = 0;
  for (int i = 0 ; i < Q; ++i) {
    if (C_array.at(i) == my_array.at(B_array.at(i)) - my_array.at(A_array.at(i))) {
      sum += D_array.at(i);
    }
  }
  return sum;
}


void dfs(int node, int depth, std::vector<int>& my_array) {
  if (depth == N) {
    max = std::max(max, calc_point(my_array));
    return;
  }

  for (int i = node; i <= M; ++i) {
    my_array.at(depth) = i;
    dfs(i, depth + 1, my_array);
  }
}

int main() {
  std::cin >> N >> M >> Q;

  A_array.resize(Q);
  B_array.resize(Q);
  C_array.resize(Q);
  D_array.resize(Q);
  for (int i = 0; i < Q; ++i) {
    std::cin >> A_array.at(i) >> B_array.at(i) >> C_array.at(i) >> D_array.at(i);
    A_array.at(i) -= 1;
    B_array.at(i) -= 1;
  }

  std::vector<int> my_array(N, 0);

  dfs(1, 0, my_array);

  std::cout << max << std::endl;

  return 0;
}
