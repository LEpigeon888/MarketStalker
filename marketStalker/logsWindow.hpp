#ifndef LOGSWINDOW_HPP
#define LOGSWINDOW_HPP

#include <QtGui>
#include <QtCore>

struct logsInformation
{
    bool connectToSmtp;
    bool authToSmtp;
    bool sendMailSucces;
    QString logs;
};

class logsWindowClass : public QDialog
{
    Q_OBJECT
public:
    logsWindowClass(QWidget* parent, logsInformation* newLogsInfo);
public slots:
    void valueNeedUpdate();
    void eraseLogs();
private:
    QLabel labConnectToSmtp;
    QLabel labAuthToSmtp;
    QLabel labSendMailSucces;
    QTextEdit boxLogs;
    logsInformation* logsInfo;
};

#endif
