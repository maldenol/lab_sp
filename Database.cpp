#include "Database.h"

#include <stdexcept>

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

bool Database::save(const QString &path) const
{
    bool success = false;

    if(!path.isEmpty())
    {
        QFile file{path};

        if (file.open(QIODevice::WriteOnly))
        {
            QJsonDocument jsonDoc{toJson()};
            file.write(jsonDoc.toJson());

            success = true;
        }

        file.close();
    }

    return success;
}

bool Database::load(const QString &path)
{
    bool success = false;

    if(!path.isEmpty())
    {
        QFile file{path};

        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray saveData = file.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));
            *this = fromJson(jsonDoc.object());

            success = true;
        }

        file.close();
    }

    return success;
}

unsigned int Database::addClient(const Client &client) noexcept
{
    Client _client = client;

    _client.mID = mCurrentID;
    ++mCurrentID;

    mClients.push_back(_client);

    return mCurrentID - 1;
}

void Database::removeClient(unsigned int clientID)
{
    size_t clientIndex = findClient(clientID);
    mClients.erase(mClients.begin() + clientIndex);
}

Client &Database::getClient(unsigned int clientID)
{
    size_t clientIndex = findClient(clientID);
    return mClients[clientIndex];
}

const Client &Database::getClient(unsigned int clientID) const
{
    size_t clientIndex = findClient(clientID);
    return mClients[clientIndex];
}

const std::vector<Client> &Database::getClients() const noexcept
{
    return mClients;
}

size_t Database::findClient(unsigned int clientID) const
{
    size_t clientNumber = mClients.size();
    for (size_t i = 0; i < clientNumber; ++i) {
        if (mClients[i].mID == clientID) {
            return i;
        }
    }

    throw std::runtime_error{ "No such client" };
}

QJsonObject Database::toJson() const
{
    QJsonObject json;

    QJsonArray clients;
    for (const Client &client : mClients)
    {
        clients.append(client.toJson());
    }
    json["Clients"] = clients;

    json["CurrentID"] = QString::fromStdString(std::to_string(mCurrentID));

    return json;
}

Database Database::fromJson(const QJsonObject &json)
{
    Database database;

    for (const QJsonValue &client : json["Clients"].toArray())
    {
        database.mClients.push_back(Client::fromJson(client.toObject()));
    }

    database.mCurrentID = json["CurrentID"].toString().toUInt();

    return database;
}
