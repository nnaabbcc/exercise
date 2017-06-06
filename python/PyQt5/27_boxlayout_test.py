
from PyQt5.QtWidgets import QApplication, QDialog, QVBoxLayout, QPushButton


class MyDialog(QDialog):

    def __init__(self):
        super(QDialog, self).__init__()
        self.setWindowTitle('PyQt5 Box Layout example')

        b1 = QPushButton('Button 1')
        b2 = QPushButton('Button 2')
        b3 = QPushButton('Button 3')
        b4 = QPushButton('Button 4')

        layout = QVBoxLayout()
        layout.addWidget(b1)
        layout.addWidget(b2)
        layout.addWidget(b3)
        layout.addWidget(b4)

        self.setLayout(layout)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    dlg = MyDialog()
    sys.exit(dlg.exec_())
