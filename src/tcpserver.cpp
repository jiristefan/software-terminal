#include "tcpserver.h"

TCPServer::TCPServer(QObject* parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(connectClient()));
}

TCPServer::~TCPServer()
{
    stop();
}

void TCPServer::toggle()
{
    if(!isListening())
    {
        start();
    }
    else
    {
        stop();
    }
}

void TCPServer::start()
{
    if(port != 0)
    {
        bool ok{false};
        ok = listen(QHostAddress::Any, port);
        emit portStatus(ok);
    }
}

void TCPServer::stop()
{
    close();
    foreach(QTcpSocket* client, client_list)
    {
        client->disconnectFromHost();
        client->deleteLater();
    }
    client_list.clear();
    emit portStatus(false);
    sendClientAddresses();
}

void TCPServer::sendData(QByteArray data)
{
    if(isListening() && port != 0)
    {
        foreach(QTcpSocket* client, client_list)
        {
            client->write(data);
            client->flush();
        }
        emit dataSent(data);
    }
}

bool TCPServer::setPort(QString port_string)
{
    bool ok{false};
    port = port_string.toUShort(&ok, 10);
    return ok;
}

void TCPServer::connectClient()
{
    if(hasPendingConnections())
    {
        QTcpSocket* client = nextPendingConnection();
        client_list.append(client);

        connect(client, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(client, SIGNAL(disconnected()), this, SLOT(disconnectClient()));
    }
    sendClientAddresses();
}

void TCPServer::disconnectClient()
{
    QTcpSocket* client = static_cast<QTcpSocket*>(sender());
    if(client != nullptr)
    {
        client_list.removeAll(client);
        client->deleteLater();
    }
    sendClientAddresses();
}

void TCPServer::readData()
{
    QTcpSocket* client = static_cast<QTcpSocket*>(sender());
    if(client != nullptr)
    {
        emit dataRead(client->readAll());
    }
}

void TCPServer::sendClientAddresses()
{
    QVector<QHostAddress> address_list;
    foreach(QTcpSocket* client, client_list)
    {
        address_list.append(client->peerAddress());
    }
    emit clientAddresses(address_list);
}
