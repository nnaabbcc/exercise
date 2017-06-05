
from PyQt5.QtWidgets import QApplication, QWidget, QLineEdit, QLabel


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 drag and drop example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        edit_box = QLineEdit('Drag this', self)
        edit_box.setDragEnabled(True)
        edit_box.move(10, 10)
        edit_box.resize(200, 32)

        label = CustomLabel('Drop here.', self)
        label.move(10, 50)
        label.resize(200, 32)


class CustomLabel(QLabel):

    def __init__(self, title, parent):
        super(QLabel, self).__init__(title, parent)
        self.setAcceptDrops(True)

    def dragEnterEvent(self, e):
        if e.mimeData().hasFormat('text/plain'):
            e.accept()
        else:
            e.ignore()

    def dropEvent(self, e):
        self.setText(e.mimeData().text())


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
