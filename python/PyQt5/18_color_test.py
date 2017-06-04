
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout
from PyQt5.QtGui import QColor, QPainter
from PyQt5.QtCore import Qt


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 Color example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.setAutoFillBackground(True)
        p = self.palette()
        p.setColor(self.backgroundRole(), Qt.white)
        self.setPalette(p)

        layout = QVBoxLayout()
        canvas = PaintWidget()
        layout.addWidget(canvas)
        self.setLayout(layout)


class PaintWidget(QWidget):

    def paintEvent(self, event):
        p = QPainter(self)
        p.setPen(Qt.black)
        size = self.size()

        p.setBrush(QColor(200, 0, 0))
        p.drawRect(0, 0, 100, 100)

        p.setBrush(QColor(0, 200, 0))
        p.drawRect(100, 0, 100, 100)

        p.setBrush(QColor(0, 0, 200))
        p.drawRect(200, 0, 100, 100)

        # Color effect
        for i in range(100):
            p.setBrush(QColor(i*10, 0, 0))
            p.drawRect(10*i, 100, 10, 32)

            p.setBrush(QColor(i*10, i*10, 0))
            p.drawRect(10*i, 100+32, 10, 32)

            p.setBrush(QColor(i*2, i*10, i))
            p.drawRect(10*i, 100+64, 10, 64)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())