#ifndef MARKETSTALKER_HPP
#define MARKETSTLAKER_HPP

#include <QtGui>
#include <QtCore>

#include "getAPage.hpp"
#include "settingWindow.hpp"
#include "logsWindow.hpp"
#include "smtpClient.hpp"

struct item
{
    QString name;
    QString value;
    QString link;
};

class marketStalkerClass : public QWidget
{
    Q_OBJECT
public:
    marketStalkerClass(QWidget* parent = 0);
    ~marketStalkerClass();
    void setNewItem(QString fromThisSource, bool isFirstPass = false);
    void parseString(const QString& thisString, const std::string& thisRegExp, QStringList &toThisStringList);
    QString removeUnicodeFromString(QString thisString);
    void warnForValue();
    const QString& getWindowName();
public slots:
    void checkPageEndUse();
    void updateValue();
    void startGetPage();
    void beginAllGet();
    void thisGetEnd(getAPageClass* thisPage);
    void goToUrl(QTreeWidgetItem* thisItem);
    void showOption();
    void showLogs();
    void showProfile();
    void updateOption(bool euroChange, bool emailIsActiveChange, bool smtpOrEmailToCoChange, bool englishChange);
    void errorDelete(getAPageClass *thisPage);
    void checkFocus(QWidget* old, QWidget* current);
    void itsTimeToWarn();
    void updateAllOption();
    void creatContextMenu(const QPoint& thisPoint);
signals:
    void windowNameChanged(QString newName);
    void logsChanged();
private:
    QDoubleSpinBox boxMinValue;
    QDoubleSpinBox boxMaxValue;
    QSpinBox boxTimeRefresh;
    QLineEdit lineStringSearch;
    QStandardItemModel modelItemFound;
    QStandardItemModel modelItemList;
    QTreeWidget listItemFound;
    QTreeWidget listItemList;
    double minValue;
    double maxValue;
    bool boxIsInDollar;
    int timeRefresh;
    QString stringSearch;
    QTimer timerForGetPage;
    getAPageClass firstPageGet;
    QList< QSharedPointer<getAPageClass> > listOfPageGet;
    QLabel labStatuOfUpdate;
    QLabel labNbItemFound;
    QLabel labNbItemList;
    QLabel labNbItemTotal;
    options activeOption;
    bool updateTime;
    bool inGetPage;
    bool isOnFocus;
    QTimer timeForWarn;
    smtpClientClass* emailSender;
    logsInformation logsInfo;
    QList<item> listOfItemInRange;
    QString aditionalOptions;
    QString profileUsed;
    QList< QSharedPointer<QTreeWidgetItem> > listOfItemBlacklisted;
};

#endif
