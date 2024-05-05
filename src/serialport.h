#ifndef SERIAL_H
#define SERIAL_H

#include "macros.h"

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr);
    ~SerialPort();

public slots:
    void toggle();
    bool start();
    void stop();
    void sendData(QByteArray data);

    void setPortNameString(QString name);
    void setBaudRateString(QString baud);
    void setDataBitsString(QString data_bits);
    void setParityString(QString parity);

private slots:
    void on_readyRead();

signals:
    void portStatus(bool status) const;
    void dataRead(QByteArray data);
    void dataSent(QByteArray data);
};

#endif // SERIAL_H
