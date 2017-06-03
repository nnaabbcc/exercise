
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QLineEdit, QPushButton


class MyMainWindow(QMainWindow):

    def __init__(self):
        super(QMainWindow, self).__init__()

        self.title = 'PyQt5 textbox example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480

        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.textbox = QLineEdit(self)
        self.textbox.move(20, 20)
        self.textbox.resize(280, 30)

        button = QPushButton('Show Text', self)
        button.move(20, 80)
        button.clicked.connect(self.on_button_click)

    def on_button_click(self):
        text = self.textbox.text()
        if text:
            QMessageBox.information(self, 'Message - textbox example', 'You typed: ' + text, QMessageBox.Ok, QMessageBox.Ok)
        else:
            QMessageBox.warning(self, 'Message - textbox example', 'You have not typed anything!', QMessageBox.Ok, QMessageBox.Ok)
        self.textbox.setText('')


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyMainWindow()
    w.show()

    sys.exit(app.exec_())