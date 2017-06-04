
from PyQt5.QtWidgets import (QApplication, QWidget, QGridLayout, QVBoxLayout,
                             QInputDialog, QPushButton, QGroupBox, QLineEdit)


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 input dialog example'
        self.left = 100
        self.top = 100
        self.width = 300
        self.height = 200
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        box = self.__create_group_box()

        main_layout = QVBoxLayout()
        main_layout.addWidget(box)
        self.setLayout(main_layout)

    def __create_group_box(self):
        box = QGroupBox('Input Dialog examples')
        layout = QGridLayout()

        button_get_integer = QPushButton('Get Integer')
        button_get_integer.clicked.connect(self.on_get_integer_click)
        layout.addWidget(button_get_integer, 0, 0)

        button_get_text = QPushButton('Get Text')
        button_get_text.clicked.connect(self.on_get_text_click)
        layout.addWidget(button_get_text, 0, 1)

        button_get_double = QPushButton('Get Double')
        button_get_double.clicked.connect(self.on_get_double_click)
        layout.addWidget(button_get_double, 1, 0)

        button_get_choice = QPushButton('Get Choice')
        button_get_choice.clicked.connect(self.on_get_choice_click)
        layout.addWidget(button_get_choice, 1, 1)

        box.setLayout(layout)
        return box

    def on_get_integer_click(self):
        i, ok_pressed = QInputDialog.getInt(self, 'Get Integer', 'Percentage:', 28, 0, 100, 1)
        if ok_pressed:
            print(i)

    def on_get_text_click(self):
        text, ok_pressed = QInputDialog.getText(self, 'Get Text', 'Your name:', QLineEdit.Normal, '')
        if ok_pressed and text != '':
            print(text)

    def on_get_double_click(self):
        d, ok_pressed = QInputDialog.getDouble(self, 'Get Double', 'Double:', 10.5, 0, 100, 10)
        if ok_pressed:
            print(d)

    def on_get_choice_click(self):
        items = ('Red', 'Blue', 'Green')
        item, ok_pressed = QInputDialog.getItem(self, 'Get Choice', 'Color:', items, 0, False)
        if ok_pressed and item:
            print(item)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
