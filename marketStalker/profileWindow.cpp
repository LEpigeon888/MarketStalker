#include "profileWindow.hpp"

profileWindowClass::profileWindowClass(QWidget* parent, options* newOptions, QString* newProfileUsed) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint), setting("config.ini", QSettings::IniFormat)
{
    setAttribute(Qt::WA_DeleteOnClose);
    qRegisterMetaTypeStreamOperators<emailInformation>("emailInformation");
    qMetaTypeId<emailInformation>();
    qRegisterMetaTypeStreamOperators<options>("options");
    qMetaTypeId<options>();

    QLabel* labListOfProfile = new QLabel("Profil : ", this);
    QPushButton* buttonSave = new QPushButton("Sauvegarder", this);
    QPushButton* buttonAdd = new QPushButton("Ajouter", this);
    QPushButton* buttonDel = new QPushButton("Supprimer", this);
    QPushButton* buttonSelect = new QPushButton("Sélectionner", this);

    currentOptions = newOptions;
    profileUsed = newProfileUsed;
    listOfProfile.addItems(setting.allKeys());
    buttonSave->setAutoDefault(false);
    buttonAdd->setAutoDefault(false);
    buttonDel->setAutoDefault(false);
    buttonSelect->setAutoDefault(true);

    if(listOfProfile.findText(*profileUsed) == -1)
    {
        listOfProfile.addItem(*profileUsed);
        setting.setValue(*profileUsed, qVariantFromValue(*currentOptions));
    }
    listOfProfile.setCurrentIndex(listOfProfile.findText(*profileUsed));

    QHBoxLayout* layoutSelectProfile = new QHBoxLayout;
    layoutSelectProfile->addWidget(labListOfProfile);
    layoutSelectProfile->addWidget(&listOfProfile);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addLayout(layoutSelectProfile, 0, 0, 1, 3);
    mainLayout->addWidget(buttonSave, 1, 0);
    mainLayout->addWidget(buttonAdd, 1, 1);
    mainLayout->addWidget(buttonDel, 1, 2);
    mainLayout->addWidget(buttonSelect, 2, 0, 1, 3);

    setLayout(mainLayout);
    setWindowTitle("Profils");

    connect(buttonSave, SIGNAL(pressed()), this, SLOT(saveProfile()));
    connect(buttonAdd, SIGNAL(pressed()), this, SLOT(addNewProfile()));
    connect(buttonDel, SIGNAL(pressed()), this, SLOT(deleteProfile()));
    connect(buttonSelect, SIGNAL(pressed()), this, SLOT(selectProfile()));
}

void profileWindowClass::saveProfile()
{
    setting.setValue(listOfProfile.currentText(), qVariantFromValue(*currentOptions));
}

void profileWindowClass::addNewProfile()
{
    bool ok = false;
    QString newProfile = QInputDialog::getText(this, "Profil", "Nom du nouveau profil : ", QLineEdit::Normal, QString(), &ok, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);

    if (ok == true && newProfile.isEmpty() == false && listOfProfile.findText(newProfile) == -1)
    {
        listOfProfile.addItem(newProfile);
        setting.setValue(newProfile, QVariant());
    }
}

void profileWindowClass::deleteProfile()
{
    int choice = QMessageBox::question(this, "Profil", "Voulez-vous vraiment supprimer ce profil ?", QMessageBox ::Yes | QMessageBox::No);

    if(choice == QMessageBox::Yes)
    {
        setting.remove(listOfProfile.currentText());
        listOfProfile.removeItem(listOfProfile.currentIndex());
    }
}

void profileWindowClass::selectProfile()
{
    *profileUsed = listOfProfile.currentText();
    *currentOptions = qVariantValue<options>(setting.value(*profileUsed));
    emit allChanged();

    close();
}
