#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include <QJsonObject>

struct Client {
    unsigned int mID;
    std::string mFirstName;
    std::string mMiddleName;
    std::string mLastName;
    std::string mBirthDate;
    std::string mSex;
    unsigned int mChildrenNumber;
    std::string mAddress;
    std::string mPhoneNumber;
    float mHeight;
    float mWeight;

    QJsonObject toJson() const;
    static Client fromJson(const QJsonObject &json);
};

#endif // CLIENT_H
