#include "ui.h"

#include <sstream>

#include <qcoreapplication.h>

int getInputInt(MainWindow &mainWindow)
{
    QLineEdit * inputField = mainWindow.getInputField();
    int input = inputField->text().toInt();
    inputField->clear();
    return input;
}

float getInputFloat(MainWindow &mainWindow)
{
    QLineEdit * inputField = mainWindow.getInputField();
    float input = inputField->text().toFloat();
    inputField->clear();
    return input;
}

std::string getInputString(MainWindow &mainWindow)
{
    QLineEdit * inputField = mainWindow.getInputField();
    std::string input = inputField->text().toStdString();
    inputField->clear();
    return input;
}

void outputText(MainWindow &mainWindow, const std::string &text)
{
    QTextEdit * output = mainWindow.getOutputField();
    output->clear();
    output->setText(QString::fromStdString(text));
}

void processCommand(unsigned int command, MainWindow &mainWindow)
{
    switch (command) {
    case 0:
        QCoreApplication::exit();
        break;
    case 1:
        showHelp(mainWindow);
        break;
    case 2:
        addClient(mainWindow);
        break;
    case 3:
        removeClient(mainWindow);
        break;
    case 4:
        editClient(mainWindow);
        break;
    case 5:
        showClient(mainWindow);
        break;
    case 6:
        showClients(mainWindow);
        break;
    default:
        mainWindow.getOutputField()->setText("Unknown command\n");
        break;
    }
}

void showHelp(MainWindow &mainWindow)
{
    std::ostringstream stream;

    stream << "Choose one of the options:\n";
    stream << "0  Quit\n";
    stream << "1  Get help\n";
    stream << "2  Add a new client\n";
    stream << "3  Remove an existing client\n";
    stream << "4  Edit an existing client info\n";
    stream << "5  Show an existing client info\n";
    stream << "6  List all clients\n";

    outputText(mainWindow, stream.str());
}

void addClient(MainWindow &mainWindow)
{
    Client client;

    outputText(mainWindow, "Enter first name: ");
    mainWindow.waitForInput();
    client.mFirstName = getInputString(mainWindow);

    outputText(mainWindow, "Enter middle name: ");
    mainWindow.waitForInput();
    client.mMiddleName = getInputString(mainWindow);

    outputText(mainWindow, "Enter last name: ");
    mainWindow.waitForInput();
    client.mLastName = getInputString(mainWindow);

    outputText(mainWindow, "Enter date of birth: ");
    mainWindow.waitForInput();
    client.mBirthDate = getInputString(mainWindow);

    outputText(mainWindow, "Enter sex: ");
    mainWindow.waitForInput();
    client.mSex = getInputString(mainWindow);

    outputText(mainWindow, "Enter number of children: ");
    mainWindow.waitForInput();
    client.mChildrenNumber = getInputInt(mainWindow);

    outputText(mainWindow, "Enter address: ");
    mainWindow.waitForInput();
    client.mAddress = getInputString(mainWindow);

    outputText(mainWindow, "Enter phone number: ");
    mainWindow.waitForInput();
    client.mPhoneNumber = getInputString(mainWindow);

    outputText(mainWindow, "Enter height: ");
    mainWindow.waitForInput();
    client.mHeight = getInputFloat(mainWindow);

    outputText(mainWindow, "Enter weight: ");
    mainWindow.waitForInput();
    client.mWeight = getInputFloat(mainWindow);

    mainWindow.getDatabase().addClient(client);

    outputText(mainWindow, "Succesfully added\n");
}

void removeClient(MainWindow &mainWindow)
{
    outputText(mainWindow, "Enter client ID: ");
    mainWindow.waitForInput();
    unsigned int clientID = getInputInt(mainWindow);

    try {
        mainWindow.getDatabase().removeClient(clientID);
        outputText(mainWindow, "Successfully removed\n");
    } catch (const std::runtime_error &ex) {
        outputText(mainWindow, ex.what());
    } catch (...) {
        outputText(mainWindow, "An error has occured\n");
    }
}

void editClient(MainWindow &mainWindow)
{
    outputText(mainWindow, "Enter client ID: ");
    mainWindow.waitForInput();
    unsigned int clientID = getInputInt(mainWindow);

    try {
        Client &client = mainWindow.getDatabase().getClient(clientID);

        outputText(mainWindow, "Enter first name: ");
        mainWindow.waitForInput();
        client.mFirstName = getInputString(mainWindow);

        outputText(mainWindow, "Enter middle name: ");
        mainWindow.waitForInput();
        client.mMiddleName = getInputString(mainWindow);

        outputText(mainWindow, "Enter last name: ");
        mainWindow.waitForInput();
        client.mLastName = getInputString(mainWindow);

        outputText(mainWindow, "Enter date of birth: ");
        mainWindow.waitForInput();
        client.mBirthDate = getInputString(mainWindow);

        outputText(mainWindow, "Enter sex: ");
        mainWindow.waitForInput();
        client.mSex = getInputString(mainWindow);

        outputText(mainWindow, "Enter number of children: ");
        mainWindow.waitForInput();
        client.mChildrenNumber = getInputInt(mainWindow);

        outputText(mainWindow, "Enter address: ");
        mainWindow.waitForInput();
        client.mAddress = getInputString(mainWindow);

        outputText(mainWindow, "Enter phone number: ");
        mainWindow.waitForInput();
        client.mPhoneNumber = getInputString(mainWindow);

        outputText(mainWindow, "Enter height: ");
        mainWindow.waitForInput();
        client.mHeight = getInputFloat(mainWindow);

        outputText(mainWindow, "Enter weight: ");
        mainWindow.waitForInput();
        client.mWeight = getInputFloat(mainWindow);

        outputText(mainWindow, "Succesfully updated\n");
    } catch (const std::runtime_error &ex) {
        outputText(mainWindow, ex.what());
    } catch (...) {
        outputText(mainWindow, "An error has occured\n");
    }
}

void showClient(MainWindow &mainWindow)
{
    outputText(mainWindow, "Enter client ID: ");
    mainWindow.waitForInput();
    unsigned int clientID = getInputInt(mainWindow);

    try {
        const Client &client = mainWindow.getDatabase().getClient(clientID);

        std::ostringstream stream;

        stream << "First name: " << client.mFirstName << "\n";
        stream << "Middle name: " << client.mMiddleName << "\n";
        stream << "Last name: " << client.mLastName << "\n";
        stream << "Date of birth: " << client.mBirthDate << "\n";
        stream << "Sex: " << client.mSex << "\n";
        stream << "Number of children: " << client.mChildrenNumber
               << "\n";
        stream << "Address: " << client.mAddress << "\n";
        stream << "Phone number: " << client.mPhoneNumber << "\n";
        stream << "Height: " << client.mHeight << "\n";
        stream << "Weight: " << client.mWeight << "\n";

        outputText(mainWindow, stream.str());
    } catch (const std::runtime_error &ex) {
        outputText(mainWindow, ex.what());
    } catch (...) {
        outputText(mainWindow, "An error has occured\n");
    }
}

void showClients(MainWindow &mainWindow)
{
    const std::vector<Client> &clients = mainWindow.getDatabase().getClients();

    if (clients.empty())
    {
        outputText(mainWindow, "No clients.\n");
        return;
    }

    std::ostringstream stream;

    stream << "Clients:\n";
    for (const Client &client : clients) {
        stream << client.mID << " ";
        stream << client.mFirstName << " ";
        stream << client.mMiddleName << " ";
        stream << client.mLastName << "\n";
    }

    outputText(mainWindow, stream.str());
}
