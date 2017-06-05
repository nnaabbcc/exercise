
from PyQt5.QtWidgets import QApplication, QMainWindow, QSizePolicy, QPushButton

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.pyplot import Figure


class MyMainWindow(QMainWindow):

    def __init__(self):
        super(QMainWindow, self).__init__()
        self.title = 'PyQt5 matplotlib example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self._init_ui()

    def _init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        m = PlotCanvas(self, width=5, height=4)
        m.move(0, 0)

        button = QPushButton('PyQt5 button', self)
        button.move(500, 0)
        button.resize(140, 100)


class PlotCanvas(FigureCanvas):

    def __init__(self, parent=None, width=5.0, height=4.0, dpi=100):
        fig = Figure((width, height), dpi=dpi)
        self.axes = fig.add_subplot(1, 1, 1)
        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        self.setSizePolicy(QSizePolicy.Expanding,
                           QSizePolicy.Expanding)
        self.updateGeometry()
        self.plot()

    def plot(self):
        import random
        data = [random.random() for i in range(100)]
        self.axes.plot(data, 'r-')
        self.axes.set_title('PyQt5 matplotlib example')
        self.draw()


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyMainWindow()
    w.show()
    sys.exit(app.exec_())
