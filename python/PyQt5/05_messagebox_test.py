
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMessageBox


class MyWidget(QWidget):

    def __init__(self):
        super(MyWidget, self).__init__()

        self.title = 'PyQt5 Messagebox example - pythonspot.com'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        button1 = QPushButton('Yes/No', self)
        button1.move(100, 100)
        button1.clicked.connect(self.click_slot_1)

        button2 = QPushButton('Yes/No/Cancel', self)
        button2.move(200, 100)
        button2.clicked.connect(self.click_slot_2)

        button3 = QPushButton('All', self)
        button3.move(400, 100)
        button3.clicked.connect(self.click_slot_3)

    def click_slot_1(self):
        buttonReply = QMessageBox.question(self, 'PyQt5 message', 'Do you like PyQt5?', QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if buttonReply == QMessageBox.Yes:
            print('Yes button clicked')
        else:
            print('No button clicked')

    def click_slot_2(self):
        buttonReply = QMessageBox.warning(self, 'PyQt5 message', 'Do you want to save?', QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel, QMessageBox.Cancel)
        if buttonReply == QMessageBox.Yes:
            print('Yes button clicked')
        elif buttonReply == QMessageBox.No:
            print('No button clicked')
        else:
            print('Cancel button clicked')

    def click_slot_3(self):
        button_reply = QMessageBox.information(self, 'PyQt5 message', 'Button demo!', QMessageBox.Cancel | QMessageBox.Ok | QMessageBox.Help | QMessageBox.Open | QMessageBox.Save | QMessageBox.SaveAll | QMessageBox.Discard | QMessageBox.Close | QMessageBox.Apply | QMessageBox.Reset | QMessageBox.Yes | QMessageBox.YesToAll | QMessageBox.No | QMessageBox.NoToAll | QMessageBox.NoButton | QMessageBox.RestoreDefaults | QMessageBox.Abort | QMessageBox.Retry | QMessageBox.Ignore, QMessageBox.Cancel)
        if button_reply == QMessageBox.Cancel:
            print('Cancel clicked')
        elif button_reply == QMessageBox.Ok:
            print('Ok clicked')
        elif button_reply == QMessageBox.Help:
            print('Help clicked')
        elif button_reply == QMessageBox.Open:
            print('Open clicked')
        elif button_reply == QMessageBox.Save:
            print('Save clicked')
        elif button_reply == QMessageBox.SaveAll:
            print('SaveAll clicked')
        elif button_reply == QMessageBox.Discard:
            print('Discard clicked')
        elif button_reply == QMessageBox.Close:
            print('Close clicked')
        elif button_reply == QMessageBox.Apply:
            print('Apply clicked')
        elif button_reply == QMessageBox.Reset:
            print('Reset clicked')
        elif button_reply == QMessageBox.Yes:
            print('Yes clicked')
        elif button_reply == QMessageBox.YesToAll:
            print('YesToAll clicked')
        elif button_reply == QMessageBox.No:
            print('No clicked')
        elif button_reply == QMessageBox.NoToAll:
            print('NoToAll clicked')
        elif button_reply == QMessageBox.NoButton:
            print('NoButton clicked')
        elif button_reply == QMessageBox.RestoreDefaults:
            print('RestoreDefaults clicked')
        elif button_reply == QMessageBox.Abort:
            print('Abort clicked')
        elif button_reply == QMessageBox.Retry:
            print('Retry clicked')
        elif button_reply == QMessageBox.Ignore:
            print('Ignore clicked')
        else:
            print('Unknown button clicked')


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)

    w = MyWidget()
    w.show()

    sys.exit(app.exec_())
