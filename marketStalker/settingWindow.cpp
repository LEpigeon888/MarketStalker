#include "settingWindow.hpp"

settingWindowClass::settingWindowClass(QWidget* parent, options* newOptions) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    lineWindowName.setText(newOptions->windowName);
    boxItemPerPage.setMinimum(10);
    boxItemPerPage.setMaximum(100);
    boxItemPerPage.setValue(newOptions->itemPerPage);
    boxValueOfEuro.setMinimum(0);
    boxValueOfEuro.setMaximum(100);
    boxValueOfEuro.setDecimals(10);
    boxValueOfEuro.setValue(newOptions->valueOfEuro);
    boxIsInEuro.setChecked(newOptions->isInEuro);
    boxIsInEnglish.setChecked(newOptions->isInEnglish);
    boxAlwaysBeep.setChecked(newOptions->alwaysBeep);
    boxEmailActivate.setChecked(newOptions->emailInfo.isActive);
    lineSendTo.setText(newOptions->emailInfo.emailTo);
    lineSendWith.setText(newOptions->emailInfo.emailWith);
    lineMdpSendWith.setText(newOptions->emailInfo.mdpWith);
    lineMdpSendWith.setEchoMode(QLineEdit::Password);
    lineSmtp.setText(newOptions->emailInfo.smtpServ);
    boxPortSmtp.setMaximum(65535);
    boxPortSmtp.setValue(newOptions->emailInfo.smtpPort);

    stockOptions = newOptions;

    QLabel* labWindowName = new QLabel("Nom de la fenêtre :", this);
    QLabel* labItemPerPage = new QLabel("Nombre d'item par page :", this);
    QLabel* labValueOfEuro = new QLabel("Valeur de l'euro :", this);
    QLabel* labIsInEuro = new QLabel("Affichage en euro :", this);
    QLabel* labIsInEnglish = new QLabel("Affichage en anglais :", this);
    QLabel* labAlwaysBeep = new QLabel("Biper en continue :", this);
    QPushButton* acceptButton = new QPushButton("Accepter", this);
    QPushButton* rejectButton = new QPushButton("Refuser", this);

    QLabel* labEmailActivate = new QLabel("Activer l'envoie d'email :", this);
    QLabel* labSendTo = new QLabel("Evoyer à :", this);
    QLabel* labSendWith = new QLabel("Envoyer avec :", this);
    QLabel* labMdpSendWith = new QLabel("Mot de passe :", this);
    QLabel* labSmtp = new QLabel("Serveur SMTP :", this);
    QLabel* labPortSmtp = new QLabel("Port :", this);

    listOfLabForEmail.append(labSendTo);
    listOfLabForEmail.append(labSendWith);
    listOfLabForEmail.append(labMdpSendWith);
    listOfLabForEmail.append(labSmtp);
    listOfLabForEmail.append(labPortSmtp);
    boxHasChanged(boxEmailActivate.isChecked());

    QFrame* firstSeparator = new QFrame(this);
    firstSeparator->setLineWidth(2);
    firstSeparator->setMidLineWidth(1);
    firstSeparator->setFrameShape(QFrame::HLine);
    firstSeparator->setFrameShadow(QFrame::Sunken);
    QFrame* lastSeparator = new QFrame(this);
    lastSeparator->setLineWidth(2);
    lastSeparator->setMidLineWidth(1);
    lastSeparator->setFrameShape(QFrame::HLine);
    lastSeparator->setFrameShadow(QFrame::Sunken);

    QGridLayout* layoutForEMail = new QGridLayout;
    layoutForEMail->addWidget(labEmailActivate, 0, 0);
    layoutForEMail->addWidget(&boxEmailActivate, 0, 1);
    layoutForEMail->addWidget(labSendTo, 1, 0);
    layoutForEMail->addWidget(&lineSendTo, 1, 1, 1, 3);
    layoutForEMail->addWidget(labSendWith, 2, 0);
    layoutForEMail->addWidget(&lineSendWith, 2, 1, 1, 3);
    layoutForEMail->addWidget(labMdpSendWith, 3, 0);
    layoutForEMail->addWidget(&lineMdpSendWith, 3, 1, 1, 3);
    layoutForEMail->addWidget(labSmtp, 4, 0);
    layoutForEMail->addWidget(&lineSmtp, 4, 1);
    layoutForEMail->addWidget(labPortSmtp, 4, 2);
    layoutForEMail->addWidget(&boxPortSmtp, 4, 3);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labWindowName, 0, 0);
    mainLayout->addWidget(&lineWindowName, 0, 1);
    mainLayout->addWidget(labItemPerPage, 1, 0);
    mainLayout->addWidget(&boxItemPerPage, 1, 1);
    mainLayout->addWidget(labValueOfEuro, 2, 0);
    mainLayout->addWidget(&boxValueOfEuro, 2, 1);
    mainLayout->addWidget(labIsInEuro, 3, 0);
    mainLayout->addWidget(&boxIsInEuro, 3, 1);
    mainLayout->addWidget(labIsInEnglish, 4, 0);
    mainLayout->addWidget(&boxIsInEnglish, 4, 1);
    mainLayout->addWidget(labAlwaysBeep, 5, 0);
    mainLayout->addWidget(&boxAlwaysBeep, 5, 1);
    mainLayout->addWidget(firstSeparator, 6, 0, 1, 2);
    mainLayout->addLayout(layoutForEMail, 7, 0, 1, 2);
    mainLayout->addWidget(lastSeparator, 8, 0, 1, 2);
    mainLayout->addWidget(acceptButton, 9, 0);
    mainLayout->addWidget(rejectButton, 9, 1);

    setLayout(mainLayout);
    setWindowTitle("Option");

    connect(&boxEmailActivate, SIGNAL(toggled(bool)), this, SLOT(boxHasChanged(bool)));
    connect(acceptButton, SIGNAL(pressed()), this, SLOT(acceptOption()));
    connect(rejectButton, SIGNAL(pressed()), this, SLOT(rejectOption()));
}

void settingWindowClass::boxHasChanged(bool newValue)
{
    QMutableListIterator<QLabel*> iterator(listOfLabForEmail);
    while(iterator.hasNext())
    {
        iterator.next()->setDisabled(!newValue);
    }

    lineSendTo.setDisabled(!newValue);
    lineSendWith.setDisabled(!newValue);
    lineMdpSendWith.setDisabled(!newValue);
    lineSmtp.setDisabled(!newValue);
    boxPortSmtp.setDisabled(!newValue);
}

void settingWindowClass::acceptOption()
{
    bool euroChange = (stockOptions->isInEuro != boxIsInEuro.isChecked() || stockOptions->valueOfEuro != boxValueOfEuro.value());
    bool emailIsActiveChange = (stockOptions->emailInfo.isActive != boxEmailActivate.isChecked());
    bool smtpOrEmailToCoChange = (stockOptions->emailInfo.smtpServ != lineSmtp.text() || stockOptions->emailInfo.smtpPort != boxPortSmtp.value() || stockOptions->emailInfo.mdpWith != lineMdpSendWith.text() || stockOptions->emailInfo.emailWith != lineSendWith.text());
    bool englishChange = (stockOptions->isInEnglish != boxIsInEnglish.isChecked());
    stockOptions->windowName = lineWindowName.text();
    stockOptions->itemPerPage = boxItemPerPage.value();
    stockOptions->valueOfEuro = boxValueOfEuro.value();
    stockOptions->isInEuro = boxIsInEuro.isChecked();
    stockOptions->isInEnglish = boxIsInEnglish.isChecked();
    stockOptions->alwaysBeep = boxAlwaysBeep.isChecked();
    stockOptions->emailInfo.isActive = boxEmailActivate.isChecked();
    stockOptions->emailInfo.emailTo = lineSendTo.text();
    stockOptions->emailInfo.emailWith = lineSendWith.text();
    stockOptions->emailInfo.mdpWith = lineMdpSendWith.text();
    stockOptions->emailInfo.smtpServ = lineSmtp.text();
    stockOptions->emailInfo.smtpPort = boxPortSmtp.value();
    emit updateOption(euroChange, emailIsActiveChange, smtpOrEmailToCoChange, englishChange);
    this->close();
}

void settingWindowClass::rejectOption()
{
    this->close();
}
