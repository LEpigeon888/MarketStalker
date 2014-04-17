#include "treeWidgetItem.hpp"


bool treeWidgetItemClass::operator<(const QTreeWidgetItem &other) const
{
    int sortCol = treeWidget() ? treeWidget()->sortColumn() : 0;

    if(sortCol == COLUMN_ITEM_VALUE)
    {
        return text(sortCol).toDouble() < other.text(sortCol).toDouble();
    }
    else
    {
        return text(sortCol) < other.text(sortCol);
    }
}
