
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QGroupBox, QTreeView
from PyQt5.QtGui import QStandardItemModel
from PyQt5.QtCore import Qt

class MyWidget(QWidget):
    # define some index
    FROM, SUBJECT, DATE = range(3)

    def __init__(self):
        super(QWidget, self).__init__()
        self.title = 'PyQt5 treeview example'
        self.left = 100
        self.top = 100
        self.width = 640
        self.height = 480
        self._init_ui()

    def _init_ui(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        group_box = QGroupBox('Inbox');
        data_view = QTreeView()
        data_view.setRootIsDecorated(False)
        data_view.setAlternatingRowColors(True)
        data_layout = QHBoxLayout()
        data_layout.addWidget(data_view)
        group_box.setLayout(data_layout)

        model = self._create_mail_model(self)
        data_view.setModel(model)
        self._add_mail(model, 'A@github.com', 'A subject', '01/01/2001')
        self._add_mail(model, 'B@gitlab.com', 'B subject', '02/02/2002')
        self._add_mail(model, 'C@bitbucket.com', 'C subject', '03/03/2003')

        main_layout = QHBoxLayout()
        main_layout.addWidget(group_box)
        self.setLayout(main_layout)

    def _create_mail_model(self, parent):
        model = QStandardItemModel(0, 3, parent)
        model.setHeaderData(self.FROM, Qt.Horizontal, 'From')
        model.setHeaderData(self.SUBJECT, Qt.Horizontal, 'Subject')
        model.setHeaderData(self.DATE, Qt.Horizontal, 'Date')
        return model

    def _add_mail(self, model, from_mail, subject, date):
        model.insertRow(0)
        model.setData(model.index(0, self.FROM), from_mail)
        model.setData(model.index(0, self.SUBJECT), subject)
        model.setData(model.index(0, self.DATE), subject)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyWidget()
    w.show()
    sys.exit(app.exec_())
