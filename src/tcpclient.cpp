#include "tcpclient.h"

TCPClient::TCPClient(QObject* parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void TCPClient::toggle()
{
    if(state() == QAbstractSocket::UnconnectedState)
    {
        start();
    }
    else
    {
        stop();
    }
}

void TCPClient::start()
{
    if(!address.isNull() && port != 0)
    {
        connectToHost(address, port);
        waitForConnected(3000);
    }
}

void TCPClient::stop()
{
    disconnectFromHost();
}

void TCPClient::sendData(QByteArray data)
{
    if(state() == QAbstractSocket::ConnectedState && !address.isNull() && port != 0)
    {
        write(data);
        emit dataSent(data);
    }
}

bool TCPClient::setAddress(QString address_string)
{
    bool ok{false};
    ok = address.setAddress(address_string);
    return ok;
}

bool TCPClient::setPort(QString port_string)
{
    bool ok{false};
    port = port_string.toUShort(&ok, 10);
    return ok;
}

void TCPClient::on_readyRead()
{
    if(state() == QAbstractSocket::ConnectedState)
    {
        emit dataRead(readAll());
    }
}
