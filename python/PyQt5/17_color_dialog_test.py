
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QColorDialog


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 Color dialog example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        button = QPushButton('Open Color Dialog', self)
        button.move(10, 10)
        button.clicked.connect(self.on_click)

    def on_click(self):
        color = QColorDialog.getColor()
        if color.isValid():
            print(color.name())


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
