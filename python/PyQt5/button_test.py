
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtCore import pyqtSlot


class MyWidget(QWidget):

    def __init__(self):
        super(MyWidget, self).__init__()

        self.title = 'PyQt5 button example -- pythonspot.com'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480

        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        
        button = QPushButton('PyQt5 button', self)
        button.setToolTip('This is an example button')
        button.move(100, 100)
        button.clicked.connect(self.on_click)

    @pyqtSlot()
    def on_click(self):
        print('PyQt5 button clicked')


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()

    sys.exit(app.exec_())

