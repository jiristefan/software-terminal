#include "statusbar.h"

StatusBar::StatusBar(QWidget* parent) : QStatusBar(parent)
{

    icon_led_off = icon_led_off.scaled(15, 15,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);

    icon_led_on = icon_led_on.scaled(15, 15,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);

    icon_led_waiting = icon_led_waiting.scaled(15, 15,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);

    file_status_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    port_status_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    serial_file_layout->setContentsMargins(2, 2, 2, 2);
    serial_port_layout->setContentsMargins(2, 2, 2, 2);
    UDP_file_layout->setContentsMargins(2, 2, 2, 2);
    UDP_port_layout->setContentsMargins(2, 2, 2, 2);
    TCPClient_file_layout->setContentsMargins(2, 2, 2, 2);
    TCPClient_port_layout->setContentsMargins(2, 2, 2, 2);
    TCPServer_file_layout->setContentsMargins(2, 2, 2, 2);
    TCPServer_port_layout->setContentsMargins(2, 2, 2, 2);

    serial_file_layout->setAlignment(Qt::AlignRight);
    UDP_file_layout->setAlignment(Qt::AlignRight);
    TCPClient_file_layout->setAlignment(Qt::AlignRight);
    TCPServer_file_layout->setAlignment(Qt::AlignRight);

    serial_port_text->setMinimumWidth(38);
    serial_port_text->setAlignment(Qt::AlignHCenter);
    UDP_port_text->setMinimumWidth(38);
    UDP_port_text->setAlignment(Qt::AlignHCenter);
    TCPClient_port_text->setMinimumWidth(38);
    TCPClient_port_text->setAlignment(Qt::AlignHCenter);
    TCPServer_port_text->setMinimumWidth(38);
    TCPServer_port_text->setAlignment(Qt::AlignHCenter);

    file_status_widget->addWidget(serial_file_page);
    file_status_widget->addWidget(UDP_file_page);
    file_status_widget->addWidget(TCPClient_file_page);
    file_status_widget->addWidget(TCPServer_file_page);

    port_status_widget->addWidget(serial_port_page);
    port_status_widget->addWidget(UDP_port_page);
    port_status_widget->addWidget(TCPClient_port_page);
    port_status_widget->addWidget(TCPServer_port_page);

    serial_file_layout->addWidget(serial_file_text);
    serial_file_layout->addWidget(serial_file_icon);
    serial_port_layout->addWidget(serial_port_text);
    serial_port_layout->addWidget(serial_port_icon);

    UDP_file_layout->addWidget(UDP_file_text);
    UDP_file_layout->addWidget(UDP_file_icon);
    UDP_port_layout->addWidget(UDP_port_text);
    UDP_port_layout->addWidget(UDP_port_icon);

    TCPClient_file_layout->addWidget(TCPClient_file_text);
    TCPClient_file_layout->addWidget(TCPClient_file_icon);
    TCPClient_port_layout->addWidget(TCPClient_port_text);
    TCPClient_port_layout->addWidget(TCPClient_port_icon);

    TCPServer_file_layout->addWidget(TCPServer_file_text);
    TCPServer_file_layout->addWidget(TCPServer_file_icon);
    TCPServer_port_layout->addWidget(TCPServer_port_text);
    TCPServer_port_layout->addWidget(TCPServer_port_icon);

    // Set initial state
    serial_file_text->setText(text_saving_off);
    UDP_file_text->setText(text_saving_off);
    TCPClient_file_text->setText(text_saving_off);
    TCPServer_file_text->setText(text_saving_off);

    serial_port_text->setText(text_closed);
    UDP_port_text->setText(text_closed);
    TCPClient_port_text->setText(text_closed);
    TCPServer_port_text->setText(text_closed);

    serial_file_icon->setPixmap(icon_led_off);
    UDP_file_icon->setPixmap(icon_led_off);
    TCPClient_file_icon->setPixmap(icon_led_off);
    TCPServer_file_icon->setPixmap(icon_led_off);

    serial_port_icon->setPixmap(icon_led_off);
    UDP_port_icon->setPixmap(icon_led_off);
    TCPClient_port_icon->setPixmap(icon_led_off);
    TCPServer_port_icon->setPixmap(icon_led_off);

    // Add prepared widgets to interface
    addPermanentWidget(file_status_widget);
    addPermanentWidget(port_status_widget, 1);
}

StatusBar::~StatusBar()
{
    file_status_widget->deleteLater();
    port_status_widget->deleteLater();

    serial_file_page->deleteLater();
    serial_file_layout->deleteLater();
    serial_file_text->deleteLater();
    serial_file_icon->deleteLater();

    serial_port_page->deleteLater();
    serial_port_layout->deleteLater();
    serial_port_text->deleteLater();
    serial_port_icon->deleteLater();

    UDP_file_page->deleteLater();
    UDP_file_layout->deleteLater();
    UDP_file_text->deleteLater();
    UDP_file_icon->deleteLater();

    UDP_port_page->deleteLater();
    UDP_port_layout->deleteLater();
    UDP_port_text->deleteLater();
    UDP_port_icon->deleteLater();

    TCPClient_file_page->deleteLater();
    TCPClient_file_layout->deleteLater();
    TCPClient_file_text->deleteLater();
    TCPClient_file_icon->deleteLater();

    TCPClient_port_page->deleteLater();
    TCPClient_port_layout->deleteLater();
    TCPClient_port_text->deleteLater();
    TCPClient_port_icon->deleteLater();

    TCPServer_file_page->deleteLater();
    TCPServer_file_layout->deleteLater();
    TCPServer_file_text->deleteLater();
    TCPServer_file_icon->deleteLater();

    TCPServer_port_page->deleteLater();
    TCPServer_port_layout->deleteLater();
    TCPServer_port_text->deleteLater();
    TCPServer_port_icon->deleteLater();
}

void StatusBar::setCurrentIndex(int index)
{
    file_status_widget->setCurrentIndex(index);

    serial_file_page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    UDP_file_page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    TCPClient_file_page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    TCPServer_file_page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    switch(index)
    {
        case 0:
            serial_file_page->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            break;
        case 1:
            UDP_file_page->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            break;
        case 2:
            TCPClient_file_page->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            break;
        case 3:
            TCPServer_file_page->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            break;
    }

    file_status_widget->adjustSize();

    port_status_widget->setCurrentIndex(index);
}

QString StatusBar::formatFileName(QString file_name)
{
    // ...XXX.yyy (character maximum)
    if(file_name.size() > INT_MAX_STATUS_FILE_CHARACTERS)
    {
        file_name = "..." + file_name.right(INT_MAX_STATUS_FILE_CHARACTERS - 2);
    }
    return file_name;
}

void StatusBar::toggleFileSerial(bool is_running, QString file_name)
{
    file_name = formatFileName(file_name);
    serial_file_text->setText(is_running ? text_saving_on + file_name : text_saving_off);
    serial_file_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::toggleFileUDP(bool is_running, QString file_name)
{
    file_name = formatFileName(file_name);
    UDP_file_text->setText(is_running ? text_saving_on + file_name : text_saving_off);
    UDP_file_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::toggleFileTCPClient(bool is_running, QString file_name)
{
    file_name = formatFileName(file_name);
    TCPClient_file_text->setText(is_running ? text_saving_on + file_name : text_saving_off);
    TCPClient_file_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::toggleFileTCPServer(bool is_running, QString file_name)
{
    file_name = formatFileName(file_name);
    TCPServer_file_text->setText(is_running ? text_saving_on + file_name : text_saving_off);
    TCPServer_file_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::togglePortSerial(bool is_running)
{
    serial_port_text->setText(is_running ? text_open : text_closed);
    serial_port_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::togglePortUDP(bool is_running)
{
    UDP_port_text->setText(is_running ? text_open : text_closed);
    UDP_port_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}

void StatusBar::setPortTCPClient(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        TCPClient_port_text->setText(text_closed);
        TCPClient_port_icon->setPixmap(icon_led_off);
    }
    else if(state == QAbstractSocket::ConnectedState)
    {
        TCPClient_port_text->setText(text_open);
        TCPClient_port_icon->setPixmap(icon_led_on);
    }
    else
    {
        TCPClient_port_text->setText(text_waiting);
        TCPClient_port_icon->setPixmap(icon_led_waiting);
    }
}

void StatusBar::togglePortTCPServer(bool is_running)
{
    TCPServer_port_text->setText(is_running ? text_open : text_closed);
    TCPServer_port_icon->setPixmap(is_running ? icon_led_on : icon_led_off);
}
