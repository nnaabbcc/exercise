
from PyQt5.QtWidgets import QApplication, QDialog, QFormLayout, QLabel, \
    QLineEdit, QComboBox, QSpinBox, QDialogButtonBox, QVBoxLayout, QGroupBox

class MyDialog(QDialog):

    def __init__(self):
        super(QDialog, self).__init__()

        group_box = self._create_group_box()
        button_box = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        button_box.accepted.connect(self.accept)
        button_box.rejected.connect(self.reject)

        layout = QVBoxLayout()
        layout.addWidget(group_box)
        layout.addWidget(button_box)
        self.setLayout(layout)

        self.setWindowTitle('PyQt5 Form Layout example')

    @staticmethod
    def _create_group_box():
        box = QGroupBox('Form Layout')
        layout = QFormLayout()
        layout.addRow(QLabel('Name:'), QLineEdit())
        layout.addRow(QLabel('Country:'), QComboBox())
        layout.addRow(QLabel('Age'), QSpinBox())
        box.setLayout(layout)
        return box


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    dlg = MyDialog()
    sys.exit(dlg.exec_())
