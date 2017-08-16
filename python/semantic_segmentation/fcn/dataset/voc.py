import chainer
from chainer.dataset import DatasetMixin
import os
import scipy.misc
import numpy as np
import collections
import PIL

class VOC2012ClassSeg(DatasetMixin):
    label_names = [
        'background',
        'aeroplane',
        'bicycle',
        'bird',
        'boat',
        'bottle',
        'bus',
        'car',
        'cat',
        'chair',
        'cow',
        'diningtable',
        'dog',
        'horse',
        'motorbike',
        'person',
        'potted plant',
        'sheep',
        'sofa',
        'train',
        'tv/monitor',
    ]
    mean_bgr = np.array((104.00698793, 116.66876762, 122.67891434))

    def __init__(self, split="train"):
        assert split in ('train', 'val')
        dataset_dir = os.path.join(os.path.dirname(os.path.abspath( __file__ )),
                                   "data/VOCdevkit/VOC2012")
        imgsets_file = os.path.join(dataset_dir, 'ImageSets/Segmentation/%s.txt' % split)
        self.files = []
        for did in open(imgsets_file):
            did = did.strip()
            img_file = os.path.join(dataset_dir, 'JPEGImages/%s.jpg' % did)
            lbl_file = os.path.join(dataset_dir, 'SegmentationClass/%s.png' % did)
            self.files.append({
                'img': img_file,
                'lbl': lbl_file,
            })

    def __len__(self):
        return len(self.files)

    def get_example(self, i):
        data_file = self.files[i]
        img_file = data_file["img"]
        lbl_file = data_file["lbl"]

        img = PIL.Image.open(img_file)
        img = np.array(img, dtype=np.uint8)
        img = scipy.misc.imresize(img, (224, 224))
        datum = img.astype(np.float32)
        datum = datum[:,:,::-1]
        datum -= self.mean_bgr
        datum = datum.transpose((2, 0, 1))

        lbl = PIL.Image.open(lbl_file)
        lbl = np.array(lbl, dtype=np.int32)
        lbl[lbl == 255] = -1
        lbl = scipy.misc.imresize(lbl, (224, 224), mode="F", interp="nearest")
        lbl = lbl.astype(np.int32)

        return datum, lbl
