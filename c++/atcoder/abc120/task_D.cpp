#include <iostream>
#include <vector>
#include <algorithm>

class UnionFind {
public:
  UnionFind(const unsigned int n) : mParent(std::vector<int>(n, -1)) {
  }

  // indexがどのグループに属しているか調べる
  unsigned int GetRoot(const unsigned int index) {
    if (mParent.at(index) < 0) {
      return index;
    } else {
      mParent.at(index) = GetRoot(mParent.at(index));
      return mParent.at(index);
    }
  }

  // indexの属しているグループの頂点数を調べる
  unsigned int GetSize(const unsigned int index) {
    return -1 * mParent.at(GetRoot(index));
  }

  bool Connect(const unsigned int index_a, const unsigned int index_b) {
    // fromとtoを直接つなぐのではなく，root(index_a)にroot(index_b)をくっつける．
    unsigned int a_root = GetRoot(index_a);
    unsigned int b_root = GetRoot(index_b);
    if (a_root == b_root) {
      return false;
    }

    // 頂点数が多い方をAとしたい
    if (GetRoot(a_root) < GetRoot(b_root)) {
      std::swap(a_root, b_root);
    }

    mParent.at(a_root) += mParent.at(b_root);
    mParent.at(b_root) = a_root;

    return true;
  }

private:
  // 親の番号を格納する．親だった場合は-（その集合のサイズ）．
  std::vector<int> mParent;
};


int main() {
  unsigned int n, m;
  std::cin >> n >> m;

  std::vector<unsigned int> a_array(m), b_array(m);
  for (unsigned int i = 0; i < m; ++i) {
    std::cin >> a_array.at(i) >> b_array.at(i);
    a_array.at(i) -= 1;
    b_array.at(i) -= 1;
  }

  UnionFind uf(n);
  std::vector<unsigned long> ans(m);
  ans.at(m - 1) = static_cast<unsigned long>(n) * (n - 1) / 2;
  for (unsigned int i = m - 1; i > 0; --i) {
    const unsigned int& a = a_array.at(i);
    const unsigned int& b = b_array.at(i);

    const unsigned int a_size = uf.GetSize(a);
    const unsigned int b_size = uf.GetSize(b);

    if (uf.GetRoot(a) != uf.GetRoot(b)) {
      ans.at(i - 1) = ans.at(i) - static_cast<unsigned long>(a_size) * b_size;
      uf.Connect(a, b);
    } else {
      ans.at(i - 1) = ans.at(i);
    }
  }

  for (unsigned int i = 0; i < m; ++i) {
    std::cout << ans.at(i) << std::endl;
  }

  return 0;
}
