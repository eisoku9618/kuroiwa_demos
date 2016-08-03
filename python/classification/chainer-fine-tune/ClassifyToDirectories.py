#! /usr/bin/env python
# -*- coding: utf-8 -*-

import os
import cPickle as pickle
import skimage.io
skimage.io.use_plugin("matplotlib")
from MyCNN import *
import imghdr
import csv
import argparse
import shutil
import multiprocessing
import datetime

# arg option
parser = argparse.ArgumentParser(description='classify all the pictures in SD card')
parser.add_argument('sdcard_path', type=str, help='sd card path')
parser.add_argument('dest_path', type=str, help='destination path')
args = parser.parse_args()

cpu_cnt = (lambda x: x - 1 if x > 1 else x)(multiprocessing.cpu_count())
dir_name = os.path.abspath(os.path.dirname(__file__))
my_model_list = [pickle.load(open(os.path.join(os.path.join(dir_name, 'config'), "new_model.pkl"), "rb")) for x in range(cpu_cnt)]
# my_model = pickle.load(open(os.path.join(os.path.join(dir_name, 'config'), "new_model.pkl"), "rb"))

# store pictures in ./SDcard/xxx directory
store_dir_list = []
with open(os.path.join(os.path.join(dir_name, 'config'), "model_label.txt"), mode="r") as f:
    reader = csv.reader(f, delimiter=":")
    for row in reader:
        new_dir = os.path.join(os.path.join(args.dest_path, "SDcard"),
                               str(row[0]) + "_" + row[1])
        if not os.path.exists(new_dir):
            os.makedirs(new_dir)
        store_dir_list.append(os.path.join(dir_name, new_dir))

def getClassIndex(model, fname):
    try:
        img = skimage.img_as_float(skimage.io.imread(fname, as_grey=False)).astype(np.float32)
    except ValueError:
        print fname
        exit(-1)
    if img.ndim == 2:
        img = img[:, :, np.newaxis]
        img = np.tile(img, (1, 1, 3))
    elif img.shape[2] == 4:
        img = img[:, :, :3]
    h, loss = model([img], np.array([0], dtype=np.int32))
    ans = h.data.flatten().tolist()
    return ans

def copyPictures(model, d):
    print "start {} at {}".format(d.split(os.sep)[-1],
                                  datetime.datetime.now().strftime("%H:%M:%S"))
    img_list = filter(lambda img: imghdr.what(os.path.join(d, img)), os.listdir(d))
    for img in img_list:
        img_full_path = os.path.join(d, img)
        ans = getClassIndex(model, img_full_path)
        diff = int(sorted(ans)[-1] - sorted(ans)[-2])
        cls = ans.index(max(ans))
        new_img_name = str(diff) + "_" + d.split(os.sep)[-1]  + "_" + img.split(os.sep)[-1]
        shutil.copy(img_full_path, os.path.join(store_dir_list[cls], new_img_name))
    print "     finish {} at {}".format(d.split(os.sep)[-1],
                                        datetime.datetime.now().strftime("%H:%M:%S"))

dir_list = filter(lambda d: os.path.isdir(d),
                  [os.path.join(args.sdcard_path, d) for d in os.listdir(args.sdcard_path)])
for i in range(0, len(dir_list), cpu_cnt):
    worker_list = []
    for m, d in zip(my_model_list, dir_list[i:i+cpu_cnt]):
        worker = multiprocessing.Process(target=copyPictures,
                                         args=(m, d))
        worker_list.append(worker)
        worker.start()
    [w.join() for w in worker_list]
