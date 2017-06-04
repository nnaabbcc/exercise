
from PyQt5.QtWidgets import QApplication, QDialog, QGridLayout, QPushButton, QGroupBox, QVBoxLayout


class MyDialog(QDialog):

    def __init__(self):
        super(QDialog, self).__init__()
        self.title = 'PyQt5 Grid layout example'
        self.left = 100
        self.top = 100
        self.width = 300
        self.height = 240
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        box = self.__create_group_box()

        main_layout = QVBoxLayout()
        main_layout.addWidget(box)
        self.setLayout(main_layout)

    def __create_group_box(self):
        box = QGroupBox('Grid')
        layout = QGridLayout()
        layout.setColumnStretch(1, 4)
        layout.setColumnStretch(2, 4)

        layout.addWidget(QPushButton('1'), 0, 0)
        layout.addWidget(QPushButton('2'), 0, 1)
        layout.addWidget(QPushButton('3'), 0, 2)
        layout.addWidget(QPushButton('4'), 1, 0)
        layout.addWidget(QPushButton('5'), 1, 1)
        layout.addWidget(QPushButton('6'), 1, 2)
        layout.addWidget(QPushButton('7'), 2, 0)
        layout.addWidget(QPushButton('8'), 2, 1)
        layout.addWidget(QPushButton('9'), 2, 2)

        box.setLayout(layout)
        return box


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyDialog()
    w.show()
    sys.exit(app.exec_())