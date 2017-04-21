# SenseHat_TicTacToe

RPi_TicTacToe ist ein einfaches Programm mit dem man Tic Tac Toe auf dem RaspberryPi spielen kann. 
Zur Darstellung des Spielfelds, etc. wird das Add-on Board "SenseHat" verwendet. 
Zum Starten des Programms müssen als Kommandozeilenparameter der Framebuffer (/dev/fb1 in meinem Fall) und das 
Input-Device(/dev/input/event0 in meinem Fall) übergeben werden: RPi_TicTacToe &lt;FB_Path> &lt;EV_PATH>
