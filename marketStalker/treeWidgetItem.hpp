#ifndef TREEWIDGETITEM_HPP
#define TREEWIDGETITEM_HPP

#include <QTreeWidgetItem>

#define COLUMN_GAME_NAME 0
#define COLUMN_ITEM_NAME 1
#define COLUMN_ITEM_VALUE 2
#define COLUMN_ITEM_DATE 3
#define COLUMN_ITEM_LINK 4
#define COLUMN_ITEM_VALUE_DOLLAR 5

class treeWidgetItemClass : public QTreeWidgetItem
{
public:
    treeWidgetItemClass(int type = Type) : QTreeWidgetItem(type) {}
    treeWidgetItemClass(QTreeWidget *tree) : QTreeWidgetItem(tree)  {}
    treeWidgetItemClass(QTreeWidget * parent, const QStringList & strings) : QTreeWidgetItem (parent,strings)  {}
    bool operator<(const QTreeWidgetItem &other) const;
};

#endif
