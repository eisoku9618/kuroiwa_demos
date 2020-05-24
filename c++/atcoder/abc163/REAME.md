https://atcoder.jp/contests/abc163/tasks

# memo

## D
- 小さい数で実験，の考え方が大事だった

## E
- dpにする経験が足りなかった
- 普通にやると2^nかかるが，
- dp[i][l][r]: 大きい方からi個まで左 or 右を決めて左をl回，右をr回使ったときの最大値
- == dp[i][l]: 大きい方からi個まで左 or 右を決めて左をl回，右をi-l回使ったときの最大値
- とすることでメモできて計算量を減らせる O(n^2)

- sortしたときにindexも欲しいケースは，std::vector<pair<int, int>>とすればよい
