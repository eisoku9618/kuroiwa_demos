https://atcoder.jp/contests/abc141/tasks

```
g++ -std=gnu++17 task_A.cpp && ./a.out
cat task_A.cpp | xsel -b --clipboard
```

# memo

## D
- prioty queueでいける
   - https://github.com/eisoku9618/kuroiwa_demos/blob/master/c%2B%2B/atcoder/abc137/README.md
- 追加： O(log n)
- 削除： O(log n)
- 最大値取得: O(1)

- 最大値取得がM回なのでO(1) * M
- 削除がM回なのでO(log n) * M
- 追加がM回なのでO(log n) * M
- 合計は O(M log n) = O (10^5 log 10^5)となる
