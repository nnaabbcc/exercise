
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QFileSystemModel, QTreeView


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 Directory view example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self._init_ui()

    def _init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        model = QFileSystemModel(self)
        model.setRootPath('')
        view = QTreeView()
        view.setModel(model)

        view.setAnimated(False)
        view.setIndentation(20)
        view.setSortingEnabled(True)

        layout = QVBoxLayout()
        layout.addWidget(view)
        self.setLayout(layout)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
