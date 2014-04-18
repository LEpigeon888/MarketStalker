#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QtGui>
#include <QtCore>

struct emailInformation
{
    bool isActive;
    QString emailTo;
    QString emailWith;
    QString mdpWith;
    QString smtpServ;
    int smtpPort;
};

struct item
{
    QString gameName;
    QString name;
    QString value;
    QString link;
};

struct options
{
    QString windowName;
    int itemPerPage;
    double valueOfEuro;
    bool isInEuro;
    bool isInEnglish;
    bool alwaysBeep;
    emailInformation emailInfo;
    double minValue;
    double maxValue;
    int timeRefresh;
    QString stringSearch;
    QList<item> listOfItemBlacklisted;
};

QDataStream& operator<<(QDataStream& thisStream, const emailInformation& thisObject);
QDataStream& operator>>(QDataStream& thisStream, emailInformation& thisObject);
QDataStream& operator<<(QDataStream& thisStream, const item& thisObject);
QDataStream& operator>>(QDataStream& thisStream, item& thisObject);
QDataStream& operator<<(QDataStream& thisStream, const options& thisObject);
QDataStream& operator>>(QDataStream& thisStream, options& thisObject);

Q_DECLARE_METATYPE(emailInformation)
Q_DECLARE_METATYPE(item)
Q_DECLARE_METATYPE(options)

#endif
