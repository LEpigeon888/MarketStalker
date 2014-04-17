#ifndef SETTINGWINDOW_HPP
#define SETTINGWINDOW_HPP

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
};

QDataStream& operator<<(QDataStream& thisStream, const emailInformation& thisObject);
QDataStream& operator>>(QDataStream& thisStream, emailInformation& thisObject);
QDataStream& operator<<(QDataStream& thisStream, const options& thisObject);
QDataStream& operator>>(QDataStream& thisStream, options& thisObject);

Q_DECLARE_METATYPE(emailInformation)
Q_DECLARE_METATYPE(options)

class settingWindowClass : public QDialog
{
    Q_OBJECT
public:
    settingWindowClass();
    settingWindowClass(QWidget* parent, options* newOptions);
public slots:
    void boxHasChanged(bool newValue);
    void acceptOption();
    void rejectOption();
signals:
    void updateOption(bool euroChange, bool emailIsActiveChange, bool smtpOrEmailToCoChange, bool englishChange);
private:
    QLineEdit lineWindowName;
    QSpinBox boxItemPerPage;
    QDoubleSpinBox boxValueOfEuro;
    QCheckBox boxIsInEuro;
    QCheckBox boxIsInEnglish;
    QCheckBox boxAlwaysBeep;
    QCheckBox boxEmailActivate;
    QLineEdit lineSendTo;
    QLineEdit lineSendWith;
    QLineEdit lineMdpSendWith;
    QLineEdit lineSmtp;
    QSpinBox boxPortSmtp;
    QList<QLabel*> listOfLabForEmail;
    options* stockOptions;
};

#endif
