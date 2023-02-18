import sys

import func
from PyQt5.QtWidgets import (QApplication, QLabel, QLineEdit, QPushButton,
                             QVBoxLayout, QWidget)


class MyApp(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle(f"Convert ({func.get_library_build_date()})")

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
        text = self.input_field.text()
        self.result_field.setText(func.convert(text))

    def clear(self):
        self.input_field.setText("")
        self.result_field.setText("")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.setMinimumWidth(500)
    window.show()
    sys.exit(app.exec_())
