#include "smtpClient.hpp"

smtpClientClass::smtpClientClass(const QString& newHost, int newPort)
{
    socket = new QSslSocket(this);
    connectionTimeout = 5000;
    responseTimeout = 5000;
    sendMessageTimeout = 60000;
    host = newHost;
    port = newPort;
}

void smtpClientClass::setHost(QString &newHost)
{
    host = newHost;
}

void smtpClientClass::setPort(int newPort)
{
    port = newPort;
}

void smtpClientClass::setUser(const QString &newUser)
{
    user = newUser;
}

void smtpClientClass::setPassword(const QString &newPassword)
{
    password = newPassword;
}

bool smtpClientClass::connectToHost()
{
    socket->connectToHostEncrypted(host, port);

    if(socket->waitForConnected(connectionTimeout) == false)
    {
        return false;
    }
    if(waitForResponse() == false)
    {
        return false;
    }
    if(responseCode != 220)
    {
        return false;
    }

    if(sendAndWait("EHLO you") == false)
    {
        return false;
    }

    return true;
}

bool smtpClientClass::login()
{
    return login(user, password);
}

bool smtpClientClass::login(const QString &user, const QString &password)
{
    if(sendAndWait("AUTH PLAIN " + QByteArray().append((char) 0).append(user).append((char) 0).append(password).toBase64(), 235) == false)
    {
        return false;
    }

    return true;
}

bool smtpClientClass::sendMail(email& thisMail)
{
    QString messageToSend;
    QCryptographicHash md5(QCryptographicHash::Md5);
    QString resultHash;

    md5.addData(QByteArray().append(qrand()));
    resultHash = md5.result().toHex();

    if(sendAndWait("MAIL FROM: <" + thisMail.from + ">") == false)
    {
        return false;
    }

    if(sendAndWait("RCPT TO: <" + thisMail.to + ">") == false)
    {
        return false;
    }

    if(sendAndWait("DATA", 354) == false)
    {
        return false;
    }

    messageToSend = "From: market stalker";
    messageToSend += " <" + thisMail.from + ">\r\n";
    messageToSend += "To: you <" + thisMail.to + ">\r\n";
    messageToSend += "Subject: " + thisMail.subject + "\r\n";
    messageToSend += "Mime-Version: 1.0\r\n";
    messageToSend += "Content-Type: text/plain; charset=UTF-8\r\n";
    messageToSend += "Content-Transfer-Encoding: 8bit\r\n\r\n";
    messageToSend += thisMail.message.replace("\n", "\r\n").replace("\r\n.\r\n", "\r\n..\r\n");

    if(sendMessage(messageToSend) == false)
    {
        return false;
    }
    if(sendAndWait(".") == false)
    {
        return false;
    }

    return true;
}

void smtpClientClass::quit()
{
    sendMessage("QUIT");
}


bool smtpClientClass::sendAndWait(const QString& thisMessage, int succesCode)
{
    if(sendMessage(thisMessage) == false)
    {
        return false;
    }
    if(waitForResponse() == false)
    {
        return false;
    }
    if(responseCode != succesCode)
    {
        return false;
    }

    return true;
}

bool smtpClientClass::waitForResponse()
{
    do
    {
        if(socket->waitForReadyRead(responseTimeout) == false)
        {
            return false;
        }

        while(socket->canReadLine() == true)
        {
            responseText = socket->readLine();
            responseCode = responseText.left(3).toInt();

            if(responseCode / 100 == 4)
            {
                return false;
            }

            if(responseCode / 100 == 5)
            {
                return false;
            }

            if(responseText[3] == ' ')
            {
                return true;
            }
        }
    } while(true);

    return true;
}

bool smtpClientClass::sendMessage(const QString& text)
{
    socket->write(text.toUtf8() + "\r\n");
    if(socket->waitForBytesWritten(sendMessageTimeout) == false)
    {
        return false;
    }

    return true;
}
