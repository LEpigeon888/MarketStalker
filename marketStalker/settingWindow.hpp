#ifndef SETTINGWINDOW_HPP
#define SETTINGWINDOW_HPP

#include <QtGui>
#include <QtCore>

#include "options.hpp"

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
