# Basic_keylogger
A program demostrating the basic principles regarding keyloggers
This program demonstrates the basic principles regarding a Hook based keylogger. Keyboard input is received and if the wParam received is a keypress, then the program will first check to see if the VK code is a [ENTER] press. If so, the press will be logged down with the addition of a newline statement. Else the program will simply log the keypress and repeat.  All VK codes are converted to Hex format, this is done for both readability and condensing of source code along with log file.
