#include "options.hpp"

QDataStream& operator<<(QDataStream& thisStream, const emailInformation& thisObject)
{
    thisStream << thisObject.isActive << thisObject.emailTo << thisObject.emailWith << thisObject.mdpWith << thisObject.smtpServ << thisObject.smtpPort;

    return thisStream;
}

QDataStream& operator>>(QDataStream& thisStream, emailInformation& thisObject)
{
    thisStream >> thisObject.isActive >> thisObject.emailTo >> thisObject.emailWith >> thisObject.mdpWith >> thisObject.smtpServ >> thisObject.smtpPort;

    return thisStream;
}

QDataStream& operator<<(QDataStream& thisStream, const item& thisObject)
{
    thisStream << thisObject.gameName << thisObject.name << thisObject.value << thisObject.link;

    return thisStream;
}

QDataStream& operator>>(QDataStream& thisStream, item& thisObject)
{
    thisStream >> thisObject.gameName >> thisObject.name >> thisObject.value >> thisObject.link;

    return thisStream;
}

QDataStream& operator<<(QDataStream& thisStream, const options& thisObject)
{
    thisStream << thisObject.windowName << thisObject.itemPerPage << thisObject.valueOfEuro << thisObject.isInEuro << thisObject.isInEnglish << thisObject.alwaysBeep
               << thisObject.emailInfo << thisObject.minValue << thisObject.maxValue << thisObject.timeRefresh << thisObject.listOfItemBlacklisted;

    return thisStream;
}

QDataStream& operator>>(QDataStream& thisStream, options& thisObject)
{
    thisStream >> thisObject.windowName >> thisObject.itemPerPage >> thisObject.valueOfEuro >> thisObject.isInEuro >> thisObject.isInEnglish >> thisObject.alwaysBeep
               >> thisObject.emailInfo >> thisObject.minValue >> thisObject.maxValue >> thisObject.timeRefresh >> thisObject.listOfItemBlacklisted;

    return thisStream;
}
