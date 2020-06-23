# This Python file uses the following encoding: utf-8
import sys
from PySide2.QtWidgets import QApplication, QMainWindow


class hello(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)


if __name__ == "__main__":
    app = QApplication([])
    window = hello()
    window.show()
    # app.exec_()
    print("window x:", window.x())
    sys.exit(app.exec_())
