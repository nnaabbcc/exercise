
from PyQt5.QtWidgets import QApplication, QDialog, QVBoxLayout, QHBoxLayout, QPushButton, QGroupBox
from PyQt5.QtCore import pyqtSlot


class MyDialog(QDialog):

    def __init__(self):
        super(QDialog, self).__init__()
        self.title = 'PyQt5 horizontal layout example'
        self.left = 100
        self.top = 100
        self.width = 480
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        box = self.__create_group_box()

        main_layout = QVBoxLayout()
        main_layout.addWidget(box)
        self.setLayout(main_layout)

    def __create_group_box(self):
        box = QGroupBox("What's your favorite colors?")
        layout = QHBoxLayout()

        button_blue = QPushButton('Blue')
        button_blue.clicked.connect(self.on_click)
        layout.addWidget(button_blue)

        button_red = QPushButton('Red')
        button_red.clicked.connect(self.on_click)
        layout.addWidget(button_red)

        button_green = QPushButton('Green')
        button_green.clicked.connect(self.on_click)
        layout.addWidget(button_green)

        box.setLayout(layout)

        return box

    @pyqtSlot()
    def on_click(self):
        text = self.sender().text()
        print(text + ' button clicked')


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyDialog()
    w.show()
    sys.exit(app.exec_())
