https://atcoder.jp/contests/abc118/tasks

# memo

## C
- 最小の2つの数字の最大公約数が答えと誤認識してWA
- gcdはc++17からstdに実装されているがc++11でも__gcdという関数名で使えるらしい

## D
- 噂のDP．慣れが必要そう．
- pythonのitertoolsを使って全探索は出来たが，C++での実装が出来なかった
   - 以下，itertoolsのproduct的なもののC++実装の参考URL
      - https://gist.github.com/thirdwing/953b146ba39c5f5ff562
      - https://stackoverflow.com/questions/5279051/how-can-i-create-cartesian-product-of-vector-of-vectors
- unsigned longでも足りない場合はstringを使うと良い
