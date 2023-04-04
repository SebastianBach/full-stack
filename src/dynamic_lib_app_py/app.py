import ctypes
import os
import platform
import sys

from PyQt5.QtWidgets import (QApplication, QLabel, QLineEdit, QPushButton,
                             QVBoxLayout, QWidget)

dynamic_lib = {}
dynamic_lib["Windows"] = "text_conversion.dll"
dynamic_lib["Linux"] = "text_conversion.so"

dll_path = os.path.join(os.path.dirname(__file__), dynamic_lib[platform.system()])
text_conversion = ctypes.CDLL(dll_path)

title_case = text_conversion.title_case
title_case.argtypes = [ctypes.c_char_p]
title_case.restype = None

version = text_conversion.version
version.restype = ctypes.c_char_p

class MyApp(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle(
            f"Title Case App ({version().decode('utf-8')})")

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

        data = ctypes.create_string_buffer(len(text.encode('utf-8')) + 1)
        data.value = text.encode('utf-8')
        title_case(data)

        res = data.value.decode('utf-8')
        self.result_field.setText(res)

    def clear(self):
        """Clears all line edit fields."""
        self.input_field.setText("")
        self.result_field.setText("")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.setMinimumWidth(500)
    window.show()
    sys.exit(app.exec_())
