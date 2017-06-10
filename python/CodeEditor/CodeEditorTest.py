
if __name__ == '__main__':
    from CodeEditor import CodeEditor
    import sys
    from PyQt5.QtWidgets import QApplication
    from PyQt5.QtGui import QColor
    from PyQt5.QtCore import Qt

    app = QApplication(sys.argv)
    # editor = CodeEditor()
    # editor = CodeEditor(line_number_area_space=30)
    # editor = CodeEditor(highlight_background_color=Qt.red)
    # editor = CodeEditor(line_number_area_space=25, highlight_background_color=Qt.green)
    editor = CodeEditor(line_number_area_space=20, highlight_background_color=QColor('#E2A69B'))
    editor.load_file('log.txt')
    editor.show()
    sys.exit(app.exec_())
