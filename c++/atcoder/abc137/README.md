https://atcoder.jp/contests/abc137/tasks

```
g++ -std=gnu++17 task_A.cpp && ./a.out
cat task_A.cpp | xsel -b --clipboard
```

# memo

## C
- unordered_mapというのがある
- mapとunordered_mapの違い
   - mapは赤黒木という平衡2分探索木を採用していて，検索にO(log n)かかる．orderは整頓される．
   - unordered_mapはhash tableで検索するので，O(1)で早い．orderは整頓されない．

## D
- priority queueを覚えよう
   - https://ufcpp.net/study/algorithm/col_heap.html
- このコレクションはheapで実現されている
   - heapとは以下の4条件．ヒープソートをイメージしたら覚えやすい．
     1. 2分木
     2. 葉を除いて子ノードは2つ
     3. 葉は左詰め
     4. 親は子よりも大きな値
- なので，挿入も削除もO(log n)でできる
