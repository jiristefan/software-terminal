#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "macros.h"

#include "console.h"
#include "savefile.h"
#include "messagedialog.h"
#include "savefiledialog.h"
#include "addressdialog.h"
#include "statusbar.h"

#include "serialport.h"
#include "udpsocket.h"
#include "tcpclient.h"
#include "tcpserver.h"

#include <QObject>
#include <QWidget>
#include <QMainWindow>

#include <QString>
#include <QSaveFile>
#include <QFileDialog>

#include <QSettings>
#include <QTimer>
#include <QThread>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    // Serial
    SerialPort* serial_client{nullptr};
    QThread serial_thread{nullptr};
    SaveFile* serial_file{nullptr};
    QThread serial_file_thread{nullptr};
    SaveFileDialog* serial_file_dialog{nullptr};
    MessageDialog* serial_messages{nullptr};

    // UDP
    UDPSocket* UDP_client{nullptr};
    QThread UDP_thread{nullptr};
    SaveFile* UDP_file{nullptr};
    QThread UDP_file_thread{nullptr};
    SaveFileDialog* UDP_file_dialog{nullptr};
    MessageDialog* UDP_messages{nullptr};
    AddressDialog* UDP_address_dialog{nullptr};

    // TCP Client
    TCPClient* TCP_client{nullptr};
    QThread TCP_client_thread{nullptr};
    SaveFile* TCP_client_file{nullptr};
    QThread TCP_client_file_thread{nullptr};
    SaveFileDialog* TCP_client_file_dialog{nullptr};
    MessageDialog* TCP_client_messages{nullptr};

    // TCP Server
    TCPServer* TCP_server{nullptr};
    QThread TCP_server_thread{nullptr};
    SaveFile* TCP_server_file{nullptr};
    QThread TCP_server_file_thread{nullptr};
    SaveFileDialog* TCP_server_file_dialog{nullptr};
    MessageDialog* TCP_server_messages{nullptr};

    QSettings settings{APP_ORGANIZATION, APP_NAME};

private slots:
    void setupStatusBar();
    void setupSerialPort();
    void setupUDP();
    void setupTCPClient();
    void setupTCPServer();
    void setupThreads();

    void loadSettings();
    void saveSettings();

    void updateLastShownMessageCount();
    void resizeWindowMessages();

    void refreshSerialPorts();

    void refreshTCPServerClients(QVector<QHostAddress> address_list);

    void updateSerialInterface(bool is_running = false);
    void updateUDPInterface(QAbstractSocket::SocketState state);
    void updateTCPClientInterface(QAbstractSocket::SocketState state);
    void updateTCPServerInterface(bool is_running = false);


private: // UI
    Ui::MainWindow* ui{nullptr};
    StatusBar* status_bar{nullptr};
    QPixmap icon_led_off;
    QPixmap icon_led_on;

    int last_shown_message_count{0};

private slots: // UI Slots
    void toggleSerialFile(bool checked);
    void toggleUDPFile(bool checked);
    void toggleTCPClientFile(bool checked);
    void toggleTCPServerFile(bool checked);

};

#endif // MAINWINDOW_H
