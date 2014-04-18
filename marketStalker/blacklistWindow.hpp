#ifndef BLACKLISTWINDOW_HPP
#define BLACKLISTWINDOW_HPP

#include <QtGui>
#include <QtCore>

#include "options.hpp"

class blacklistWindowClass : public QDialog
{
    Q_OBJECT
public:
    blacklistWindowClass(QWidget* parent, options* newOptions);
public slots:
    void goToUrl(QTreeWidgetItem* thisItem);
    void creatContextMenu(const QPoint& thisPoint);
private:
    QTreeWidget listOfItemBlacklisted;
    options* currentOptions;
};

#endif
