#ifndef GETAPAGE_HPP
#define GETAPAGE_HPP

#include <QtCore>
#include <QtNetwork>

class getAPageClass : public QObject
{
    Q_OBJECT
public:
    getAPageClass();
    ~getAPageClass();
    void manuallyDelete(bool newDeleteThis);
    void setUrlToAccess(QString url);
    QNetworkReply* getReply();
    void setEndUse(bool newValue);
    bool getIsOnGet();
    bool getEndUse();
public slots:
    void emitSignalReady();
    void emitSignalError();
signals:
    void isReady(getAPageClass* thisObject);
    void errorGet(getAPageClass* thisObject);
private:
    QNetworkAccessManager manager;
    QNetworkReply* reply;
    bool isOnGet;
    bool endUse;
    bool deleteThis;
};

#endif
