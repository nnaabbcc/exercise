
from PyQt5.QtWidgets import QApplication, QMainWindow, QMdiArea, QMdiSubWindow, QAction
from PyQt5.QtCore import Qt


class MyMainWindow(QMainWindow):

    window_index = 1

    def __init__(self):
        super(QMainWindow, self).__init__()

        self.mdi_area = QMdiArea()
        self.setCentralWidget(self.mdi_area)

        self.__init_menu()

    def __init_menu(self):
        menu_bar = self.menuBar()

        file_menu = menu_bar.addMenu('File')

        open_action = QAction('Open', self)
        open_action.setShortcut('Ctrl+O')
        open_action.triggered.connect(self.__on_open)
        file_menu.addAction(open_action)

        exit_action = QAction('Exit', self)
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)

        window_menu = menu_bar.addMenu('Windows')

        close_current_action = QAction('Close Current Window', self)
        close_current_action.triggered.connect(self.mdi_area.closeActiveSubWindow)
        window_menu.addAction(close_current_action)

        close_all_action = QAction('Close All', self)
        close_all_action.triggered.connect(self.mdi_area.closeAllSubWindows)
        window_menu.addAction(close_all_action)

        cascade_action = QAction('Cascade Windows', self)
        cascade_action.triggered.connect(self.mdi_area.cascadeSubWindows)
        window_menu.addAction(cascade_action)

        tile_action = QAction('Title Windows', self)
        tile_action.triggered.connect(self.mdi_area.tileSubWindows)
        window_menu.addAction(tile_action)

        self.__window_list_menu = window_menu.addMenu('Window List')
        self.__window_list_menu.aboutToShow.connect(self.__window_list_menu_about_to_show)

    def __window_list_menu_about_to_show(self):
        self.__window_list_menu.clear()
        windows = self.mdi_area.subWindowList()
        index = 1
        for window in windows:
            action = QAction(str(index) + '. ' + window.windowTitle(), self.__window_list_menu)
            action.setProperty('WindowObject', window)
            action.triggered.connect(self.__on_select_window)
            self.__window_list_menu.addAction(action)
            index += 1

    def __on_select_window(self):
        action = self.sender()
        window = action.property('WindowObject')
        self.mdi_area.setActiveSubWindow(window)

    def __on_open(self):
        window = QMdiSubWindow()
        window.setAttribute(Qt.WA_DeleteOnClose, True)
        window.setWindowTitle('Sub Window ' + str(MyMainWindow.window_index))
        window.resize(300, 200)
        self.mdi_area.addSubWindow(window)
        window.show()

        MyMainWindow.window_index += 1


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    w = MyMainWindow()
    w.setWindowTitle('MdiArea example')
    w.show()
    sys.exit(app.exec_())

