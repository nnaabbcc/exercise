
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog, QPushButton


class MyWidget(QWidget):

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 File dialog example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self.__init_ui()

    def __init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        button_get_open_file_name = QPushButton('Get Open File Name', self)
        button_get_open_file_name.move(20, 20)
        button_get_open_file_name.clicked.connect(self.on_get_file_name_click)

        button_get_open_file_names = QPushButton('Get Multi Open File Names', self)
        button_get_open_file_names.move(20, 50)
        button_get_open_file_names.clicked.connect(self.on_get_file_names_click)

        button_get_save_file_name = QPushButton('Get Save File Name', self)
        button_get_save_file_name.move(20, 80)
        button_get_save_file_name.clicked.connect(self.on_get_save_file_name_click)

    def on_get_file_name_click(self):
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        filename, _ = QFileDialog.getOpenFileName(self,
                                                  'QFileDialog.getOpenFileName()',
                                                  '',
                                                  'All Files(*);;Python Files(*.py)',
                                                  options=options)
        if filename:
            print(filename)

    def on_get_file_names_click(self):
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        files, _ = QFileDialog.getOpenFileNames(self,
                                                'QFileDialog.getOpenFileNames()',
                                                '',
                                                'All Files(*);;Python Files(*.py)',
                                                options=options)
        if files:
            print(files)

    def on_get_save_file_name_click(self):
        options = QFileDialog.Options()
        options != QFileDialog.DontUseNativeDialog
        filename, _ = QFileDialog.getSaveFileName(self,
                                                  'QFileDialog.getSaveFileName()',
                                                  '',
                                                  'All Files(*);;Text Files(*.txt)',
                                                  options=options)
        if filename:
            print(filename)

if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec())