#include "blacklistWindow.hpp"
#include "treeWidgetItem.hpp"

blacklistWindowClass::blacklistWindowClass(QWidget* parent, options* newOptions) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* labListOfItemBlacklisted = new QLabel("Items dans la blacklist :", this);

    QStringList horizontalHeader;
    horizontalHeader.append("Jeu");
    horizontalHeader.append("Nom");
    horizontalHeader.append("Prix");

    currentOptions = newOptions;
    listOfItemBlacklisted.setSortingEnabled(true);
    listOfItemBlacklisted.setHeaderLabels(horizontalHeader);
    listOfItemBlacklisted.setRootIsDecorated(false);
    listOfItemBlacklisted.setContextMenuPolicy(Qt::CustomContextMenu);

    QMutableListIterator<item> iteratorBlacklist(currentOptions->listOfItemBlacklisted);
    while(iteratorBlacklist.hasNext())
    {
        item thisItem = iteratorBlacklist.next();
        treeWidgetItemClass* newItem = new treeWidgetItemClass;
        newItem->setText(COLUMN_GAME_NAME, thisItem.gameName);
        newItem->setText(COLUMN_ITEM_NAME, thisItem.name);
        newItem->setText(COLUMN_ITEM_LINK, thisItem.link);

        if(currentOptions->isInEuro == false)
        {
            newItem->setText(COLUMN_ITEM_VALUE, thisItem.value);
        }
        else
        {
            newItem->setText(COLUMN_ITEM_VALUE, QString::number(thisItem.value.toDouble() * currentOptions->valueOfEuro));
        }

        listOfItemBlacklisted.addTopLevelItem(newItem);
    }

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labListOfItemBlacklisted, 0, 0);
    mainLayout->addWidget(&listOfItemBlacklisted, 1, 0);

    setLayout(mainLayout);
    setWindowTitle("Blacklist");

    connect(&listOfItemBlacklisted, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(goToUrl(QTreeWidgetItem*)));
    connect(&listOfItemBlacklisted, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(creatContextMenu(QPoint)));
}

void blacklistWindowClass::goToUrl(QTreeWidgetItem* thisItem)
{
    QString linkToGo = QUrl::fromPercentEncoding(thisItem->text(COLUMN_ITEM_LINK).replace("\\/", "/").toUtf8());
    int indexForString = linkToGo.indexOf('\\');
    int secIndexForString = linkToGo.indexOf('\"');

    if(indexForString != -1 || secIndexForString != -1)
    {
        if(indexForString != -1)
        {
            if(indexForString > secIndexForString)
            {
                indexForString = secIndexForString;
            }
        }
        else
        {
            indexForString = secIndexForString;
        }

        linkToGo = linkToGo.left(indexForString);
    }

    QDesktopServices::openUrl(QUrl(linkToGo));
}

void blacklistWindowClass::creatContextMenu(const QPoint &thisPoint)
{
    QTreeWidgetItem* itemSelected = listOfItemBlacklisted.itemAt(thisPoint);
    if(itemSelected != 0)
    {
        QAction* actionSelected = 0;
        QMenu contextMenu;
        QAction* actionRemove = contextMenu.addAction("Supprimer cet objet de la blacklist");
        actionSelected = contextMenu.exec(listOfItemBlacklisted.viewport()->mapToGlobal(thisPoint));

        if(actionSelected == actionRemove)
        {
            QTreeWidgetItem* tmpTreeItem = listOfItemBlacklisted.takeTopLevelItem(listOfItemBlacklisted.indexOfTopLevelItem(itemSelected));
            QMutableListIterator<item> iteratorBlacklist(currentOptions->listOfItemBlacklisted);
            while(iteratorBlacklist.hasNext())
            {
                item thisItem = iteratorBlacklist.next();
                if(thisItem.link == tmpTreeItem->text(COLUMN_ITEM_LINK).replace("\\/", "/"))
                {
                    iteratorBlacklist.remove();
                    break;
                }
            }
            delete tmpTreeItem;
        }
    }
}
