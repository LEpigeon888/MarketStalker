#include "getAPage.hpp"

getAPageClass::getAPageClass()
{
    reply = 0;
    manager.setCookieJar(new QNetworkCookieJar(&manager));
    isOnGet = false;
    endUse = false;
    deleteThis = true;
}

void getAPageClass::manuallyDelete(bool newDeleteThis)
{
    deleteThis = newDeleteThis;
}

getAPageClass::~getAPageClass()
{
    if(reply != 0 && deleteThis == true)
    {
        delete reply;
    }
}

void getAPageClass::setUrlToAccess(QString url)
{
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Firefox");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Cookie", "");
    request.setRawHeader("Connection", "Keep-Alive");

    reply = manager.get(request);
    isOnGet = true;

    connect(reply, SIGNAL(finished()), this, SLOT(emitSignalReady()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(emitSignalError()));
}

QNetworkReply* getAPageClass::getReply()
{
    return reply;
}

void getAPageClass::setEndUse(bool newValue)
{
    endUse = newValue;
}

bool getAPageClass::getIsOnGet()
{
    return isOnGet;
}

bool getAPageClass::getEndUse()
{
    return endUse;
}

void getAPageClass::emitSignalReady()
{
    isOnGet = false;
    emit isReady(this);
}

void getAPageClass::emitSignalError()
{
    isOnGet = false;
    emit errorGet(this);
}
