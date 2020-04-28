#include <iostream>
#include <vector>
#include <queue>

int main() {
  unsigned int N, M;
  std::cin >> N >> M;

  std::priority_queue<unsigned int> A_que;
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int A;
    std::cin >> A;
    A_que.push(A);
  }

  for (unsigned int i = 0; i < M; ++i) {
    unsigned int cost = A_que.top();
    A_que.pop();
    A_que.push(cost / 2);
  }

  unsigned long sum = 0;
  for (unsigned int i = 0; i < N; ++i) {
    sum += A_que.top();
    A_que.pop();
  }

  std::cout << sum << std::endl;

  return 0;
}
