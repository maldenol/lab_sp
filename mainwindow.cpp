#include "mainwindow.h"

#include <QFileDialog>
#include <QPushButton>

#include "ui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Lab 3");
    setGeometry(100, 100, 620, 480);

    outputField = new QTextEdit(this);
    outputField->setGeometry(10, 40, 600, 400);
    outputField->setReadOnly(true);

    inputField = new QLineEdit(this);
    inputField->setGeometry(10, 450, 500, 20);
    connect(inputField, SIGNAL (returnPressed()), this, SLOT (execute()));
    connect(inputField, SIGNAL (returnPressed()), &inputWaitLoop, SLOT (quit()));

    QPushButton *executeButton = new QPushButton("Execute", this);
    executeButton->setGeometry(520, 450, 90, 20);
    connect(executeButton, SIGNAL (released()), this, SLOT (execute()));

    QPushButton *saveButton = new QPushButton("Save", this);
    saveButton->setGeometry(315, 10, 295, 20);
    connect(saveButton, SIGNAL (released()), this, SLOT (save()));

    QPushButton *loadButton = new QPushButton("Load", this);
    loadButton->setGeometry(10, 10, 295, 20);
    connect(loadButton, SIGNAL (released()), this, SLOT (load()));

    showHelp(*this);
}

MainWindow::~MainWindow() {}

QLineEdit *MainWindow::getInputField() const noexcept
{
    return inputField;
}

QTextEdit *MainWindow::getOutputField() const noexcept
{
    return outputField;
}

Database &MainWindow::getDatabase() noexcept
{
    return database;
}

const Database &MainWindow::getDatabase() const noexcept
{
    return database;
}

void MainWindow::waitForInput() noexcept
{
    inputWaitLoop.exec();
}

void MainWindow::execute()
{
    if (inputWaitLoop.isRunning())
    {
        return;
    }

    unsigned int command = getInputInt(*this);
    processCommand(command, *this);
}

void MainWindow::save()
{
    QString path = QFileDialog::getSaveFileName(this, "Save to Json File", "", "Json files (*.json);;All files (*.*)");
    if (database.save(path))
    {
        outputText(*this, "Successfully saved.\n");
    }
    else
    {
        outputText(*this, "Error while saving.\n");
    }
}

void MainWindow::load()
{
    QString path = QFileDialog::getOpenFileName(this, "Load from Json File", "", "Json files (*.json);;All files (*.*)");
    if (database.load(path))
    {
        outputText(*this, "Successfully loaded.\n");
    }
    else
    {
        outputText(*this, "Error while loading.\n");
    }
}
