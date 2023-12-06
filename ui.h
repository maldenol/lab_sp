#ifndef UI_H
#define UI_H

#include "mainwindow.h"

int getInputInt(MainWindow &mainWindow);
float getInputFloat(MainWindow &mainWindow);
std::string getInputString(MainWindow &mainWindow);
void outputText(MainWindow &mainWindow, const std::string &text);
void processCommand(unsigned int command, MainWindow &mainWindow);
void showHelp(MainWindow &mainWindow);
void addClient(MainWindow &mainWindow);
void removeClient(MainWindow &mainWindow);
void editClient(MainWindow &mainWindow);
void showClient(MainWindow &mainWindow);
void showClients(MainWindow &mainWindow);

#endif // UI_H
