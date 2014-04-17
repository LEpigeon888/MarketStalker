#include "mainWindow.hpp"

mainWindowClass::mainWindowClass()
{
    QMenuBar* menuBar = new QMenuBar(this);
    QAction* actionOptions = menuBar->addAction("Options");
    QAction* actionLogs = menuBar->addAction("Logs");
    QAction* actionProfile = menuBar->addAction("Profil");

    setMenuBar(menuBar);
    setCentralWidget(&marketStalker);
    setWindowTitle(marketStalker.getWindowName());

    connect(&marketStalker, SIGNAL(windowNameChanged(QString)), this, SLOT(setWindowTitle(QString)));
    connect(actionOptions, SIGNAL(triggered()), &marketStalker, SLOT(showOption()));
    connect(actionLogs, SIGNAL(triggered()), &marketStalker, SLOT(showLogs()));
    connect(actionProfile, SIGNAL(triggered()), &marketStalker, SLOT(showProfile()));
}
