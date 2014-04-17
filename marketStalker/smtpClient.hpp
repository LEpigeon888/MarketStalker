#ifndef SMTPCLIENT_HPP
#define SMTPCLIENT_HPP

#include <QtCore>
#include <QtNetwork>

struct email
{
    QString from;
    QString to;
    QString subject;
    QString message;
};

class smtpClientClass : public QObject
{
    Q_OBJECT
public:
    smtpClientClass(const QString& newHost = "smtp.gmail.com", int newPort = 465);
    void setHost(QString &newHost);
    void setPort(int newPort);
    void setUser(const QString &newUser);
    void setPassword(const QString &newPassword);
    bool connectToHost();
    bool login();
    bool login(const QString &user, const QString &password);
    bool sendMail(email& thisMail);
    void quit();
    bool sendAndWait(const QString& thisMessage, int succesCode = 250);
private:
    bool waitForResponse();
    bool sendMessage(const QString& text);

    QSslSocket* socket;
    QString host;
    int port;
    QString user;
    QString password;
    int connectionTimeout;
    int responseTimeout;
    int sendMessageTimeout;
    QString responseText;
    int responseCode;

};

#endif
