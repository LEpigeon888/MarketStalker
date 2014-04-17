#include "logsWindow.hpp"

logsWindowClass::logsWindowClass(QWidget* parent, logsInformation* newLogsInfo) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* labTextConnectToSmtp = new QLabel("Connecté au serveur SMTP :", this);
    QLabel* labTextAuthToSmtp = new QLabel("Authentifié au serveur SMTP :", this);
    QLabel* labTextSendMail = new QLabel("Envoie de mail réussi :", this);
    QLabel* labLogs = new QLabel("Logs :", this);
    QPushButton* buttonEraseLogs = new QPushButton("Supprimer les logs", this);

    logsInfo = newLogsInfo;
    buttonEraseLogs->setAutoDefault(false);
    boxLogs.setReadOnly(true);
    boxLogs.setText(logsInfo->logs);
    valueNeedUpdate();

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labTextConnectToSmtp, 0, 0);
    mainLayout->addWidget(&labConnectToSmtp, 0, 1, Qt::AlignRight);
    mainLayout->addWidget(labTextAuthToSmtp, 1, 0);
    mainLayout->addWidget(&labAuthToSmtp, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(labTextSendMail, 2, 0);
    mainLayout->addWidget(&labSendMailSucces, 2, 1, Qt::AlignRight);
    mainLayout->addWidget(labLogs, 3, 0, 1, 2);
    mainLayout->addWidget(&boxLogs, 4, 0, 1, 2);
    mainLayout->addWidget(buttonEraseLogs, 5, 0, 1, 2);

    setLayout(mainLayout);
    setWindowTitle("Logs");

    connect(buttonEraseLogs, SIGNAL(pressed()), this, SLOT(eraseLogs()));
}

void logsWindowClass::valueNeedUpdate()
{
    if(logsInfo->connectToSmtp == true)
    {
        labConnectToSmtp.setText("oui");
    }
    else
    {
        labConnectToSmtp.setText("non");
    }

    if(logsInfo->authToSmtp == true)
    {
        labAuthToSmtp.setText("oui");
    }
    else
    {
        labAuthToSmtp.setText("non");
    }

    if(logsInfo->sendMailSucces == true)
    {
        labSendMailSucces.setText("oui");
    }
    else
    {
        labSendMailSucces.setText("non");
    }
    boxLogs.setText(logsInfo->logs);
}

void logsWindowClass::eraseLogs()
{
    logsInfo->logs.clear();
    boxLogs.clear();
}
