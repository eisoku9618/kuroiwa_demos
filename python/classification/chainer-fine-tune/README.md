画像からタイトルを推測し，グリッド状に並べてPDFとして保存できるプログラム．

[![](http://img.youtube.com/vi/s0VbPafut7k/0.jpg)](https://www.youtube.com/watch?v=s0VbPafut7k)

特徴としては

- 今流行りのDeepLearningで自動的にタイトルを判断している
   - 手動でもタイトルを付けることができる
- グリッドサイズがスムーズに変更できる
   - グリッドサイズに応じて縦置き・横置きが自動的に切り替わる
- windowサイズに合わせて画像が拡大・縮小される
   - 内部で変換しているので入力画像のサイズは問わない．


## やっていること
[Caffeで学習済みのモデル](https://github.com/BVLC/caffe/tree/master/models/bvlc_reference_caffenet)をChainerに変換し，
CNNの最後の層の数を変えてChainerでfine-tuneしている．

fine-tuneなのでCPUでも現実的な時間でできて，[Caltech101](http://www.vision.caltech.edu/Image_Datasets/Caltech101/)の中から適当に選んだ20種類の画像を学習させた時にかかった時間は以下．
使ったCPUは Core i7-6700．

```bash
[00:23:19] epoch 1
train mean loss 1.33527529811, accuracy 0.646573606075
test mean loss 0.592220082096, accuracy 0.826722337582
[00:35:01] epoch 2
train mean loss 0.242164332325, accuracy 0.940355322688
test mean loss 0.330748546367, accuracy 0.897703539355
[00:46:47] epoch 3
train mean loss 0.112526594941, accuracy 0.972715723484
test mean loss 0.263797145921, accuracy 0.918580379889
[00:58:41] epoch 4
train mean loss 0.0464725346827, accuracy 0.989847710668
test mean loss 0.197412491541, accuracy 0.929018780807
```

## Operation Confirmed OS
- Windows 7 32bit
- Ubuntu 16.04 32bit
- Ubuntu 16.04 64bit

## How to Install
Python 2.7がインストールされている状態を仮定．

### windows
TODO

### ubuntu
TODO
