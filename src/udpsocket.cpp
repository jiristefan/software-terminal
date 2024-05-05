#include "udpsocket.h"

UDPSocket::UDPSocket(QObject *parent) : QUdpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

UDPSocket::~UDPSocket()
{

}

void UDPSocket::toggle()
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

bool UDPSocket::start()
{
    bool isOpen{false};
    isOpen = bind(local_address, local_port);
    return isOpen;
}

void UDPSocket::stop()
{
    close();
}

void UDPSocket::sendData(QByteArray data)
{
    if(state() == QAbstractSocket::BoundState)
    {
        for(int i = 0; i < address_list.size(); i++)
        {
            if(!address_list.at(i).isNull() && port_list.at(i) != 0)
            {
                writeDatagram(data.data(), data.size(), address_list.at(i), port_list.at(i));
            }
        }
        emit dataSent(data);
    }
}

void UDPSocket::setAddressData(QVector<QHostAddress> a_list, QVector<quint16> p_list)
{
    address_list.clear();
    port_list.clear();

    address_list.append(a_list);
    port_list.append(p_list);
}

bool UDPSocket::setLocalPort(QString port_string)
{
    bool ok{false};
    local_port = port_string.toUShort(&ok, 10);
    return ok;
}

void UDPSocket::on_readyRead()
{
    if(state() == QAbstractSocket::BoundState)
    {
        QNetworkDatagram datagram = receiveDatagram();
        emit dataRead(datagram.data());
    }
}
