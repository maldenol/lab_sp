#include "Client.h"

QJsonObject Client::toJson() const
{
    QJsonObject json;

    json["ID"] = QString::fromStdString(std::to_string(mID));
    json["FirstName"] = QString::fromStdString(mFirstName);
    json["MiddleName"] = QString::fromStdString(mMiddleName);
    json["LastName"] = QString::fromStdString(mLastName);
    json["BirthDate"] = QString::fromStdString(mBirthDate);
    json["Sex"] = QString::fromStdString(mSex);
    json["ChildrenNumber"] = QString::fromStdString(std::to_string(mChildrenNumber));
    json["Address"] = QString::fromStdString(mAddress);
    json["PhoneNumber"] = QString::fromStdString(mPhoneNumber);
    json["Height"] = QString::fromStdString(std::to_string(mHeight));
    json["Weight"] = QString::fromStdString(std::to_string(mWeight));

    return json;
}

Client Client::fromJson(const QJsonObject &json)
{
    Client client;

    client.mID = json["ID"].toString().toUInt();
    client.mFirstName = json["FirstName"].toString().toStdString();
    client.mMiddleName = json["MiddleName"].toString().toStdString();
    client.mLastName = json["LastName"].toString().toStdString();
    client.mBirthDate = json["BirthDate"].toString().toStdString();
    client.mSex = json["Sex"].toString().toStdString();
    client.mChildrenNumber = json["ChildrenNumber"].toString().toUInt();
    client.mAddress = json["Address"].toString().toStdString();
    client.mPhoneNumber = json["PhoneNumber"].toString().toStdString();
    client.mHeight = json["Height"].toString().toFloat();
    client.mWeight = json["Weight"].toString().toFloat();

    return client;
}
