import chainer
from chainer.links.connection.convolution_2d import Convolution2D
from chainer.links.connection.deconvolution_2d import Deconvolution2D
from chainer.functions.activation.relu import relu
from chainer.functions.noise.dropout import dropout
from chainer.functions.pooling.max_pooling_2d import max_pooling_2d
from initializers.weight import UpsamplingDeconvWeight
import collections

class FCN32s(chainer.link.Chain):
    """
    Fully Convolutional Networks for Semantic Segmentation
    https://people.eecs.berkeley.edu/~jonlong/long_shelhamer_fcn.pdf
    """
    def __init__(self, num_output=40):
        init = chainer.initializers.constant.Zero()
        kwargs = {'initialW': init, 'initial_bias': init}
        super(FCN32s, self).__init__()
        with self.init_scope():
            # https://github.com/shelhamer/fcn.berkeleyvision.org/blob/master/voc-fcn32s/net.py
            self.conv1_1 = Convolution2D(   3,   64, ksize=3, stride=1, pad=1, **kwargs)
            self.conv1_2 = Convolution2D(  64,   64, ksize=3, stride=1, pad=1, **kwargs)

            self.conv2_1 = Convolution2D(  64,  128, ksize=3, stride=1, pad=1, **kwargs)
            self.conv2_2 = Convolution2D( 128,  128, ksize=3, stride=1, pad=1, **kwargs)

            self.conv3_1 = Convolution2D( 128,  256, ksize=3, stride=1, pad=1, **kwargs)
            self.conv3_2 = Convolution2D( 256,  256, ksize=3, stride=1, pad=1, **kwargs)
            self.conv3_3 = Convolution2D( 256,  256, ksize=3, stride=1, pad=1, **kwargs)

            self.conv4_1 = Convolution2D( 256,  512, ksize=3, stride=1, pad=1, **kwargs)
            self.conv4_2 = Convolution2D( 512,  512, ksize=3, stride=1, pad=1, **kwargs)
            self.conv4_3 = Convolution2D( 512,  512, ksize=3, stride=1, pad=1, **kwargs)

            self.conv5_1 = Convolution2D( 512,  512, ksize=3, stride=1, pad=1, **kwargs)
            self.conv5_2 = Convolution2D( 512,  512, ksize=3, stride=1, pad=1, **kwargs)
            self.conv5_3 = Convolution2D( 512,  512, ksize=3, stride=1, pad=1, **kwargs)

            # http://cs231n.github.io/convolutional-networks/#convert
            self.fc6     = Convolution2D( 512, 4096, ksize=7, stride=1, pad=0, **kwargs)
            self.fc7     = Convolution2D(4096, 4096, ksize=1, stride=1, pad=0, **kwargs)
            self.score_fr = Convolution2D(4096, num_output, ksize=1, stride=1, pad=0, **kwargs)
            # http://warmspringwinds.github.io/tensorflow/tf-slim/2016/11/22/upsampling-and-image-segmentation-with-tensorflow-and-tf-slim/
            self.upscore  = Deconvolution2D(num_output, num_output, ksize=224, stride=32, pad=0,
                                            nobias=True,
                                            initialW=UpsamplingDeconvWeight())

    def __call__(self, x):
        # conv1
        h = relu(self.conv1_1(x))
        h = relu(self.conv1_2(h))
        h = max_pooling_2d(h, 2, stride=2, pad=0)

        # conv2
        h = relu(self.conv2_1(h))
        h = relu(self.conv2_2(h))
        h = max_pooling_2d(h, 2, stride=2, pad=0)

        # conv3
        h = relu(self.conv3_1(h))
        h = relu(self.conv3_2(h))
        h = relu(self.conv3_3(h))
        h = max_pooling_2d(h, 2, stride=2, pad=0)

        # conv4
        h = relu(self.conv4_1(h))
        h = relu(self.conv4_2(h))
        h = relu(self.conv4_3(h))
        h = max_pooling_2d(h, 2, stride=2, pad=0)

        # conv5
        h = relu(self.conv5_1(h))
        h = relu(self.conv5_2(h))
        h = relu(self.conv5_3(h))
        h = max_pooling_2d(h, 2, stride=2, pad=0)

        # fc6
        h = relu(self.fc6(h))
        h = dropout(h, ratio=.5)

        # fc7
        h = relu(self.fc7(h))
        h = dropout(h, ratio=.5)

        # score_fr
        h = self.score_fr(h)

        # upscore
        h = self.upscore(h)
        return h
