#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "macros.h"

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QNetworkDatagram>

class TCPClient : public QTcpSocket
{
    Q_OBJECT
public:
    TCPClient(QObject* parent = nullptr);

private:
    QHostAddress address{""};
    quint16 port{0};

public slots:
    void toggle();
    void start();
    void stop();
    void sendData(QByteArray data);

    bool setAddress(QString address_string);
    bool setPort(QString port_string);

private slots:
    void on_readyRead();

signals:
    void dataRead(QByteArray data);
    void dataSent(QByteArray data);
};

#endif // TCPSOCKET_H
