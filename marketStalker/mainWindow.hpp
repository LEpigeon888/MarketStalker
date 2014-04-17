#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui>
#include <QtCore>

#include "marketStalker.hpp"

class mainWindowClass : public QMainWindow
{
public:
    mainWindowClass();
private:
    marketStalkerClass marketStalker;
};
#endif
