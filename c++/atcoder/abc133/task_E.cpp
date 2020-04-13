#include <iostream>
#include <vector>

const long long mod = 1e9 + 7;
unsigned int K = 0;
std::vector<int> to[100005];
unsigned long ans = 1;

long long permutation(int n, int r) {
  long long ret = 1;
  for (unsigned int i = 0; i < r; ++i) {
    ret = (ret * (n - i)) % mod;
  }
  return ret;
}

void dfs(int node, int parent) {
  const std::vector<int>& children = to[node];
  // childrenがいない末端から進んでいく
  for (size_t i = 0; i < children.size(); ++i) {
    const int& child = children.at(i);
    if (child == parent) {
      continue;
    }
    dfs(child, node);
  }

  // calc nPr
  int n;                        // 色の候補
  if (parent == -1) {
    // rootの分を含めて候補はK個
    n = K;
  } else {
    // 親とその親の色は選べない
    n = K - 2;
  }

  int r;                        // 塗る対象
  if (parent == -1) {
    // rootも入れるので対象は+1
    r = children.size() + 1;
  } else {
    // 親はすでに塗ってあるので-1
    r = children.size() - 1;
  }

  ans = (ans * permutation(n, r)) % mod;
}

int main() {
  int N;
  std::cin >> N >> K;
  for (int i = 0; i < N - 1; ++i) {
    int a, b;
    std::cin >> a >> b;
    a -= 1;
    b -= 1;
    to[a].push_back(b);
    to[b].push_back(a);
  }

  dfs(0, -1);

  std::cout << ans << std::endl;

  return 0;
}
