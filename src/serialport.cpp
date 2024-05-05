#include "serialport.h"

SerialPort::SerialPort(QObject* parent) : QSerialPort(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

SerialPort::~SerialPort()
{

}

void SerialPort::toggle()
{
    if(!isOpen())
    {
        start();
    }
    else
    {
        stop();
    }
}

bool SerialPort::start()
{
    bool isOpen{false};
    isOpen = open(QIODevice::ReadWrite);
    if(isOpen)
    {
        emit portStatus(true);
    }
    return isOpen;
}

void SerialPort::stop()
{
    close();
    emit portStatus(false);
}

void SerialPort::sendData(QByteArray data)
{
    if(isOpen())
    {
        write(data);
        emit dataSent(data);
    }
}

void SerialPort::setPortNameString(QString name)
{
    setPortName(name);
}

void SerialPort::setBaudRateString(QString baud)
{
    setBaudRate(baud.toInt());
}

void SerialPort::setDataBitsString(QString data_bits)
{
    switch(data_bits.toInt())
    {
        case 5: setDataBits(QSerialPort::Data5); break;
        case 6: setDataBits(QSerialPort::Data6); break;
        case 7: setDataBits(QSerialPort::Data7); break;
        case 8: setDataBits(QSerialPort::Data8); break;
        default: setDataBits(QSerialPort::Data8); break;
    }
}

void SerialPort::setParityString(QString parity)
{
    if(parity == "None")
    {
        setParity(QSerialPort::NoParity);
    }
    else if(parity == "Even")
    {
        setParity(QSerialPort::EvenParity);
    }
    else if(parity == "Odd")
    {
        setParity(QSerialPort::OddParity);
    }
    else if(parity == "Space")
    {
        setParity(QSerialPort::SpaceParity);
    }
    else if(parity == "Mark")
    {
        setParity(QSerialPort::MarkParity);
    }
    else
    {
        setParity(QSerialPort::NoParity);
    }
}

void SerialPort::on_readyRead()
{
    emit dataRead(readAll());
}
