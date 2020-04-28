#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> to[200005];
std::unordered_map<unsigned int, unsigned long> counter_map;
std::unordered_map<unsigned int, unsigned long> score_map;

void dfs(int node, int parent, unsigned long current) {
  if (counter_map.count(node) != 0) {
    current += counter_map.at(node);
  }
  score_map.at(node) = current;
  const std::vector<int>& children = to[node];
  // childrenがいない末端から進んでいく
  for (size_t i = 0; i < children.size(); ++i) {
    const int& child = children.at(i);
    if (child == parent) {
      continue;
    }
    dfs(child, node, current);
  }
}

int main() {
  unsigned int N, Q;
  std::cin >> N >> Q;

  for (unsigned int i = 0; i < N - 1; ++i) {
    unsigned int a, b;
    std::cin >> a >> b;
    a -= 1;
    b -= 1;
    to[a].push_back(b);
    to[b].push_back(a);
  }

  for (unsigned int i = 0; i < Q; ++i) {
    unsigned int p, x;
    std::cin >> p >> x;
    p -= 1;
    if (counter_map.count(p) == 0) {
      counter_map.emplace(p, x);
    } else {
      counter_map.at(p) += x;
    }
  }

  for (unsigned int i = 0; i < N; ++i) {
    score_map.emplace(i, 0);
  }

  dfs(0, -1, 0);

  for (unsigned int i = 0; i < N; ++i) {
    std::cout << score_map.at(i);
    if (i != N - 1) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;

  return 0;
}
