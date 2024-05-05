#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "macros.h"

#include <QObject>
#include <QWidget>
#include <QStatusBar>

#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>

#include <QAbstractSocket>

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    StatusBar(QWidget* parent = nullptr);
    ~StatusBar();

private:
    QPixmap icon_led_off{ICON_LED_OFF};
    QPixmap icon_led_waiting{ICON_LED_WAITING};
    QPixmap icon_led_on{ICON_LED_ON};

    const QString text_saving_off{"Not saving to file"};
    const QString text_saving_on{"Saving to file: "};
    const QString text_closed{"Closed"};
    const QString text_waiting{"Waiting"};
    const QString text_open{"Open"};

    QStackedWidget* file_status_widget{new QStackedWidget(this)};
    QStackedWidget* port_status_widget{new QStackedWidget(this)};


    QWidget* serial_file_page{new QWidget(file_status_widget)};
    QHBoxLayout* serial_file_layout{new QHBoxLayout(serial_file_page)};
    QLabel* serial_file_text{new QLabel(serial_file_page)};
    QLabel* serial_file_icon{new QLabel(serial_file_page)};

    QWidget* serial_port_page{new QWidget(port_status_widget)};
    QHBoxLayout* serial_port_layout{new QHBoxLayout(serial_port_page)};
    QLabel* serial_port_text{new QLabel(serial_port_page)};
    QLabel* serial_port_icon{new QLabel(serial_port_page)};


    QWidget* UDP_file_page{new QWidget(file_status_widget)};
    QHBoxLayout* UDP_file_layout{new QHBoxLayout(UDP_file_page)};
    QLabel* UDP_file_text{new QLabel(UDP_file_page)};
    QLabel* UDP_file_icon{new QLabel(UDP_file_page)};

    QWidget* UDP_port_page{new QWidget(port_status_widget)};
    QHBoxLayout* UDP_port_layout{new QHBoxLayout(UDP_port_page)};
    QLabel* UDP_port_text{new QLabel(UDP_port_page)};
    QLabel* UDP_port_icon{new QLabel(UDP_port_page)};


    QWidget* TCPClient_file_page{new QWidget(file_status_widget)};
    QHBoxLayout* TCPClient_file_layout{new QHBoxLayout(TCPClient_file_page)};
    QLabel* TCPClient_file_text{new QLabel(TCPClient_file_page)};
    QLabel* TCPClient_file_icon{new QLabel(TCPClient_file_page)};

    QWidget* TCPClient_port_page{new QWidget(port_status_widget)};
    QHBoxLayout* TCPClient_port_layout{new QHBoxLayout(TCPClient_port_page)};
    QLabel* TCPClient_port_text{new QLabel(TCPClient_port_page)};
    QLabel* TCPClient_port_icon{new QLabel(TCPClient_port_page)};


    QWidget* TCPServer_file_page{new QWidget(file_status_widget)};
    QHBoxLayout* TCPServer_file_layout{new QHBoxLayout(TCPServer_file_page)};
    QLabel* TCPServer_file_text{new QLabel(TCPServer_file_page)};
    QLabel* TCPServer_file_icon{new QLabel(TCPServer_file_page)};

    QWidget* TCPServer_port_page{new QWidget(port_status_widget)};
    QHBoxLayout* TCPServer_port_layout{new QHBoxLayout(TCPServer_port_page)};
    QLabel* TCPServer_port_text{new QLabel(TCPServer_port_page)};
    QLabel* TCPServer_port_icon{new QLabel(TCPServer_port_page)};

public slots:
    void setCurrentIndex(int index);
    QString formatFileName(QString file_name);

    void toggleFileSerial(bool is_running, QString file_name);
    void toggleFileUDP(bool is_running, QString file_name);
    void toggleFileTCPClient(bool is_running, QString file_name);
    void toggleFileTCPServer(bool is_running, QString file_name);

    void togglePortSerial(bool is_running);
    void togglePortUDP(bool is_running);
    void setPortTCPClient(QAbstractSocket::SocketState state);
    void togglePortTCPServer(bool is_running);
};

#endif // STATUSBAR_H
