
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel

class MyMainWindow(QMainWindow):

    def __init__(self):
        super(QMainWindow, self).__init__()

        self.title = 'PyQt5 Absolute positioning example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480

        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        label1 = QLabel('python', self)
        label1.move(50, 50)

        label2 = QLabel('PyQt5', self)
        label2.move(100, 100)

        label3 = QLabel('Example', self)
        label3.move(150, 150)

        label4 = QLabel('pythonspot.com', self)
        label4.move(200, 200)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyMainWindow()
    w.show()
    sys.exit(app.exec_())
