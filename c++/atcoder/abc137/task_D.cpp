#include <iostream>
#include <vector>
#include <queue>

int main() {
  unsigned int N, M;
  std::cin >> N >> M;

  std::vector<std::vector<unsigned int>> day_jobs(100000 + 5);
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int a, b;
    std::cin >> a >> b;
    day_jobs.at(a).push_back(b);
  }

  std::priority_queue<unsigned int> job_queue;
  unsigned long long sum = 0;
  for (unsigned int i = 1; i <= M; ++i) {
    for (auto x : day_jobs.at(i)) {
      job_queue.push(x);
    }
    if (!job_queue.empty()) {
      sum += job_queue.top();
      job_queue.pop();
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
