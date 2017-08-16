import chainer
from chainer.links import VGG16Layers
from model.fcn_model import FCN32s
from dataset.voc import VOC2012ClassSeg
import chainer.links as L
from chainer.training import extensions

def init_from_vgg16(model, vgg16_model):
    for l in model.children():
        if l.name.startswith('conv'):
            l1 = getattr(vgg16_model, l.name)
            l2 = getattr(model, l.name)
            assert l1.W.shape == l2.W.shape
            assert l1.b.shape == l2.b.shape
            l2.W.data[...] = l1.W.data[...]
            l2.b.data[...] = l1.b.data[...]
        elif l.name in ['fc6', 'fc7']:
            l1 = getattr(vgg16_model, l.name)
            l2 = getattr(model, l.name)
            assert l1.W.size == l2.W.size
            assert l1.b.size == l2.b.size
            l2.W.data[...] = l1.W.data.reshape(l2.W.shape)[...]
            l2.b.data[...] = l1.b.data.reshape(l2.b.shape)[...]

if __name__ == "__main__":
    device = 0

    train = VOC2012ClassSeg("train")
    test  = VOC2012ClassSeg("val")

    vgg16_model = VGG16Layers()
    model = FCN32s(num_output=len(VOC2012ClassSeg.label_names))
    init_from_vgg16(model, vgg16_model)

    train_iter = chainer.iterators.SerialIterator(train, batch_size=1)
    test_iter  = chainer.iterators.SerialIterator(test,  batch_size=1, repeat=False, shuffle=False)
    model = L.Classifier(model)

    optimizer = chainer.optimizers.Adam(alpha=1e-5)
    optimizer.setup(model)
    updater = chainer.training.StandardUpdater(train_iter, optimizer, device=device)
    trainer = chainer.training.Trainer(updater, (100, 'epoch'), out="result")

    trainer.extend(extensions.Evaluator(test_iter, model, device=device))
    trainer.extend(extensions.dump_graph('main/loss'))
    trainer.extend(extensions.snapshot(), trigger=(10, 'epoch'))
    trainer.extend(extensions.snapshot_object(model, 'model_iter_{.updater.iteration}'), trigger=(10, 'epoch'))
    trainer.extend(extensions.LogReport())
    trainer.extend(extensions.PrintReport(['epoch', 'main/loss', 'validation/main/loss',
                                           'main/accuracy', 'validation/main/accuracy']))
    trainer.extend(extensions.ProgressBar())
    trainer.run()
