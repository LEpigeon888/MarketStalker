#include "mainWindow.hpp"

mainWindowClass::mainWindowClass()
{
    QMenuBar* menuBar = new QMenuBar(this);
    QAction* actionOptions = menuBar->addAction("Options");
    QAction* actionProfile = menuBar->addAction("Profil");
    QAction* actionBlacklist = menuBar->addAction("Blacklist");
    QAction* actionLogs = menuBar->addAction("Logs");

    setMenuBar(menuBar);
    setCentralWidget(&marketStalker);
    setWindowTitle(marketStalker.getWindowName());

    connect(&marketStalker, SIGNAL(windowNameChanged(QString)), this, SLOT(setWindowTitle(QString)));
    connect(actionOptions, SIGNAL(triggered()), &marketStalker, SLOT(showOption()));
    connect(actionProfile, SIGNAL(triggered()), &marketStalker, SLOT(showProfile()));
    connect(actionBlacklist, SIGNAL(triggered()), &marketStalker, SLOT(showBlacklist()));
    connect(actionLogs, SIGNAL(triggered()), &marketStalker, SLOT(showLogs()));
}
