#
# Implement CodeEditor with PyQt5,
# see reference on http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
#

from PyQt5.QtWidgets import QPlainTextEdit, QWidget, QTextEdit
from PyQt5.QtGui import QPainter, QColor, QTextFormat
from PyQt5.QtCore import Qt, QSize


class CodeEditor(QPlainTextEdit):

    def __init__(self, parent=None, line_number_area_space=10,
                 highlight_background_color=QColor(Qt.yellow).lighter(160)):
        super(QPlainTextEdit, self).__init__(parent)
        self.__line_number_area = LineNumberArea(self)
        self.__line_number_area_space = line_number_area_space
        self.__highlight_background_color = highlight_background_color

        self.blockCountChanged.connect(self.__update_line_number_area_width)
        self.updateRequest.connect(self.__update_line_number_area)
        self.cursorPositionChanged.connect(self.__highlight_current_line)

        self.__update_line_number_area_width()
        self.__highlight_current_line()

    def load_file(self, file):
        text = open(file).read()
        self.setPlainText(text)

    def line_number_area_width(self):
        digits = 1
        max_line_number = max(digits, self.blockCount())
        while max_line_number >= 10:
            max_line_number /= 10
            digits += 1
        spaces = self.__line_number_area_space + self.fontMetrics().width('9') * digits
        return spaces

    def line_number_area_paint_event(self, event):
        painter = QPainter(self.__line_number_area)
        painter.fillRect(event.rect(), Qt.lightGray)

        block = self.firstVisibleBlock()
        block_number = block.blockNumber()
        top = self.blockBoundingGeometry(block).translated(self.contentOffset()).top()
        bottom = top + self.blockBoundingRect(block).height()

        while block.isValid() and top <= event.rect().bottom():
            if block.isVisible() and bottom >= event.rect().top():
                painter.setPen(Qt.black)
                painter.drawText(0, top,
                                 # 1/3 margin on the right
                                 self.__line_number_area.width() - self.__line_number_area_space/3,
                                 self.fontMetrics().height(),
                                 Qt.AlignRight, str(block_number + 1))

            block = block.next()
            top = bottom
            bottom = top + self.blockBoundingRect(block).height()
            block_number += 1

    def __update_line_number_area_width(self):
        self.setViewportMargins(self.line_number_area_width(), 0, 0, 0)

    def resizeEvent(self, event):
        super(QPlainTextEdit, self).resizeEvent(event)
        cr = self.contentsRect()
        self.__line_number_area.setGeometry(cr.left(), cr.top(),
                                            self.line_number_area_width(), cr.height())

    def __update_line_number_area(self, rect, dy):
        if dy:
            self.__line_number_area.scroll(0, dy)
        else:
            self.update(0, rect.y(), self.__line_number_area.width(), rect.height())
        if rect.contains(self.viewport().rect()):
            self.__update_line_number_area_width()

    def __highlight_current_line(self):
        selection = QTextEdit.ExtraSelection()
        selection.format.setBackground(self.__highlight_background_color)
        selection.format.setProperty(QTextFormat.FullWidthSelection, True)
        selection.cursor = self.textCursor()
        selection.cursor.clearSelection()
        self.setExtraSelections([selection])


class LineNumberArea(QWidget):

    def __init__(self, editor):
        super(QWidget, self).__init__(editor)
        self.__code_editor = editor

    def sizeHint(self):
        return QSize(self.__code_editor.line_number_area_width(), 0)

    def paintEvent(self, event):
        self.__code_editor.line_number_area_paint_event(event)


if __name__ == '__main__':
    import sys
    from PyQt5.QtWidgets import QApplication

    app = QApplication(sys.argv)

    w = CodeEditor()
    w.setReadOnly(True)
    w.setWindowTitle('Code Editor example')
    w.setPlainText('line1\nline2\nline3')
    w.resize(800, 600)
    w.show()

    sys.exit(app.exec_())
