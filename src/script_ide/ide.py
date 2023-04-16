import subprocess
import sys
import os
from PyQt5.QtWidgets import QApplication, QWidget, QTextEdit, QPushButton, QVBoxLayout

class MyApp(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        # Create widgets
        self.text_edit1 = QTextEdit(self)
        self.text_edit1.setFontFamily("Courier New")
        self.text_edit2 = QTextEdit(self)
        self.text_edit2.setFontFamily("Courier New")
        self.btn_execute = QPushButton('Execute', self)

        # Create layout
        vbox = QVBoxLayout()
        vbox.addWidget(self.text_edit1)
        vbox.addWidget(self.btn_execute)
        vbox.addWidget(self.text_edit2)
        self.setLayout(vbox)

        # Connect signals to slots
        self.btn_execute.clicked.connect(self.on_execute)

        # Set window properties
        self.setGeometry(300, 300, 300, 250)
        self.setWindowTitle('Text Conversion Script IDE')
        self.show()

    def on_execute(self):
        # Get content of first text field
        content = self.text_edit1.toPlainText()

        # Generate unique file name
        filename = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'output.txt')
        counter = 1
        while os.path.exists(filename):
            filename = os.path.join(os.path.dirname(os.path.realpath(__file__)), f'output_{counter}.txt')
            counter += 1

        # Write content to file
        with open(filename, 'w') as f:
            f.write(content)

        # Clear the content of the second text field
        self.text_edit2.clear()

        # Call subprocess with file path as argument
        cmd = [r'interpreter.exe', filename]
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        # Get stdout and stderr output
        stdout, stderr = proc.communicate()

        # Display stdout output in second text field
        self.text_edit2.setText(stdout.decode())

        # Delete the file that was created
        os.remove(filename)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
