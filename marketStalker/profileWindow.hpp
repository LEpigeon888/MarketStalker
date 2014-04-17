#ifndef PROFILWINDOW_HPP
#define PROFILWINDOW_HPP

#include <QtGui>
#include <QtCore>

#include "settingWindow.hpp"

class profileWindowClass : public QDialog
{
    Q_OBJECT
public:
    profileWindowClass(QWidget* parent, options* newOptions, QString* newProfileUsed);
public slots:
    void editProfile();
    void addNewProfile();
    void deleteProfile();
    void selectProfile();
signals:
    void allChanged();
private:
    QSettings setting;
    QComboBox listOfProfile;
    options* currentOptions;
    QString* profileUsed;
};

#endif
