
from PyQt5.QtWidgets import (QApplication, QVBoxLayout, QDialog,
                             QPushButton)


class MyDialog(QDialog):

    def click_slot(self):
        print('click slot called')

    def __init__(self):
        super(MyDialog, self).__init__()

        button = QPushButton('Click')
        button.clicked.connect(self.click_slot)

        main_layout = QVBoxLayout()
        main_layout.addWidget(button)

        self.setLayout(main_layout)
        self.setWindowTitle('PyQt5 signals & slots example -- pythonspot.com')


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    myDialog = MyDialog()
    sys.exit(myDialog.exec_())
