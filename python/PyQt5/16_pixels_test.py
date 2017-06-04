
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout
from PyQt5.QtGui import QPainter
from PyQt5.QtCore import Qt


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 pixels example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        layout = QVBoxLayout()
        canvas = MyPaintWidget(self)
        layout.addWidget(canvas)

        self.setLayout(layout)


class MyPaintWidget(QWidget):

    def paintEvent(self, event):
        import random
        p = QPainter(self)
        p.setPen(Qt.black)
        size = self.size()

        for i in range(1024):
            x = random.randint(1, size.width() - 1)
            y = random.randint(1, size.height() - 1)
            p.drawPoint(x, y)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
