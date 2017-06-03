
from PyQt5.QtWidgets import QApplication, QMainWindow


class MyMainWindow(QMainWindow):

    def __init__(self):
        super(QMainWindow, self).__init__()
        self.title = 'PyQt5 status bar example - pythonspot.com'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.statusBar().showMessage('Message in statusbar.')


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)

    w = MyMainWindow()
    w.show()

    sys.exit(app.exec_())
