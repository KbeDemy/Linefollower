import os
import sys
import ctypes  
from PyQt6.QtWidgets import QApplication
from main_window import MainWindow
from data_manager import DataManager

def main():

    myappid = u'@#@LineFollower@#@'  # unieke app id
    ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(myappid)

    app = QApplication(sys.argv)

    # --- DataManager aanmaken ---
    data_manager = DataManager(db_path="robot_data.db")

    # --- MainWindow opstarten ---
    window = MainWindow(data_manager=data_manager)
    window.show()

    hwnd = int(window.winId())

    color = 0xFF000000  # FF = alpha, 00 00 00 = RGB zwart
    DWMWA_CAPTION_COLOR = 35  # Windows 10 1809+ voor title bar kleur
    ctypes.windll.dwmapi.DwmSetWindowAttribute(
        hwnd, 
        DWMWA_CAPTION_COLOR, 
        ctypes.byref(ctypes.c_uint(color)), 
        ctypes.sizeof(ctypes.c_uint)
    )
    # --- Run eventloop ---
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
