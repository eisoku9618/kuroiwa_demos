#include <iostream>
#include <vector>
#include <queue>

int main() {
  int N, M;
  std::cin >> N >> M;
  std::vector<std::vector<int>> graph(N);
  for (int i = 0; i < M; ++i) {
    int A, B;
    std::cin >> A >> B;
    A -= 1;
    B -= 1;
    graph[A].push_back(B);
    graph[B].push_back(A);
  }

  // BFS のためのデータ構造
  std::vector<int> dist(N, -1); // 全頂点を「未訪問」に初期化
  std::queue<int> que;

  // 初期条件 (頂点 0 を初期ノードとする)
  dist[0] = 0;
  que.push(0); // 0 を橙色頂点にする

  int counter = 1;
  // BFS 開始 (キューが空になるまで探索を行う)
  while (!que.empty()) {
    const int v = que.front(); // キューから先頭頂点を取り出す
    que.pop();
    // v から辿れる頂点をすべて調べる
    for (const int next : graph[v]) {
      if (dist[next] != -1) {
        continue; // すでに発見済みの頂点は探索しない
      }
      // 新たな白色頂点 nv について距離情報を更新してキューに追加する
      dist[next] = v + 1;
      que.push(next);
      counter += 1;
    }
  }

  if (counter != N) {
    std::cout << "No" << std::endl;
  } else {
    std::cout << "Yes" << std::endl;
    for (int i = 1; i < N; ++i) {
      std::cout << dist[i] << std::endl;
    }
  }
  return 0;
}
