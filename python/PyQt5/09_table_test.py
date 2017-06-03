
from PyQt5.QtWidgets import QApplication, QWidget, QTableWidget, QTableWidgetItem, QVBoxLayout


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 table example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.__create_table()

        layout = QVBoxLayout()
        layout.addWidget(self.table_widget)

        self.setLayout(layout)

    def __create_table(self):
        self.table_widget = QTableWidget()
        self.table_widget.setRowCount(4)
        self.table_widget.setColumnCount(2)

        self.table_widget.setItem(0, 0, QTableWidgetItem('Cell Item (0, 0)'))
        self.table_widget.setItem(0, 1, QTableWidgetItem('Cell Item (0, 1)'))
        self.table_widget.setItem(1, 0, QTableWidgetItem('Cell Item (1, 0)'))
        self.table_widget.setItem(1, 1, QTableWidgetItem('Cell Item (1, 1)'))
        self.table_widget.setItem(2, 0, QTableWidgetItem('Cell Item (2, 0)'))
        self.table_widget.setItem(2, 1, QTableWidgetItem('Cell Item (2, 1)'))
        self.table_widget.setItem(3, 0, QTableWidgetItem('Cell Item (3, 0)'))
        self.table_widget.setItem(3, 1, QTableWidgetItem('Cell Item (3, 1)'))

        self.table_widget.doubleClicked.connect(self.on_double_click)

    def on_double_click(self):
        print('\n')
        for item in self.table_widget.selectedItems():
            print(item.row(), item.column(), item.text())


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())

