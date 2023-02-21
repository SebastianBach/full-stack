import os
import platform
import subprocess
import sys

from PyQt5.QtWidgets import (QApplication, QLabel, QLineEdit, QMessageBox,
                             QPushButton, QVBoxLayout, QWidget)

executable = {}
executable["Windows"] = "title_case.exe"
executable["Linux"] = "title_case"

cmdl_path = executable[platform.system()]


class MyApp(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle(f"Title Case App")

        self.label_source = QLabel("Source:")
        self.input_field = QLineEdit()
        self.label_result = QLabel("Result:")
        self.result_field = QLineEdit()
        self.result_field.setReadOnly(True)

        self.button = QPushButton("Convert")
        self.button.clicked.connect(self.convert)

        self.button_clear = QPushButton("Clear")
        self.button_clear.clicked.connect(self.clear)

        layout = QVBoxLayout()
        layout.addWidget(self.label_source)
        layout.addWidget(self.input_field)
        layout.addWidget(self.label_result)
        layout.addWidget(self.result_field)
        layout.addWidget(self.button)
        layout.addWidget(self.button_clear)
        self.setLayout(layout)

    def convert(self):
        """ Converts the text of the input field to title case and
            writes the result to the result field.
        """
        text = self.input_field.text()
        res = subprocess.run([cmdl_path, text], capture_output=True, text=True)
        self.result_field.setText(res.stdout)

    def clear(self):
        """Clears all line edit fields."""
        self.input_field.setText("")
        self.result_field.setText("")


if __name__ == "__main__":

    app = QApplication(sys.argv)

    if not os.path.exists(cmdl_path):
        msg_box = QMessageBox()
        msg_box.setIcon(QMessageBox.Critical)
        msg_box.setText("Could not find command line tool.")
        msg_box.setWindowTitle("Error")
        msg_box.setStandardButtons(QMessageBox.Ok)
        msg_box.exec_()

        exit(-1)

    window = MyApp()
    window.setMinimumWidth(500)
    window.show()
    sys.exit(app.exec_())
