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
    QList<QTreeWidgetItem> listOfItemBlacklisted;
};

QDataStream& operator<<(QDataStream& thisStream, const emailInformation& thisObject);
QDataStream& operator>>(QDataStream& thisStream, emailInformation& thisObject);
QDataStream& operator<<(QDataStream& thisStream, const options& thisObject);
QDataStream& operator>>(QDataStream& thisStream, options& thisObject);

Q_DECLARE_METATYPE(emailInformation)
Q_DECLARE_METATYPE(options)

#endif
