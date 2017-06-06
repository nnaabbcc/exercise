
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QUrl

import sys

if __name__ == '__main__':
    app = QApplication(sys.argv)
    view = QWebEngineView()
    view.load(QUrl('https://www.baidu.com'))
    view.show()
    sys.exit(app.exec_())
