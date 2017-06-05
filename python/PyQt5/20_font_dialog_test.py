
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QFontDialog


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 Font dialog example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        button = QPushButton('Open font dialog', self)
        button.move(10, 10)
        button.resize(200, 32)
        button.clicked.connect(self.on_click)

    def on_click(self):
        font, ok = QFontDialog.getFont()
        if ok:
            print(font.toString())


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
