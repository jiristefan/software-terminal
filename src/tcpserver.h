#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "macros.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QNetworkDatagram>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer(QObject* parent = nullptr);
    ~TCPServer();

private:
    quint16 port{0};

    QVector<QTcpSocket*> client_list;

public slots:
    void toggle();
    void start();
    void stop();
    void sendData(QByteArray data);

    bool setPort(QString port_string);

private slots:
    void connectClient();
    void disconnectClient();
    void readData();

    void sendClientAddresses();

signals:
    void clientAddresses(QVector<QHostAddress> address_list);
    void portStatus(bool status);
    void dataSent(QByteArray data);
    void dataRead(QByteArray data);
};

#endif // TCPSERVER_H
