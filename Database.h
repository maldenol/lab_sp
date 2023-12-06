#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include <QJsonObject>
#include <QString>

#include "Client.h"

class Database {
public:
    bool save(const QString &path) const;
    bool load(const QString &path);

    unsigned int addClient(const Client &client) noexcept;
    void removeClient(unsigned int clientID);
    Client &getClient(unsigned int clientID);
    const Client &getClient(unsigned int clientID) const;
    const std::vector<Client> &getClients() const noexcept;

private:
    size_t findClient(unsigned int clientID) const;

    QJsonObject toJson() const;
    static Database fromJson(const QJsonObject &json);

private:
    std::vector<Client> mClients = std::vector<Client>{};
    unsigned int mCurrentID = 0;
};

#endif // DATABASE_H
