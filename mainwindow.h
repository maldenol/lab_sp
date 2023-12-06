#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEventLoop>
#include <QFile>
#include <QLineEdit>
#include <QMainWindow>
#include <QTextEdit>

#include "Database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLineEdit *getInputField() const noexcept;
    QTextEdit *getOutputField() const noexcept;
    Database &getDatabase() noexcept;
    const Database &getDatabase() const noexcept;

    void waitForInput() noexcept;

private slots:
    void execute();
    void save();
    void load();

private:
    QLineEdit *inputField;
    QEventLoop inputWaitLoop;

    QTextEdit *outputField;

    Database database;
};

#endif // MAINWINDOW_H
