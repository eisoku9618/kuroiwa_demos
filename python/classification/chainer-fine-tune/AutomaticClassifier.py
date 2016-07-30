#! /usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib
matplotlib.use("WXAgg")
import wx
import wx.grid
import wx.lib.newevent
import math
import os
import cPickle as pickle
import numpy as np
import skimage.io
import matplotlib.pyplot
import matplotlib.font_manager
import PIL.Image
import datetime
import webbrowser
import tempfile
import thread
import csv
from MyCNN import *
from matplotlib.backends.backend_pdf import PdfPages

# global variable
(MyThreadEvent, EVT_MY_THREAD) = wx.lib.newevent.NewEvent()
my_model = None
dir_name = os.path.abspath(os.path.dirname(__file__))
LABEL_FILE_PATH = os.path.join(os.path.join(dir_name, 'config'), 'model_label.txt')
with open(LABEL_FILE_PATH, mode="r") as f:
    reader = csv.reader(f, delimiter=":")
    dir_list = [row[1] for row in reader]

class MyThread(object):
    """
    See http://bty.sakura.ne.jp/wp/archives/626
    """
    def __init__(self, window):
        self.window = window

    def Start(self):
        thread.start_new_thread(self.Run, ())

    def Run(self):
        dir_name = os.path.abspath(os.path.dirname(__file__))
        NEW_MODEL_PATH = os.path.join(os.path.join(dir_name, 'config'), 'new_model.pkl')
        global my_model
        my_model = pickle.load(open(NEW_MODEL_PATH, "rb"))
        event = MyThreadEvent()
        wx.PostEvent(self.window, event)

def getClassIndex(model, fname):
    img = skimage.img_as_float(skimage.io.imread(fname, as_grey=False)).astype(np.float32)
    if img.ndim == 2:
        img = img[:, :, np.newaxis]
        img = np.tile(img, (1, 1, 3))
    elif img.shape[2] == 4:
        img = img[:, :, :3]
    h, loss = model([img], np.array([0], dtype=np.int32))
    ans = h.data.flatten().tolist()
    print ans
    return ans.index(max(ans))

class MyFileDropTarget(wx.FileDropTarget):
    def __init__(self, panel):
        wx.FileDropTarget.__init__(self)
        self.panel = panel

    def OnDropFiles(self, x, y, filenames):
        fname = filenames[0]
        if my_model:
            cls = getClassIndex(my_model, fname)
            self.panel.setPanel(fname, text=dir_list[cls])
        else:
            self.panel.setPanel(fname)

class MyMemory(object):
    def __init__(self, h_num, w_num, title_list, img_path_list):
        self.h_num = h_num
        self.w_num = w_num
        self.title_list = title_list
        self.img_path_list = img_path_list

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Classification", size=(800, 450))
        self.CreateStatusBar()

        self.sz = wx.BoxSizer(wx.VERTICAL)

        # assume 2 page at most
        self.mymemories = [None, None]

        # Menu Button : I don't use wx.Menu because it needs 2 mouse click steps for action
        btn_panel = wx.Panel(self, wx.ID_ANY)
        btn_sz = wx.BoxSizer(wx.HORIZONTAL)
        btn_tips = ["Start Print", "Reset", "Select Layout", "Go Back", "Go Forward", "Quit"]
        btn_arts = [wx.ART_PRINT, wx.ART_DELETE, wx.ART_LIST_VIEW, wx.ART_GO_BACK, wx.ART_GO_FORWARD, wx.ART_QUIT]
        btn_funcs = [self.onPrint, self.onReset, self.onLayout, self.onPrevNextCommon, self.onPrevNextCommon, self.onClose]
        for tip, art, func in zip(btn_tips, btn_arts, btn_funcs):
            bitmap = wx.ArtProvider.GetBitmap(art, size=(32, 32))
            btn = wx.BitmapButton(btn_panel, wx.ID_ANY, bitmap, size=(100, 50))
            btn.SetToolTip(wx.ToolTip(tip))
            btn.Bind(wx.EVT_BUTTON, func)
            if art == wx.ART_GO_BACK:
                self.gobackbtn = btn
                btn.Disable()
            if art == wx.ART_GO_FORWARD:
                self.goforwardbtn = btn
            btn_sz.Add(btn, flag=wx.GROW | wx.RIGHT, border=20)
        btn_panel.SetSizer(btn_sz)

        # The aspect ratio of root panel shoud be the one of A4
        self.__root_panel = wx.Panel(self, wx.ID_ANY, size=(1000*math.sqrt(2), 1000))
        self.__root_panel.SetBackgroundColour(wx.Colour(255, 255, 200))

        self.sz.Add(btn_panel, flag=wx.ALIGN_LEFT)
        self.sz.Add(self.__root_panel, flag=wx.SHAPED | wx.ALIGN_CENTER, proportion=1)
        self.SetSizer(self.sz)

        init_h = 3
        init_w = 4
        self.__panels = [ExplanationDrawingPanel(self.__root_panel) for i in range(init_h*init_w)]
        self.__root_layout = wx.GridSizer(init_h, init_w)
        for p in self.__panels:
            self.__root_layout.Add(p, flag=wx.SHAPED | wx.ALIGN_CENTER | wx.ALL, border=10)
            dt = MyFileDropTarget(p)
            p.SetDropTarget(dt)
        self.__root_panel.SetSizer(self.__root_layout)

        # about Loading CNN model Process
        self.Bind(wx.EVT_SHOW, self.onShow)
        self.Bind(wx.EVT_CLOSE, self.onClose)
        self.Bind(EVT_MY_THREAD, self.OnLoadComplete)

        # for Japanese fonts
        jp_font_list = [f for f in matplotlib.font_manager.findSystemFonts() if "mincho" in f]
        if len(jp_font_list) == 0:
            self.jp_font = None
        else:
            self.jp_font = jp_font_list[0]

    def OnLoadComplete(self, event):
        """
        Loading CNNmodel takes a lot of time, so push it to background process
        """
        message = "[{}] Complete model loading".format(datetime.datetime.now().strftime("%H:%M:%S"))
        print message
        self.SetStatusText(message)
        print dir_list
        self.__root_panel.SetBackgroundColour('white')
        for p in self.__panels:
            if not p.isTextCustomized():
                path = p.getImagePath()
                cls = getClassIndex(my_model, path)
                text = dir_list[cls]
                p.setPanel(path, text)

    def onShow(self, event):
        """
        Loading CNNmodel takes a lot of time, so push it to background process
        """
        dir_name = os.path.abspath(os.path.dirname(__file__))
        NEW_MODEL_PATH = os.path.join(os.path.join(dir_name, 'config'), 'new_model.pkl')
        message = "[{}] Loading {} in the backgroud ...".format(
            datetime.datetime.now().strftime("%H:%M:%S"),
            NEW_MODEL_PATH.split(os.sep)[-1])
        print message
        self.SetStatusText(message)
        if not os.path.exists(NEW_MODEL_PATH):
            message = "model is not found"
            print message
            self.SetStatusText(message)
        else:
            my_thread = MyThread(self)
            my_thread.Start()

    def onPrevNextCommon(self, event):
        if event.GetEventObject().GetToolTip().GetTip() == "Go Back":
            self.gobackbtn.Disable()
            self.goforwardbtn.Enable()
            memory_flag = 1
        elif event.GetEventObject().GetToolTip().GetTip() == "Go Forward":
            self.gobackbtn.Enable()
            self.goforwardbtn.Disable()
            memory_flag = 0
        h_num = self.__root_layout.GetRows()
        w_num = self.__root_layout.GetCols()
        title_list = [p.getText() for p in self.__panels]
        img_path_list = [p.getImagePath() for p in self.__panels]
        self.mymemories[memory_flag] = MyMemory(h_num, w_num, title_list, img_path_list)
        # clear pages
        self.onReset(None)
        if self.mymemories[1-memory_flag] != None:
            h_num = self.mymemories[1-memory_flag].h_num
            w_num = self.mymemories[1-memory_flag].w_num
            title_list = self.mymemories[1-memory_flag].title_list
            img_path_list = self.mymemories[1-memory_flag].img_path_list
            if h_num * 3 < w_num * 4:
                # Landscape
                new_size = wx.Size(1000*math.sqrt(2), 1000)
            else:
                # Portrait
                new_size = wx.Size(1000, 1000*math.sqrt(2))
            # ew have to detach before resize
            self.sz.Detach(self.__root_panel)
            self.__root_panel.SetSize(new_size)
            self.sz.Add(self.__root_panel, flag=wx.SHAPED | wx.ALIGN_CENTER, proportion=1)
            self.changeLayout(h_num, w_num)
            for p, tl, ipl in zip(self.__panels, title_list, img_path_list):
                if ipl != None:
                    p.setPanel(ipl, tl)
                else:
                    # no image in this case
                    pass

    def onClose(self, event):
        self.Destroy()
        exit(-1)                # we need this because webbrowser.open_new_tab preventsxs exit

    def printCommon(self, h_num, w_num, title_list, img_path_list):
        f, (axes) = matplotlib.pyplot.subplots(h_num, w_num)
        # See http://stackoverflow.com/questions/15571267/python-a4-size-for-a-plot
        if h_num * 3 < w_num * 4:
            f.set_size_inches(11.69, 8.27)
        else:
            f.set_size_inches(8.27, 11.69)
        ax_list = axes.flatten()
        for i, (title, img_path) in enumerate(zip(title_list, img_path_list)):
            if img_path:
                ax_list[i].imshow(PIL.Image.open(img_path))
            if w_num == 4:
                fontsize = 14
            elif w_num == 3:
                fontsize = 18
            else:
                fontsize = 20
            if self.jp_font:
                fp = matplotlib.font_manager.FontProperties(fname=self.jp_font)
                ax_list[i].set_xlabel(title, fontproperties=fp, fontsize=fontsize)
            else:
                ax_list[i].set_xlabel(title, fontsize=fontsize)
            ax_list[i].tick_params(labelbottom='off', labelleft='off')
            ax_list[i].get_xaxis().set_ticks_position('none')
            ax_list[i].get_yaxis().set_ticks_position('none')
            for s in ax_list[i].spines.values():
                s.set_visible(False)
        f.tight_layout()
        return f

    def printCurrentPage(self):
        h_num = self.__root_layout.GetRows()
        w_num = self.__root_layout.GetCols()
        title_list = [p.getText() for p in self.__panels]
        img_path_list = [p.getImagePath() for p in self.__panels]
        return self.printCommon(h_num, w_num, title_list, img_path_list)

    def printMemory(self, memory):
        h_num = memory.h_num
        w_num = memory.w_num
        title_list = memory.title_list
        img_path_list = memory.img_path_list
        return self.printCommon(h_num, w_num, title_list, img_path_list)

    def onPrint(self, event):
        now = datetime.datetime.now().strftime("%y-%m-%d_%H-%M-%S")
        out_fname = os.path.join(tempfile.gettempdir(), "output_{}.pdf".format(now))
        with PdfPages(out_fname) as pdf:
            if self.gobackbtn.IsEnabled() == False:
                # now is first page
                if self.mymemories[1] == None or len([x for x in [self.mymemories[1].img_path_list] if x != None]) == 0:
                    # we don't have second page
                    self.printCurrentPage()
                    pdf.savefig()
                else:
                    # we have second page
                    self.printCurrentPage()
                    pdf.savefig()
                    self.printMemory(self.mymemories[1])
                    pdf.savefig()
            else:
                # now is second page
                self.printMemory(self.mymemories[0])
                pdf.savefig()
                self.printCurrentPage()
                pdf.savefig()
            d = pdf.infodict()
            d['Title'] = 'Automatic Classification'
            d['Author'] = 'Eisoku Kuroiwa'
            d['Subject'] = 'with CNN'
            d['Keywords'] = 'python, chainer, caffe, wxpython, matplotlib, imagenet'
            d['CreationDate'] = datetime.datetime.now()
            d['ModDate'] = datetime.datetime.today()
        # See http://stackoverflow.com/questions/1679798/how-to-open-a-file-with-the-standard-application
        webbrowser.open_new_tab(out_fname)

    def onReset(self, event):
        for p in self.__panels:
            p.reset()

    def onLayout(self, event):
        dialog = LayoutSelectionDialog(self)
        try:
            res = dialog.ShowModal()
            if res == wx.ID_OK:
                if dialog.g10.GetValue() != "" and dialog.g12.GetValue() != "":
                    h_num = int(dialog.g10.GetValue())
                    w_num = int(dialog.g12.GetValue())
                    if h_num * 3 < w_num * 4:
                        # Landscape
                        new_size = wx.Size(1000*math.sqrt(2), 1000)
                    else:
                        # Portrait
                        new_size = wx.Size(1000, 1000*math.sqrt(2))
                    # ew have to detach before resize
                    self.sz.Detach(self.__root_panel)
                    self.__root_panel.SetSize(new_size)
                    self.sz.Add(self.__root_panel, flag=wx.SHAPED | wx.ALIGN_CENTER, proportion=1)
                    self.changeLayout(h_num, w_num)
        finally:
            dialog.Destroy()

    def changeLayout(self, h, w):
        if self.__root_layout.GetRows() == h and self.__root_layout.GetCols() == w:
            # I don't know why but we need this line ...
            self.sz.Layout()
            return
        # update sizer
        new_root_layout = wx.GridSizer(h, w)
        self.__root_panel.SetSizer(new_root_layout)
        self.__root_layout = new_root_layout
        # update panels
        new_panels = []
        for p in self.__panels:
            if p.getText() == "" or len(new_panels) == h * w:
                self.__root_layout.Remove(p)
                p.Destroy()
            else:
                new_panels.append(p)
        while len(new_panels) < h * w:
            new_panels.append(ExplanationDrawingPanel(self.__root_panel))
        self.__panels = new_panels
        # set panels to new layout
        for p in self.__panels:
            new_root_layout.Add(p, flag=wx.SHAPED | wx.ALIGN_CENTER | wx.ALL, border=10)
            dt = MyFileDropTarget(p)
            p.SetDropTarget(dt)
        # I don't know why but we need this line ...
        self.sz.Layout()

class ExplanationDrawingPanel(wx.Panel):
    """
    This class contains Image and Explanation
    """
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.ID_ANY, size=(-1, -1))
        layout = wx.BoxSizer(wx.VERTICAL)
        self.__button_img = MyImage(self)
        self.__text_expl = wx.ComboBox(self, wx.ID_ANY, "",
                                       choices=dir_list, style=wx.CB_DROPDOWN)
        layout.Add(self.__button_img, flag=wx.GROW | wx.ALIGN_CENTER, proportion=1)
        layout.Add(self.__text_expl, flag=wx.GROW, proportion=0)
        self.SetSizer(layout)

    def setPanel(self, fname, text=None):
        self.__button_img.setImage(fname)
        if text:
            self.__text_expl.SetValue(text)
        else:
            self.__text_expl.SetValue(fname.split(os.sep)[-1])

    def getImagePath(self):
        return self.__button_img.getImagePath()

    def getText(self):
        return self.__text_expl.GetValue()

    def isTextCustomized(self):
        text = self.__text_expl.GetValue()
        fname = self.getImagePath()
        if fname is None:
            return True
        else:
            return text != fname.split(os.sep)[-1]

    def reset(self):
        self.__button_img.reset()
        self.__text_expl.SetValue('')

class MyImage(wx.Window):
    """
    __img_raw  : raw image
    __cur_size : current best fit size
    """
    def __init__(self, parent):
        wx.Window.__init__(self, parent)
        self.__img_path = None
        default_img = wx.EmptyImage(400, 300) # black
        default_img.Replace(*(wx.BLACK.Get() + wx.WHITE.Get())) # convert to white
        self.__img_raw = default_img
        self.__cur_size = default_img.GetSize().Get()
        self.Bind(wx.EVT_SIZE, self.onResize)
        self.Bind(wx.EVT_PAINT, self.onPaint)

    def setImage(self, fname):
        self.__img_path = fname
        self.__img_raw = wx.Image(fname)
        # self.onPaint will be called after this function called
        # so we have to call onResize first for no-4:3 images
        self.onResize(None)
        self.Refresh()

    def getImagePath(self):
        return self.__img_path

    def reset(self):
        self.__img_path = None
        (w, h) = self.__cur_size
        new_img = wx.EmptyImage(w, h)
        new_img.Replace(*(wx.BLACK.Get() + wx.WHITE.Get())) # convert to white
        self.__img_raw = new_img
        self.Refresh()

    def onResize(self, event):
        orig = self.__cur_size
        (W_MAX, H_MAX) = self.GetSizeTuple()
        (W, H) = self.__img_raw.GetSize().Get()
        if W > H:
            NewW = W_MAX
            NewH = int(1.0 * H_MAX * H / W)
        else:
            NewW = int(1.0 * W_MAX * W / H)
            NewH = H_MAX
        self.__cur_size = (NewW, NewH)

    def onPaint(self, event):
        dc = wx.PaintDC(self)
        (w, h) = self.__cur_size
        if h == 0:
            return
        raw = self.__img_raw
        (raw_w, raw_h) = raw.GetSize().Get()
        if float(w) / h != float(raw_w) / raw_h:
            # In this case, __img_raw is not 4:3
            self.onResize(None)
        bitmap = wx.BitmapFromImage(raw.Scale(w, h))
        dc.DrawBitmap(bitmap, 0, 0, useMask=False)


class LayoutSelectionDialog(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, title="Layout Setting", size=(-1, -1))
        # sizer
        root_layout = wx.BoxSizer(wx.HORIZONTAL)
        right_layout = wx.BoxSizer(wx.VERTICAL)
        ans_layout = wx.GridSizer(2, 3)
        btn_layout = wx.GridSizer(2, 1)
        # panel
        root_panel = wx.Panel(self, wx.ID_ANY)
        right_panel = wx.Panel(root_panel, wx.ID_ANY)
        ans_panel = wx.Panel(right_panel, wx.ID_ANY)
        btn_panel = wx.Panel(right_panel, wx.ID_ANY)
        # grid
        self.myGrid = wx.grid.Grid(root_panel)
        h_num = 4
        w_num = 4
        self.myGrid.CreateGrid(h_num, w_num)
        self.myGrid.SetRowLabelSize(0)
        self.myGrid.SetColLabelSize(0)
        for i in range(4):
            for j in range(4):
                self.myGrid.SetRowSize(i, 30)
                self.myGrid.SetColSize(j, 30)
                self.myGrid.SetReadOnly(i, j)
        self.myGrid.Bind(wx.grid.EVT_GRID_RANGE_SELECT, self.onDragSelection)
        # button
        btn_tips = ["OK", "Cancel"]
        btn_arts = [wx.ART_TICK_MARK, wx.ART_CROSS_MARK]
        btn_funcs = [self.onOk, self.onCancel]
        for tip, art, func in zip(btn_tips, btn_arts, btn_funcs):
            bitmap = wx.ArtProvider.GetBitmap(art, size=(20, 20))
            btn = wx.BitmapButton(btn_panel, wx.ID_ANY, bitmap, size=(80, 40))
            btn.SetToolTip(wx.ToolTip(tip))
            btn.Bind(wx.EVT_BUTTON, func)
            btn_layout.Add(btn, flag=wx.GROW | wx.ALIGN_CENTER | wx.TOP, border=20)
        btn_panel.SetSizer(btn_layout)
        # answer
        g00 = wx.StaticText(ans_panel, wx.ID_ANY, "H")
        g01 = wx.StaticText(ans_panel, wx.ID_ANY, "")
        g02 = wx.StaticText(ans_panel, wx.ID_ANY, "W")
        self.g10 = wx.ComboBox(ans_panel, wx.ID_ANY, "", choices=[str(x+1) for x in range(h_num)], style=wx.CB_READONLY)
        g11 = wx.StaticText(ans_panel, wx.ID_ANY, "x")
        self.g12 = wx.ComboBox(ans_panel, wx.ID_ANY, "", choices=[str(x+1) for x in range(w_num)], style=wx.CB_READONLY)
        for g in [g00, g01, g02, self.g10, g11, self.g12]:
            ans_layout.Add(g, flag=wx.SHAPED | wx.ALIGN_CENTER, border=20)
        ans_panel.SetSizer(ans_layout)
        # right
        right_layout.Add(ans_panel, flag=wx.GROW | wx.ALIGN_CENTER | wx.ALL, border=20)
        right_layout.Add(btn_panel, flag=wx.GROW | wx.ALIGN_CENTER)
        right_panel.SetSizer(right_layout)
        # all
        root_layout.Add(self.myGrid, flag=wx.GROW | wx.ALL, border=20)
        root_layout.Add(right_panel)
        root_panel.SetSizer(root_layout)

    def onOk(self, event):
        self.EndModal(wx.ID_OK)

    def onCancel(self, event):
        self.EndModal(wx.ID_NO)

    def onDragSelection(self, event):
        if self.myGrid.GetSelectionBlockTopLeft():
            top_left = self.myGrid.GetSelectionBlockTopLeft()[0]
            bottom_right = self.myGrid.GetSelectionBlockBottomRight()[0]
            h_num = bottom_right[0] - top_left[0] + 1
            w_num = bottom_right[1] - top_left[1] + 1
            self.g10.SetValue(str(h_num))
            self.g12.SetValue(str(w_num))

if __name__=="__main__":
    app = wx.App()
    frm = MyFrame()
    frm.Show()
    app.MainLoop()
