
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QTabWidget, QPushButton, QVBoxLayout


class MyMainWindow(QMainWindow):

    def __init__(self):
        super(QMainWindow, self).__init__()
        self.title = 'PyQt5 tab example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480

        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.tab_widget = MyTabWidget(self)
        self.setCentralWidget(self.tab_widget)


class MyTabWidget(QWidget):

    def __init__(self, parent):
        super(QWidget, self).__init__(parent)

        tabs = QTabWidget()
        tab1 = QWidget()
        tab2 = QWidget()

        tabs.addTab(tab1, 'Tab 1')
        tabs.addTab(tab2, 'Tab 2')

        tab1_layout = QVBoxLayout()
        button = QPushButton('Button')
        tab1_layout.addWidget(button)
        tab1.setLayout(tab1_layout)

        main_layout = QVBoxLayout()
        main_layout.addWidget(tabs)
        self.setLayout(main_layout)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyMainWindow()
    w.show()
    sys.exit(app.exec_())
