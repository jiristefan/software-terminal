#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "macros.h"

#include <QObject>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QNetworkDatagram>

class UDPSocket : public QUdpSocket
{
    Q_OBJECT
public:
    UDPSocket(QObject* parent = nullptr);
    ~UDPSocket();

private:
    QHostAddress local_address{QHostAddress::Any};
    quint16 local_port{0};

    QVector<QHostAddress> address_list;
    QVector<quint16> port_list;

public slots:
    void toggle();
    bool start();
    void stop();
    void sendData(QByteArray data);

    void setAddressData(QVector<QHostAddress> a_list, QVector<quint16> p_list);
    bool setLocalPort(QString port_string);

private slots:
    void on_readyRead();

signals:
    void dataRead(QByteArray data);
    void dataSent(QByteArray data);

};

#endif // UDPSOCKET_H
