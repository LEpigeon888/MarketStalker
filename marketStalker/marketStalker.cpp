#include "marketStalker.hpp"
#include "treeWidgetItem.hpp"
#include "profileWindow.hpp"

marketStalkerClass::marketStalkerClass(QWidget* parent) : QWidget(parent)
{
    QLabel* labMinValue = new QLabel("Min :", this);
    QLabel* labMaxValue = new QLabel("Max :", this);
    QLabel* labTimeRefresh = new QLabel("Temps d'attente :", this);
    QLabel* labStringSearch = new QLabel("Rechercher :", this);
    QLabel* labItemFound = new QLabel("Liste des objets trouvés :", this);;
    QLabel* labItemList = new QLabel("Liste des objets :", this);;
    QPushButton* buttonUpdateSearch = new QPushButton("Mettre à jour les paramètres de recherche", this);

    QTimer* timerErase = new QTimer(this);
    timerErase->start(2000);

    QStringList horizontalHeader;
    horizontalHeader.append("Jeu");
    horizontalHeader.append("Nom");
    horizontalHeader.append("Prix");
    horizontalHeader.append("Date");

    timeRefresh = 10;
    minValue = 0;
    maxValue = 10;
    activeOption.windowName = "Market Stalker v1.12";
    activeOption.itemPerPage = 20;
    activeOption.valueOfEuro = 0.720097933;
    activeOption.isInEuro = false;
    boxIsInDollar = true;
    updateTime = false;
    inGetPage = false;
    activeOption.alwaysBeep = true;
    isOnFocus = false;
    activeOption.isInEnglish = false;
    aditionalOptions = "l=french&";
    emailSender = 0;
    profileUsed = "defaut";
    activeOption.emailInfo.isActive = false;
    activeOption.emailInfo.emailWith = "marketStalker888@gmail.com";
    activeOption.emailInfo.mdpWith = "superMarketStalkerMdp333";
    activeOption.emailInfo.smtpServ = "smtp.gmail.com";
    activeOption.emailInfo.smtpPort = 465;
    logsInfo.connectToSmtp = false;
    logsInfo.authToSmtp = false;
    logsInfo.sendMailSucces = false;
    firstPageGet.manuallyDelete(false);
    boxTimeRefresh.setValue(timeRefresh);
    boxTimeRefresh.setMinimum(0);
    boxMinValue.setValue(minValue);
    boxMinValue.setMinimum(0);
    boxMinValue.setMaximum(9999);
    boxMaxValue.setValue(maxValue);
    boxMaxValue.setMinimum(0);
    boxMaxValue.setMaximum(9999);
    labStatuOfUpdate.setText("Rien");
    labNbItemFound.setText("0");
    labNbItemList.setText("0");
    labNbItemTotal.setText("Total : 0");
    timerForGetPage.setInterval(timeRefresh * 1000);
    timerForGetPage.start();

    listItemFound.setSortingEnabled(true);
    listItemFound.setHeaderLabels(horizontalHeader);
    listItemFound.setRootIsDecorated(false);
    listItemFound.setContextMenuPolicy(Qt::CustomContextMenu);
    horizontalHeader.pop_back();
    listItemList.setSortingEnabled(true);
    listItemList.setHeaderLabels(horizontalHeader);
    listItemList.setRootIsDecorated(false);
    listItemList.setContextMenuPolicy(Qt::CustomContextMenu);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(labMinValue, 0, 0, 1, 1);
    mainLayout->addWidget(&boxMinValue, 0, 1, 1, 1);
    mainLayout->addWidget(labMaxValue, 0, 2, 1, 1);
    mainLayout->addWidget(&boxMaxValue, 0, 3, 1, 1);
    mainLayout->addWidget(labTimeRefresh, 0, 4, 1, 1);
    mainLayout->addWidget(&boxTimeRefresh, 0, 5, 1, 1);
    mainLayout->addWidget(labStringSearch, 1, 0, 1, 1);
    mainLayout->addWidget(&lineStringSearch, 1, 1, 1, 5);
    mainLayout->addWidget(buttonUpdateSearch, 2, 0, 1, 6);
    mainLayout->addWidget(labItemFound, 3, 0, 1, 4);
    mainLayout->addWidget(&labNbItemFound, 3, 4, 1, 2, Qt::AlignRight);
    mainLayout->addWidget(&listItemFound, 4, 0, 1, 6);
    mainLayout->addWidget(labItemList, 5, 0, 1, 4);
    mainLayout->addWidget(&labNbItemList, 5, 4, 1, 2, Qt::AlignRight);
    mainLayout->addWidget(&listItemList, 6, 0, 1, 6);
    mainLayout->addWidget(&labStatuOfUpdate, 7, 0, 1, 4);
    mainLayout->addWidget(&labNbItemTotal, 7, 4, 1, 2, Qt::AlignRight);

    setLayout(mainLayout);

    connect(&lineStringSearch, SIGNAL(returnPressed()), this, SLOT(updateValue()));
    connect(buttonUpdateSearch, SIGNAL(pressed()), this, SLOT(updateValue()));
    connect(&timerForGetPage, SIGNAL(timeout()), this, SLOT(startGetPage()));
    connect(&listItemFound, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(goToUrl(QTreeWidgetItem*)));
    connect(&listItemList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(goToUrl(QTreeWidgetItem*)));
    connect(timerErase, SIGNAL(timeout()), this, SLOT(checkPageEndUse()));
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(checkFocus(QWidget*,QWidget*)));
    connect(&timeForWarn, SIGNAL(timeout()), this, SLOT(itsTimeToWarn()));
    connect(&listItemFound, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(creatContextMenu(QPoint)));
    connect(&listItemList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(creatContextMenu(QPoint)));
}

marketStalkerClass::~marketStalkerClass()
{
    if(emailSender != 0)
    {
        delete emailSender;
    }
}

void marketStalkerClass::setNewItem(QString fromThisSource, bool isFirstPass)
{
    QStringList listOfLink;
    QStringList listOfValue;
    QStringList listOfName;
    QStringList listOfGameName;

    if(isFirstPass == true)
    {
        parseString(fromThisSource, "<a class=\"market_listing_row_link\" href=\"(.+)\">", listOfLink);
        parseString(fromThisSource, "<span style=\"color:.+\">&#36;(.+) USD</span>", listOfValue);
        parseString(fromThisSource, "<span id=\"result_[0-9]+_name\" class=\"market_listing_item_name\" style=\"color:.+\">(.+)</span>", listOfName);
        parseString(fromThisSource, "<span class=\"market_listing_game_name\">(.+)</span>", listOfGameName);
    }
    else
    {
        parseString(fromThisSource, "<a class=.+\"market_listing_row_link.+\" href=.+\"(.+)\\\\\">", listOfLink);
        parseString(fromThisSource, "<span style=.+\"color:.+\">&#36;(.+) USD<.+/span>", listOfValue);
        parseString(fromThisSource, "<span id=.+\"result_[0-9]+_name.+\" class=.+\"market_listing_item_name.+\" style=.+\"color:.+\">(.+)<.+/span>", listOfName);
        parseString(fromThisSource, "<span class=.+\"market_listing_game_name.+\">(.+)<.+/span>", listOfGameName);
    }

    if(listOfLink.size() != listOfValue.size() || listOfLink.size() != listOfName.size() || listOfLink.size() != listOfGameName.size())
    {
        return;
    }

    for(int i = 0; i < listOfLink.size(); ++i)
    {
        bool existBefore = false;
        QList<QTreeWidgetItem*> itemResultList = listItemList.findItems(listOfName.at(i), Qt::MatchExactly, 1);
        QMutableListIterator<QTreeWidgetItem*> iteratorList(itemResultList);
        while(iteratorList.hasNext())
        {
            QTreeWidgetItem* tmpItem = iteratorList.next();
            if(tmpItem->text(COLUMN_GAME_NAME) == listOfGameName.at(i))
            {
                existBefore = true;
                tmpItem->setText(COLUMN_ITEM_VALUE_DOLLAR, listOfValue.at(i));
                if(activeOption.isInEuro == false)
                {
                    tmpItem->setText(COLUMN_ITEM_VALUE, listOfValue.at(i));
                }
                else
                {
                    tmpItem->setText(COLUMN_ITEM_VALUE, QString::number(listOfValue.at(i).toDouble() * activeOption.valueOfEuro));
                }
                if(tmpItem->text(COLUMN_ITEM_VALUE).toDouble() >= minValue && tmpItem->text(COLUMN_ITEM_VALUE).toDouble() <= maxValue)
                {
                    tmpItem->setText(COLUMN_ITEM_DATE, QTime::currentTime().toString("HH:mm:ss"));
                    listItemFound.addTopLevelItem(listItemList.takeTopLevelItem(listItemList.indexOfTopLevelItem(tmpItem)));
                    labNbItemFound.setText(QString::number(listItemFound.topLevelItemCount()));
                    labNbItemList.setText(QString::number(listItemList.topLevelItemCount()));
                    warnForValue();

                    if(activeOption.emailInfo.isActive == true)
                    {
                        item newItemForSend;
                        newItemForSend.name = tmpItem->text(COLUMN_ITEM_NAME);
                        newItemForSend.value = tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR);
                        newItemForSend.link = QUrl::fromPercentEncoding(tmpItem->text(COLUMN_ITEM_LINK).replace("\\/", "/").toUtf8());;

                        listOfItemInRange.append(newItemForSend);
                    }
                }
                break;
            }
        }

        if(existBefore == false)
        {
            QList<QTreeWidgetItem*> itemResultFound = listItemFound.findItems(listOfName.at(i), Qt::MatchExactly, 1);
            QMutableListIterator<QTreeWidgetItem*> iteratorFound(itemResultFound);
            while(iteratorFound.hasNext())
            {
                QTreeWidgetItem* tmpItem = iteratorFound.next();
                if(tmpItem->text(COLUMN_GAME_NAME) == listOfGameName.at(i))
                {
                    QString oldValue = tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR);
                    existBefore = true;
                    tmpItem->setText(COLUMN_ITEM_VALUE_DOLLAR, listOfValue.at(i));
                    if(activeOption.isInEuro == false)
                    {
                        tmpItem->setText(COLUMN_ITEM_VALUE, listOfValue.at(i));
                    }
                    else
                    {
                        tmpItem->setText(COLUMN_ITEM_VALUE, QString::number(listOfValue.at(i).toDouble() * activeOption.valueOfEuro));
                    }
                    if(tmpItem->text(COLUMN_ITEM_VALUE).toDouble() < minValue || tmpItem->text(COLUMN_ITEM_VALUE).toDouble() > maxValue)
                    {
                        listItemList.addTopLevelItem(listItemFound.takeTopLevelItem(listItemFound.indexOfTopLevelItem(tmpItem)));
                        labNbItemFound.setText(QString::number(listItemFound.topLevelItemCount()));
                        labNbItemList.setText(QString::number(listItemList.topLevelItemCount()));
                    }
                    else if(oldValue != tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR))
                    {
                        tmpItem->setText(COLUMN_ITEM_DATE, QTime::currentTime().toString("HH:mm:ss"));
                        warnForValue();

                        if(activeOption.emailInfo.isActive == true)
                        {
                            item newItemForSend;
                            newItemForSend.name = tmpItem->text(COLUMN_ITEM_NAME);
                            newItemForSend.value = tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR);
                            newItemForSend.link = QUrl::fromPercentEncoding(tmpItem->text(COLUMN_ITEM_LINK).replace("\\/", "/").toUtf8());;

                            listOfItemInRange.append(newItemForSend);
                        }
                    }
                    break;
                }
            }
        }

        if(existBefore == false)
        {
            treeWidgetItemClass* newItem = new treeWidgetItemClass;
            newItem->setText(COLUMN_GAME_NAME, listOfGameName.at(i));
            newItem->setText(COLUMN_ITEM_NAME, listOfName.at(i));
            newItem->setText(COLUMN_ITEM_DATE, QTime::currentTime().toString("HH:mm:ss"));
            newItem->setText(COLUMN_ITEM_LINK, listOfLink.at(i));
            newItem->setText(COLUMN_ITEM_VALUE_DOLLAR, listOfValue.at(i));

            if(activeOption.isInEuro == false)
            {
                newItem->setText(COLUMN_ITEM_VALUE, listOfValue.at(i));
            }
            else
            {
                newItem->setText(COLUMN_ITEM_VALUE, QString::number(listOfValue.at(i).toDouble() * activeOption.valueOfEuro));
            }

            if(newItem->text(COLUMN_ITEM_VALUE).toDouble() >= minValue && newItem->text(COLUMN_ITEM_VALUE).toDouble() <= maxValue)
            {
                listItemFound.addTopLevelItem(newItem);
                labNbItemFound.setText(QString::number(listItemFound.topLevelItemCount()));
                warnForValue();

                if(activeOption.emailInfo.isActive == true)
                {
                    item newItemForSend;
                    newItemForSend.name = newItem->text(COLUMN_ITEM_NAME);
                    newItemForSend.value = newItem->text(COLUMN_ITEM_VALUE_DOLLAR);
                    newItemForSend.link = newItem->text(COLUMN_ITEM_LINK).replace("\\/", "/").toUtf8();

                    listOfItemInRange.append(newItemForSend);
                }
            }
            else
            {
                listItemList.addTopLevelItem(newItem);
                labNbItemList.setText(QString::number(listItemList.topLevelItemCount()));
            }

            labNbItemTotal.setText(QString("Total : ") + QString::number(labNbItemFound.text().toInt() + labNbItemList.text().toInt()));
        }
    }
}

void marketStalkerClass::parseString(const QString& thisString, const std::string& thisRegExp, QStringList& toThisStringList)
{
    int pos = 0;
    QRegExp exp;
    exp.setPattern(QString(thisRegExp.c_str()));
    exp.setMinimal(true);
    toThisStringList.clear();
    while((pos = exp.indexIn(thisString, pos)) != -1)
    {
        toThisStringList << removeUnicodeFromString(exp.cap(1));
        pos += exp.matchedLength();
    }
}

QString marketStalkerClass::removeUnicodeFromString(QString thisString)
{
    int pos = 0;
    QRegExp exp;
    exp.setPattern("\\\\u(.{4})");
    exp.setMinimal(true);
    while((pos = exp.indexIn(thisString, pos)) != -1)
    {
        thisString.replace(pos, exp.matchedLength(), QChar(QString("0x" + exp.cap(1)).toUInt(0, 16))).replace(QString("\\u00e8"), QString("\u00e8")).replace(QString("\\u00e9"), QString("\u00e9"));
        pos += exp.matchedLength();
    }

    return thisString;
}

void marketStalkerClass::warnForValue()
{
    QApplication::alert(this);
    QApplication::beep();
    if(timeForWarn.isActive() == false && activeOption.alwaysBeep == true && isOnFocus == false)
    {
        timeForWarn.start(1000);
    }
}


const QString& marketStalkerClass::getWindowName()
{
    return activeOption.windowName;
}

void marketStalkerClass::checkPageEndUse()
{
    QMutableListIterator< QSharedPointer<getAPageClass> > iterator(listOfPageGet);
    while(iterator.hasNext())
    {
        if(iterator.next()->getEndUse() == true)
        {
            iterator.remove();
        }
    }

    if(listOfPageGet.empty() == true && inGetPage == false)
    {
        labStatuOfUpdate.setText("Mise à jour terminée !");

        if(activeOption.emailInfo.isActive == true && listOfItemInRange.empty() == false)
        {
            QMutableListIterator<item> iterator(listOfItemInRange);
            email newMail;

            newMail.from = activeOption.emailInfo.emailWith;
            newMail.to = activeOption.emailInfo.emailTo;
            newMail.subject = QString::number(listOfItemInRange.size()) + " nouveaux objets trouvés !";

            while(iterator.hasNext())
            {
                item thisItem = iterator.next();
                newMail.message += thisItem.name + " à $" + thisItem.value + " : " + thisItem.link + "\n";
            }

            logsInfo.sendMailSucces = emailSender->sendMail(newMail);
            listOfItemInRange.clear();
            //logsInfo.logs.append("Envoi d'un email...\n");
            emit logsChanged();
        }

        updateTime = false;
    }
}

void marketStalkerClass::updateValue()
{
    listOfPageGet.clear();
    minValue = boxMinValue.value();
    maxValue = boxMaxValue.value();
    timeRefresh = boxTimeRefresh.value();
    listItemFound.clear();
    listItemList.clear();
    labNbItemFound.setText("0");
    labNbItemList.setText("0");
    labNbItemTotal.setText("Total : 0");
    timerForGetPage.setInterval(timeRefresh * 1000);
    timerForGetPage.start();
    stringSearch = lineStringSearch.text();
    startGetPage();
}

void marketStalkerClass::startGetPage()
{
    if(firstPageGet.getIsOnGet() == false && stringSearch.isEmpty() == false && updateTime == false)
    {
        QString url = QString("http://steamcommunity.com/market/search?") + aditionalOptions + QString("q=") + stringSearch;
        labStatuOfUpdate.setText("Récupération des informations...");
        updateTime = true;
        inGetPage = true;
        firstPageGet.setUrlToAccess(url);
        //logsInfo.logs.append(QString("Récupération de : ") + url + QString("...\n"));
        emit logsChanged();
        connect(&firstPageGet, SIGNAL(isReady(getAPageClass*)), this, SLOT(beginAllGet()));
    }
}

void marketStalkerClass::beginAllGet()
{
    int numberOfItem;
    int currentNumber = 0;
    QRegExp expNumberOfPage;
    QString sourcePage = firstPageGet.getReply()->readAll();
    firstPageGet.getReply()->deleteLater();
    labStatuOfUpdate.setText("Mise à jour en cours...");

    expNumberOfPage.setPattern(",\"total_count\":([0-9]+),\"");
    expNumberOfPage.setMinimal(true);
    expNumberOfPage.indexIn(sourcePage);
    numberOfItem = expNumberOfPage.cap(1).toInt();
    currentNumber = 10;

    while(currentNumber < numberOfItem)
    {
        QString url = QString("http://steamcommunity.com/market/search/render/?") + aditionalOptions + QString("query=") + stringSearch + QString("&start=") + QString::number(currentNumber) + QString("&count=") + QString::number(activeOption.itemPerPage) + QString("&search_descriptions=0&sort_column=default&sort_dir=desc");
        QSharedPointer<getAPageClass> newPage(new getAPageClass);
        newPage->setUrlToAccess(url);
        currentNumber += activeOption.itemPerPage;
        //logsInfo.logs.append(QString("Récupération de : ") + url + QString("...\n"));
        emit logsChanged();
        connect(newPage.data(), SIGNAL(isReady(getAPageClass*)), this, SLOT(thisGetEnd(getAPageClass*)));
        connect(newPage.data(), SIGNAL(errorGet(getAPageClass*)), this, SLOT(errorDelete(getAPageClass*)));
        listOfPageGet.append(newPage);
    }

    setNewItem(sourcePage, true);

    inGetPage = false;
}

void marketStalkerClass::thisGetEnd(getAPageClass* thisPage)
{
    setNewItem(thisPage->getReply()->readAll());
    thisPage->setEndUse(true);
}

void marketStalkerClass::goToUrl(QTreeWidgetItem* thisItem)
{
    QDesktopServices::openUrl(QUrl(QUrl::fromPercentEncoding(thisItem->text(COLUMN_ITEM_LINK).replace("\\/", "/").toUtf8())));
}

void marketStalkerClass::showOption()
{
    settingWindowClass* mySettingWindow = new settingWindowClass(this, &activeOption);
    connect(mySettingWindow, SIGNAL(updateOption(bool,bool,bool,bool)), this, SLOT(updateOption(bool,bool,bool,bool)));
    mySettingWindow->exec();
}

void marketStalkerClass::showLogs()
{
    logsWindowClass* myLogsWindow = new logsWindowClass(this, &logsInfo);
    connect(this, SIGNAL(logsChanged()), myLogsWindow, SLOT(valueNeedUpdate()));
    myLogsWindow->exec();
}

void marketStalkerClass::showProfile()
{
    profileWindowClass* myProfileWindow = new profileWindowClass(this, &activeOption, &profileUsed);
    connect(myProfileWindow, SIGNAL(allChanged()), this, SLOT(updateAllOption()));
    myProfileWindow->exec();
}

void marketStalkerClass::updateOption(bool euroChange, bool emailIsActiveChange, bool smtpOrEmailToCoChange, bool englishChange)
{
    emit windowNameChanged(activeOption.windowName);
    if(euroChange == true)
    {
        for(int i = 0; i < listItemFound.topLevelItemCount(); ++i)
        {
            QTreeWidgetItem* tmpItem = listItemFound.topLevelItem(i);
            if(tmpItem == 0)
            {
                break;
            }
            if(activeOption.isInEuro == false)
            {
                tmpItem->setText(COLUMN_ITEM_VALUE, tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR));
            }
            else
            {
                tmpItem->setText(COLUMN_ITEM_VALUE, QString::number(tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR).toDouble() * activeOption.valueOfEuro));
            }
        }
        for(int i = 0; i < listItemList.topLevelItemCount(); ++i)
        {
            QTreeWidgetItem* tmpItem = listItemList.topLevelItem(i);
            if(tmpItem == 0)
            {
                break;
            }
            if(activeOption.isInEuro == false)
            {
                tmpItem->setText(COLUMN_ITEM_VALUE, tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR));
            }
            else
            {
                tmpItem->setText(COLUMN_ITEM_VALUE, QString::number(tmpItem->text(COLUMN_ITEM_VALUE_DOLLAR).toDouble() * activeOption.valueOfEuro));
            }
        }
        if(activeOption.isInEuro == true)
        {
            if(boxIsInDollar == true)
            {
                boxMaxValue.setValue(boxMaxValue.value() * activeOption.valueOfEuro);
                boxMinValue.setValue(boxMinValue.value() * activeOption.valueOfEuro);
                boxIsInDollar = false;
            }
        }
        else
        {
            if(boxIsInDollar == false)
            {
                boxMaxValue.setValue(boxMaxValue.value() / activeOption.valueOfEuro);
                boxMinValue.setValue(boxMinValue.value() / activeOption.valueOfEuro);
                boxIsInDollar = true;
            }
        }

        minValue = boxMinValue.value();
        maxValue = boxMaxValue.value();
    }
    if(emailIsActiveChange == true || smtpOrEmailToCoChange == true)
    {
        if(emailSender != 0)
        {
            emailSender->quit();
            delete emailSender;
            emailSender = 0;
            logsInfo.connectToSmtp = false;
            logsInfo.authToSmtp = false;
            logsInfo.sendMailSucces = false;
            //logsInfo.logs.append("Déconnexion du serveur SMTP...\n");
        }

        if(activeOption.emailInfo.isActive == true)
        {
            emailSender = new smtpClientClass(activeOption.emailInfo.smtpServ, activeOption.emailInfo.smtpPort);
            logsInfo.connectToSmtp = emailSender->connectToHost();
            //logsInfo.logs.append("Connexion au serveur SMTP...\n");
            logsInfo.authToSmtp = emailSender->login(activeOption.emailInfo.emailWith, activeOption.emailInfo.mdpWith);
            //logsInfo.logs.append("Authentification au serveur SMTP...\n");
        }

        emit logsChanged();
    }
    if(englishChange == true)
    {
        if(activeOption.isInEnglish == true)
        {
            aditionalOptions = "l=english&";
        }
        else
        {
            aditionalOptions = "l=french&";
        }
        updateValue();
    }
}

void marketStalkerClass::errorDelete(getAPageClass* thisPage)
{
    thisPage->setEndUse(true);
}


void marketStalkerClass::checkFocus(QWidget* old, QWidget* current)
{
    if(current == 0)
    {
        isOnFocus = false;
    }
    else if(old == 0)
    {
        isOnFocus = true;
        timeForWarn.stop();
    }
}

void marketStalkerClass::itsTimeToWarn()
{
    warnForValue();
}

void marketStalkerClass::updateAllOption()
{
    updateOption(true, true, true, true);
}

void marketStalkerClass::creatContextMenu(const QPoint& thisPoint)
{
    QTreeWidget* treeHasFocus = 0;
    if(listItemFound.hasFocus() == true)
    {
        treeHasFocus = &listItemFound;
    }
    else if(listItemList.hasFocus() == true)
    {
        treeHasFocus = &listItemList;
    }

    if(treeHasFocus != 0)
    {
        QTreeWidgetItem* itemSelected = treeHasFocus->itemAt(thisPoint);
        if(itemSelected != 0)
        {
            QAction* actionSelected = 0;
            QMenu contextMenu;
            QAction* actionBlackList = contextMenu.addAction("Ajouter cet objet à la blacklist");
            actionSelected = contextMenu.exec(treeHasFocus->viewport()->mapToGlobal(thisPoint));

            if(actionSelected == actionBlackList)
            {
                /*listOfItemBlacklisted.append(QSharedPointer<QTreeWidgetItem>(treeHasFocus->takeTopLevelItem(treeHasFocus->indexOfTopLevelItem(itemSelected))));
                if(treeHasFocus == &listItemFound)
                {
                    labNbItemFound.setText(QString::number(listItemFound.topLevelItemCount()));
                }
                else if(treeHasFocus == &listItemList)
                {
                    labNbItemList.setText(QString::number(listItemList.topLevelItemCount()));
                }
                labNbItemTotal.setText(QString("Total : ") + QString::number(labNbItemFound.text().toInt() + labNbItemList.text().toInt()));*/
            }
        }
    }
}
