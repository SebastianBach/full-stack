import subprocess
import sys
import os
import platform
from PyQt5.QtGui import QTextCharFormat, QFont
from PyQt5.QtWidgets import QApplication, QWidget, QTextEdit, QPushButton, QVBoxLayout
from PyQt5.QtCore import Qt, QRegularExpression
from PyQt5.QtGui import QSyntaxHighlighter


class MyHighlighter(QSyntaxHighlighter):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.highlight_rules = []

        # create a rule to highlight "text" at the beginning of the line
        text_format = QTextCharFormat()
        text_format.setFontWeight(QFont.Bold)
        text_format.setForeground(Qt.darkBlue)
        text_rule = HighlightRule(QRegularExpression(r'^text\b'), text_format)
        self.highlight_rules.append(text_rule)

        # create a rule to highlight "process"
        process_format = QTextCharFormat()
        process_format.setFontWeight(QFont.Bold)
        process_format.setForeground(Qt.darkGreen)
        process_rule = HighlightRule(
            QRegularExpression(r'\bprocess\b'), process_format)
        self.highlight_rules.append(process_rule)

        # create a rule to highlight "print"
        print_format = QTextCharFormat()
        print_format.setFontWeight(QFont.Bold)
        print_format.setForeground(Qt.red)
        print_rule = HighlightRule(
            QRegularExpression(r'\bprint\b'), print_format)
        self.highlight_rules.append(print_rule)

    def highlightBlock(self, text):
        for rule in self.highlight_rules:
            iterator = rule.pattern.globalMatch(text)
            while iterator.hasNext():
                match = iterator.next()
                self.setFormat(match.capturedStart(),
                               match.capturedLength(), rule.format)


class HighlightRule():
    def __init__(self, pattern, format):
        self.pattern = pattern
        self.format = format


executable = {}
executable["Windows"] = "interpreter.exe"
executable["Linux"] = "./interpreter"

cmdl_path = executable[platform.system()]


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
        self.text_edit2.setReadOnly(True)
        self.btn_execute = QPushButton('Execute', self)

        # Create layout
        vbox = QVBoxLayout()
        vbox.addWidget(self.text_edit1)
        vbox.addWidget(self.btn_execute)
        vbox.addWidget(self.text_edit2)
        self.setLayout(vbox)

        # Connect signals to slots
        self.btn_execute.clicked.connect(self.on_execute)

        self.highlighter = MyHighlighter(self.text_edit1.document())

        # Set window properties
        self.setGeometry(300, 300, 600, 500)
        self.setWindowTitle('Script IDE')
        self.show()

    def on_execute(self):
        # Get content of first text field
        content = self.text_edit1.toPlainText()

        # Generate unique file name
        filename = os.path.join(os.path.dirname(
            os.path.realpath(__file__)), 'output.txt')
        counter = 1
        while os.path.exists(filename):
            filename = os.path.join(os.path.dirname(
                os.path.realpath(__file__)), f'output_{counter}.txt')
            counter += 1

        # Write content to file
        with open(filename, 'w') as f:
            f.write(content)

        # Clear the content of the second text field
        self.text_edit2.clear()

        # Call subprocess with file path as argument
        cmd = [cmdl_path, filename]
        proc = subprocess.Popen(
            cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

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
