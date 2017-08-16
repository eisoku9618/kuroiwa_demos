- https://github.com/wkentaro/fcn
- http://www.mathgram.xyz/entry/chainer/fcn
- http://seiya-kumada.blogspot.jp/2016/03/fully-convolutional-networks-chainer.html
- http://www.mathgram.xyz/entry/keras/fcn

を参考にして作ったもの．ほぼコピペ．

実際にコードを追うのが目的．


http://host.robots.ox.ac.uk/pascal/VOC/voc2012/index.html にある http://host.robots.ox.ac.uk/pascal/VOC/voc2012/VOCtrainval_11-May-2012.tar のリンクからダウンロードできるファイルを展開して，
``dataset/data/VOCdevkit/VOC2012/``的な感じで置く．

あとは

```python
python train_fcn32s.py
```

で動き始める．
