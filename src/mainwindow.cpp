#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);

    setupStatusBar();
    setupSerialPort();
    setupUDP();
    setupTCPClient();
    setupTCPServer();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(resizeWindowMessages()));

    loadSettings();

    setupThreads();
}

MainWindow::~MainWindow()
{
    saveSettings();

    delete ui;
    status_bar->deleteLater();

    // Delete serial tab
    serial_thread.quit();
    serial_thread.wait();
    serial_client->deleteLater();

    serial_file_thread.quit();
    serial_file_thread.wait();
    serial_file_dialog->deleteLater();
    serial_file->deleteLater();

    serial_messages->deleteLater();

    // Delete UDP tab
    UDP_thread.quit();
    UDP_thread.wait();
    UDP_client->deleteLater();

    UDP_file_thread.quit();
    UDP_file_thread.wait();
    UDP_file_dialog->deleteLater();
    UDP_file->deleteLater();

    UDP_address_dialog->deleteLater();
    UDP_messages->deleteLater();

    // Delete TCP Client tab
    TCP_client_thread.quit();
    TCP_client_thread.wait();
    TCP_client->deleteLater();

    TCP_client_file_thread.quit();
    TCP_client_file_thread.wait();
    TCP_client_file_dialog->deleteLater();
    TCP_client_file->deleteLater();

    TCP_client_messages->deleteLater();

    // Delete TCP Server tab
    TCP_server_thread.quit();
    TCP_server_thread.wait();
    TCP_server->deleteLater();

    TCP_server_file_thread.quit();
    TCP_server_file_thread.wait();
    TCP_server_file_dialog->deleteLater();
    TCP_server_file->deleteLater();

    TCP_server_messages->deleteLater();
}

// Setup status bar UI
void MainWindow::setupStatusBar()
{
    status_bar = new StatusBar(this);
    setStatusBar(status_bar);
    status_bar->setCurrentIndex(ui->tabWidget->currentIndex());
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            status_bar, SLOT(setCurrentIndex(int)));
}


// Setup serial port UI
void MainWindow::setupSerialPort()
{
    serial_messages = new MessageDialog("Serial Messages", ui->tab_serial,
                                        this, ui->tab_serial,                     // Widget for messages
                                        ui->serial_layout_messages);

    serial_file_dialog = new SaveFileDialog("Serial File Settings", this);        // Widget for file settings

    serial_client = new SerialPort();                                             // Class handling serial communication

    serial_file = new SaveFile();                                                 // Class handling saving to file

    // Connect console and messages
    connect(serial_client, SIGNAL(dataRead(QByteArray)),
            ui->serial_console, SLOT(dataInput(QByteArray)));
    connect(ui->serial_console, SIGNAL(userInput(QByteArray)),
            serial_client, SLOT(sendData(QByteArray)));
    connect(serial_messages, SIGNAL(requestToSend(QByteArray)),
            ui->serial_console, SLOT(insertText(QByteArray)));
    connect(serial_messages, SIGNAL(requestToSend(QByteArray)),
            serial_client, SLOT(sendData(QByteArray)));

    // Connect settings
    connect(ui->serial_selection_COM, SIGNAL(currentTextChanged(QString)),
            serial_client, SLOT(setPortNameString(QString)));
    connect(ui->serial_selection_baud, SIGNAL(currentTextChanged(QString)),
            serial_client, SLOT(setBaudRateString(QString)));
    connect(ui->serial_selection_dataSize, SIGNAL(currentTextChanged(QString)),
            serial_client, SLOT(setDataBitsString(QString)));
    connect(ui->serial_selection_parity, SIGNAL(currentTextChanged(QString)),
            serial_client, SLOT(setParityString(QString)));

    // Connect file settings
    connect(ui->serial_checkBox_file, SIGNAL(clicked(bool)),
            serial_file_dialog, SLOT(sendSettings()));
    connect(serial_file_dialog, SIGNAL(fileType(int)),
            serial_file, SLOT(setType(int)));
    connect(serial_file_dialog, SIGNAL(fileName(QString)),
            serial_file, SLOT(setName(QString)));
    connect(serial_file_dialog, SIGNAL(fileOverwrite(bool)),
            serial_file, SLOT(setOverwrite(bool)));

    // Connect serial port start button
    connect(ui->serial_button_start, SIGNAL(clicked()),
            serial_client, SLOT(toggle()));
    connect(serial_client, SIGNAL(portStatus(bool)),
            this, SLOT(updateSerialInterface(bool)));

    // Connect file start checkbox
    connect(ui->serial_checkBox_file, SIGNAL(clicked(bool)),
            serial_file, SLOT(toggle(bool)));
    connect(serial_file, SIGNAL(statusChanged(bool, QString)),
            this, SLOT(toggleSerialFile(bool)));
    connect(serial_file, SIGNAL(statusChanged(bool, QString)),
            status_bar, SLOT(toggleFileSerial(bool, QString)));
    connect(serial_file, SIGNAL(failedToStart(bool)),
            ui->serial_checkBox_file, SLOT(setChecked(bool)));

    // Connect tab buttons
    connect(ui->serial_button_refresh, SIGNAL(clicked()),
            this, SLOT(refreshSerialPorts()));
    connect(ui->serial_button_files, SIGNAL(clicked()),
            serial_file_dialog, SLOT(show()));
    connect(ui->serial_button_messages, SIGNAL(clicked()),
            serial_messages, SLOT(show()));

    connect(serial_messages, SIGNAL(toggledMessage()),
            this, SLOT(resizeWindowMessages()));

    refreshSerialPorts();

    for(qint32 i_baudrate : QSerialPortInfo::standardBaudRates())
    {
        ui->serial_selection_baud->addItem(QString::number(i_baudrate));
    }

    ui->serial_selection_dataSize->addItem(QString::number(5));                   // QSerialPort::Data5
    ui->serial_selection_dataSize->addItem(QString::number(6));                   // QSerialPort::Data6
    ui->serial_selection_dataSize->addItem(QString::number(7));                   // QSerialPort::Data7
    ui->serial_selection_dataSize->addItem(QString::number(8));                   // QSerialPort::Data8

    ui->serial_selection_parity->addItem("None");                                 // QSerialPort::NoParity
    ui->serial_selection_parity->addItem("Even");                                 // QSerialPort::EvenParity
    ui->serial_selection_parity->addItem("Odd");                                  // QSerialPort::OddParity
    ui->serial_selection_parity->addItem("Space");                                // QSerialPort::SpaceParity
    ui->serial_selection_parity->addItem("Mark");                                 // QSerialPort::MarkParity
}

void MainWindow::setupUDP()
{
    UDP_messages = new MessageDialog("UDP Messages",
                                     ui->tab_UDP,
                                     this,
                                     ui->tab_UDP,
                                     ui->UDP_layout_messages);

    UDP_file_dialog = new SaveFileDialog("UDP File Settings", this);

    UDP_address_dialog = new AddressDialog("Address List", this,
                                   ui->UDP_edit_address,
                                   ui->UDP_edit_port,
                                   ui->UDP_button_addresses);

    UDP_client = new UDPSocket();

    UDP_file = new SaveFile();

    // Connect console and messages
    connect(UDP_client, SIGNAL(dataRead(QByteArray)),
            ui->UDP_console, SLOT(dataInput(QByteArray)));
    connect(ui->UDP_console, SIGNAL(userInput(QByteArray)),
            UDP_client, SLOT(sendData(QByteArray)));
    connect(UDP_messages, SIGNAL(requestToSend(QByteArray)),
            ui->UDP_console, SLOT(insertText(QByteArray)));
    connect(UDP_messages, SIGNAL(requestToSend(QByteArray)),
            UDP_client, SLOT(sendData(QByteArray)));

    // Connect settings
    connect(UDP_address_dialog, SIGNAL(addressData(QVector<QHostAddress>, QVector<quint16>)),
            UDP_client, SLOT(setAddressData(QVector<QHostAddress>, QVector<quint16>)));
    connect(ui->UDP_edit_port_local, SIGNAL(textChanged(QString)),
            UDP_client, SLOT(setLocalPort(QString)));

    // Connect file settings
    connect(ui->UDP_checkBox_file, SIGNAL(clicked(bool)),
            UDP_file_dialog, SLOT(sendSettings()));
    connect(UDP_file_dialog, SIGNAL(fileType(int)),
            UDP_file, SLOT(setType(int)));
    connect(UDP_file_dialog, SIGNAL(fileName(QString)),
            UDP_file, SLOT(setName(QString)));
    connect(UDP_file_dialog, SIGNAL(fileOverwrite(bool)),
            UDP_file, SLOT(setOverwrite(bool)));

    // Connect UDP start button
    connect(ui->UDP_button_start, SIGNAL(clicked()),
            UDP_client, SLOT(toggle()));
    connect(UDP_client, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(updateUDPInterface(QAbstractSocket::SocketState)));

    // Connect file start checkbox
    connect(ui->UDP_checkBox_file, SIGNAL(clicked(bool)),
            UDP_file, SLOT(toggle(bool)));
    connect(UDP_file, SIGNAL(statusChanged(bool, QString)),
            this, SLOT(toggleUDPFile(bool)));
    connect(UDP_file, SIGNAL(statusChanged(bool, QString)),
            status_bar, SLOT(toggleFileUDP(bool, QString)));
    connect(UDP_file, SIGNAL(failedToStart(bool)),
            ui->UDP_checkBox_file, SLOT(setChecked(bool)));

    // Connect tab buttons
    connect(ui->UDP_button_files, SIGNAL(clicked()),
            UDP_file_dialog, SLOT(show()));
    connect(ui->UDP_button_messages, SIGNAL(clicked()),
            UDP_messages, SLOT(show()));

    // Connect address dialog
    connect(ui->UDP_button_addresses, SIGNAL(clicked()),
            UDP_address_dialog, SLOT(show()));
    connect(ui->UDP_button_start, SIGNAL(clicked()),
            UDP_address_dialog, SLOT(hide()));

    connect(UDP_messages, SIGNAL(toggledMessage()),
            this, SLOT(resizeWindowMessages()));
}

void MainWindow::setupTCPClient()
{
    TCP_client_messages = new MessageDialog("TCP Client Messages",
                                            ui->tab_TCP_client,
                                            this,
                                            ui->tab_TCP_client,
                                            ui->TCP_client_layout_messages);

    TCP_client_file_dialog = new SaveFileDialog("TCP Client File Settings", this);

    TCP_client = new TCPClient();

    TCP_client_file = new SaveFile();

    // Connect console and messages
    connect(TCP_client, SIGNAL(dataRead(QByteArray)),
            ui->TCP_client_console, SLOT(dataInput(QByteArray)));
    connect(ui->TCP_client_console, SIGNAL(userInput(QByteArray)),
            TCP_client, SLOT(sendData(QByteArray)));
    connect(TCP_client_messages, SIGNAL(requestToSend(QByteArray)),
            ui->TCP_client_console, SLOT(insertText(QByteArray)));
    connect(TCP_client_messages, SIGNAL(requestToSend(QByteArray)),
            TCP_client, SLOT(sendData(QByteArray)));

    // Connect settings
    connect(ui->TCP_client_edit_address, SIGNAL(textChanged(QString)),
            TCP_client, SLOT(setAddress(QString)));
    connect(ui->TCP_client_edit_port, SIGNAL(textChanged(QString)),
            TCP_client, SLOT(setPort(QString)));

    // Connect file settings
    connect(ui->TCP_client_checkBox_file, SIGNAL(clicked(bool)),
            TCP_client_file_dialog, SLOT(sendSettings()));
    connect(TCP_client_file_dialog, SIGNAL(fileType(int)),
            TCP_client_file, SLOT(setType(int)));
    connect(TCP_client_file_dialog, SIGNAL(fileName(QString)),
            TCP_client_file, SLOT(setName(QString)));
    connect(TCP_client_file_dialog, SIGNAL(fileOverwrite(bool)),
            TCP_client_file, SLOT(setOverwrite(bool)));

    // Connect UDP start button
    connect(ui->TCP_client_button_start, SIGNAL(clicked()),
            TCP_client, SLOT(toggle()));
    connect(TCP_client, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(updateTCPClientInterface(QAbstractSocket::SocketState)));

    // Connect file start checkbox
    connect(ui->TCP_client_checkBox_file, SIGNAL(clicked(bool)),
            TCP_client_file, SLOT(toggle(bool)));
    connect(TCP_client_file, SIGNAL(statusChanged(bool, QString)),
            this, SLOT(toggleTCPClientFile(bool)));
    connect(TCP_client_file, SIGNAL(statusChanged(bool, QString)),
            status_bar, SLOT(toggleFileTCPClient(bool, QString)));
    connect(TCP_client_file, SIGNAL(failedToStart(bool)),
            ui->TCP_client_checkBox_file, SLOT(setChecked(bool)));

    // Connect tab buttons
    connect(ui->TCP_client_button_files, SIGNAL(clicked()),
            TCP_client_file_dialog, SLOT(show()));
    connect(ui->TCP_client_button_messages, SIGNAL(clicked()),
            TCP_client_messages, SLOT(show()));

    connect(TCP_client_messages, SIGNAL(toggledMessage()),
            this, SLOT(resizeWindowMessages()));
}

void MainWindow::setupTCPServer()
{
    TCP_server_messages = new MessageDialog("TCP Server Messages",
                                            ui->tab_TCP_server,
                                            this,
                                            ui->tab_TCP_server,
                                            ui->TCP_server_layout_messages);

    TCP_server_file_dialog = new SaveFileDialog("TCP Server File Settings", this);

    TCP_server = new TCPServer();

    TCP_server_file = new SaveFile();

    // Connect console and messages
    connect(TCP_server, SIGNAL(dataRead(QByteArray)),
            ui->TCP_server_console, SLOT(dataInput(QByteArray)));
    connect(ui->TCP_server_console, SIGNAL(userInput(QByteArray)),
            TCP_server, SLOT(sendData(QByteArray)));
    connect(TCP_server_messages, SIGNAL(requestToSend(QByteArray)),
            ui->TCP_server_console, SLOT(insertText(QByteArray)));
    connect(TCP_server_messages, SIGNAL(requestToSend(QByteArray)),
            TCP_server, SLOT(sendData(QByteArray)));

    // Connect settings
    connect(ui->TCP_server_edit_port, SIGNAL(textChanged(QString)),
            TCP_server, SLOT(setPort(QString)));

    // Connect file settings
    connect(ui->TCP_server_checkBox_file, SIGNAL(clicked(bool)),
            TCP_server_file_dialog, SLOT(sendSettings()));
    connect(TCP_server_file_dialog, SIGNAL(fileType(int)),
            TCP_server_file, SLOT(setType(int)));
    connect(TCP_server_file_dialog, SIGNAL(fileName(QString)),
            TCP_server_file, SLOT(setName(QString)));
    connect(TCP_server_file_dialog, SIGNAL(fileOverwrite(bool)),
            TCP_server_file, SLOT(setOverwrite(bool)));

    // Connect UDP start button
    connect(ui->TCP_server_button_start, SIGNAL(clicked()),
            TCP_server, SLOT(toggle()));
    connect(TCP_server, SIGNAL(portStatus(bool)),
            this, SLOT(updateTCPServerInterface(bool)));

    // Connect file start checkbox
    connect(ui->TCP_server_checkBox_file, SIGNAL(clicked(bool)),
            TCP_server_file, SLOT(toggle(bool)));
    connect(TCP_server_file, SIGNAL(statusChanged(bool, QString)),
            this, SLOT(toggleTCPServerFile(bool)));
    connect(TCP_server_file, SIGNAL(statusChanged(bool, QString)),
            status_bar, SLOT(toggleFileTCPServer(bool, QString)));
    connect(TCP_server_file, SIGNAL(failedToStart(bool)),
            ui->TCP_server_checkBox_file, SLOT(setChecked(bool)));

    // Connect tab buttons
    connect(ui->TCP_server_button_files, SIGNAL(clicked()),
            TCP_server_file_dialog, SLOT(show()));
    connect(ui->TCP_server_button_messages, SIGNAL(clicked()),
            TCP_server_messages, SLOT(show()));

    connect(TCP_server_messages, SIGNAL(toggledMessage()),
            this, SLOT(resizeWindowMessages()));

    connect(TCP_server, SIGNAL(clientAddresses(QVector<QHostAddress>)),
            this, SLOT(refreshTCPServerClients(QVector<QHostAddress>)));
}

void MainWindow::setupThreads()
{
    serial_client->moveToThread(&serial_thread);
    serial_file->moveToThread(&serial_file_thread);

    UDP_client->moveToThread(&UDP_thread);
    UDP_file->moveToThread(&UDP_file_thread);

    TCP_client->moveToThread(&TCP_client_thread);
    TCP_client_file->moveToThread(&TCP_client_file_thread);

    TCP_server->moveToThread(&TCP_server_thread);
    TCP_server_file->moveToThread(&TCP_server_file_thread);

    serial_file_thread.start();
    serial_thread.start();

    UDP_file_thread.start();
    UDP_thread.start();

    TCP_client_file_thread.start();
    TCP_client_thread.start();

    TCP_server_file_thread.start();
    TCP_server_thread.start();
}

void MainWindow::loadSettings()
{
    // Load main window settings
    settings.beginGroup(SETTING_MAINWINDOW);
    setGeometry(settings.value(SETTING_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    ui->tabWidget->setCurrentIndex(settings.value(SETTING_TAB, DEFAULT_MAINWINDOW_TAB).toInt());
    settings.endGroup();

    // Load serial tab settings
    settings.beginGroup(SETTING_SERIAL);
    ui->serial_selection_COM->setCurrentText(settings.value(SETTING_COM, DEFAULT_SERIAL_PORT).toString());
    ui->serial_selection_baud->setCurrentText(settings.value(SETTING_BAUD, DEFAULT_SERIAL_BAUD).toString());
    ui->serial_selection_dataSize->setCurrentText(settings.value(SETTING_DATASIZE, DEFAULT_SERIAL_DATASIZE).toString());
    ui->serial_selection_parity->setCurrentText(settings.value(SETTING_PARITY, DEFAULT_SERIAL_PARITY).toString());
    serial_messages->loadSettings(settings.value(SETTING_MESSAGE_LIST).value<QVector<MessageSettings>>(),
                                  settings.value(SETTING_MESSAGE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    serial_file_dialog->loadSettings(settings.value(SETTING_FILE).value<FileSettings>(),
                                     settings.value(SETTING_FILE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    ui->serial_console->loadSettings(settings.value(SETTING_CONSOLE).value<ConsoleSettings>());
    settings.endGroup();

    // Load UDP tab settings
    settings.beginGroup(SETTING_UDP);
    UDP_address_dialog->setMainAddress(settings.value(SETTING_ADDRESS, DEFAULT_UDP_MAIN_ADDRESS).toString());
    UDP_address_dialog->setMainPort(settings.value(SETTING_PORT, DEFAULT_UDP_MAIN_PORT).toString());
    ui->UDP_edit_port_local->setText(settings.value(SETTING_LOCAL_PORT, DEFAULT_UDP_LOCAL_PORT).toString());
    UDP_messages->loadSettings(settings.value(SETTING_MESSAGE_LIST).value<QVector<MessageSettings>>(),
                               settings.value(SETTING_MESSAGE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    UDP_file_dialog->loadSettings(settings.value(SETTING_FILE).value<FileSettings>(),
                                  settings.value(SETTING_FILE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    UDP_address_dialog->loadSettings(settings.value(SETTING_ADDRESS_LIST).value<QVector<AddressSettings>>(),
                                     settings.value(SETTING_ADDRESS_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    ui->UDP_console->loadSettings(settings.value(SETTING_CONSOLE).value<ConsoleSettings>());
    settings.endGroup();

    // Load TCP Client tab settings
    settings.beginGroup(SETTING_TCP_CLIENT);
    ui->TCP_client_edit_address->setText(settings.value(SETTING_ADDRESS, DEFAULT_TCP_CLIENT_ADDRESS).toString());
    ui->TCP_client_edit_port->setText(settings.value(SETTING_PORT, DEFAULT_TCP_CLIENT_PORT).toString());
    TCP_client_messages->loadSettings(settings.value(SETTING_MESSAGE_LIST).value<QVector<MessageSettings>>(),
                                      settings.value(SETTING_MESSAGE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    TCP_client_file_dialog->loadSettings(settings.value(SETTING_FILE).value<FileSettings>(),
                                         settings.value(SETTING_FILE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    ui->TCP_client_console->loadSettings(settings.value(SETTING_CONSOLE).value<ConsoleSettings>());
    settings.endGroup();

    // Load TCP Server tab settings
    settings.beginGroup(SETTING_TCP_SERVER);
    ui->TCP_server_edit_port->setText(settings.value(SETTING_LOCAL_PORT, DEFAULT_TCP_SERVER_PORT).toString());
    TCP_server_messages->loadSettings(settings.value(SETTING_MESSAGE_LIST).value<QVector<MessageSettings>>(),
                                      settings.value(SETTING_MESSAGE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    TCP_server_file_dialog->loadSettings(settings.value(SETTING_FILE).value<FileSettings>(),
                                         settings.value(SETTING_FILE_GEOMETRY, DEFAULT_GEOMETRY).toRect());
    ui->TCP_server_console->loadSettings(settings.value(SETTING_CONSOLE).value<ConsoleSettings>());
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    // settings.setValue(, );

    // Save main window settings
    settings.beginGroup(SETTING_MAINWINDOW);
    QRect last_geometry{geometry()};
    last_geometry.setHeight(last_geometry.height() - last_shown_message_count * MESSAGE_HEIGHT);
    settings.setValue(SETTING_GEOMETRY, last_geometry);
    settings.setValue(SETTING_TAB, ui->tabWidget->currentIndex());
    settings.endGroup();

    // Save serial tab settings
    settings.beginGroup(SETTING_SERIAL);
    settings.setValue(SETTING_COM, ui->serial_selection_COM->currentText());
    settings.setValue(SETTING_BAUD, ui->serial_selection_baud->currentText());
    settings.setValue(SETTING_DATASIZE, ui->serial_selection_dataSize->currentText());
    settings.setValue(SETTING_PARITY, ui->serial_selection_parity->currentText());
    settings.setValue(SETTING_MESSAGE_LIST, QVariant::fromValue<QVector<MessageSettings>>(serial_messages->saveSettings()));
    settings.setValue(SETTING_MESSAGE_GEOMETRY, serial_messages->geometry());
    settings.setValue(SETTING_FILE, QVariant::fromValue<FileSettings>(serial_file_dialog->saveSettings()));
    settings.setValue(SETTING_FILE_GEOMETRY, serial_file_dialog->geometry());
    settings.setValue(SETTING_CONSOLE, QVariant::fromValue<ConsoleSettings>(ui->serial_console->saveSettings()));
    settings.endGroup();

    // Save UDP tab settings
    settings.beginGroup(SETTING_UDP);
    settings.setValue(SETTING_ADDRESS, ui->UDP_edit_address->text());
    settings.setValue(SETTING_PORT, ui->UDP_edit_port->text());
    settings.setValue(SETTING_LOCAL_PORT, ui->UDP_edit_port_local->text());
    settings.setValue(SETTING_MESSAGE_LIST, QVariant::fromValue<QVector<MessageSettings>>(UDP_messages->saveSettings()));
    settings.setValue(SETTING_MESSAGE_GEOMETRY, UDP_messages->geometry());
    settings.setValue(SETTING_FILE, QVariant::fromValue<FileSettings>(UDP_file_dialog->saveSettings()));
    settings.setValue(SETTING_FILE_GEOMETRY, UDP_file_dialog->geometry());
    settings.setValue(SETTING_ADDRESS_LIST, QVariant::fromValue<QVector<AddressSettings>>(UDP_address_dialog->saveSettings()));
    settings.setValue(SETTING_ADDRESS_GEOMETRY, UDP_address_dialog->geometry());
    settings.setValue(SETTING_CONSOLE, QVariant::fromValue<ConsoleSettings>(ui->UDP_console->saveSettings()));
    settings.endGroup();

    // Save TCP Client tab settings
    settings.beginGroup(SETTING_TCP_CLIENT);
    settings.setValue(SETTING_ADDRESS, ui->TCP_client_edit_address->text());
    settings.setValue(SETTING_PORT, ui->TCP_client_edit_port->text());
    settings.setValue(SETTING_MESSAGE_LIST, QVariant::fromValue<QVector<MessageSettings>>(TCP_client_messages->saveSettings()));
    settings.setValue(SETTING_MESSAGE_GEOMETRY, TCP_client_messages->geometry());
    settings.setValue(SETTING_FILE, QVariant::fromValue<FileSettings>(TCP_client_file_dialog->saveSettings()));
    settings.setValue(SETTING_FILE_GEOMETRY, TCP_client_file_dialog->geometry());
    settings.setValue(SETTING_CONSOLE, QVariant::fromValue<ConsoleSettings>(ui->TCP_client_console->saveSettings()));
    settings.endGroup();

    // Save TCP Server tab settings
    settings.beginGroup(SETTING_TCP_SERVER);
    settings.setValue(SETTING_LOCAL_PORT, ui->TCP_server_edit_port->text());
    settings.setValue(SETTING_MESSAGE_LIST, QVariant::fromValue<QVector<MessageSettings>>(TCP_server_messages->saveSettings()));
    settings.setValue(SETTING_MESSAGE_GEOMETRY, TCP_server_messages->geometry());
    settings.setValue(SETTING_FILE, QVariant::fromValue<FileSettings>(TCP_server_file_dialog->saveSettings()));
    settings.setValue(SETTING_FILE_GEOMETRY, TCP_server_file_dialog->geometry());
    settings.setValue(SETTING_CONSOLE, QVariant::fromValue<ConsoleSettings>(ui->TCP_server_console->saveSettings()));
    settings.endGroup();

    settings.sync();
}

void MainWindow::updateLastShownMessageCount()
{
    switch(ui->tabWidget->currentIndex())
    {
        case 0:
            last_shown_message_count = serial_messages->shownMessageCount();
            break;
        case 1:
            last_shown_message_count = UDP_messages->shownMessageCount();
            break;
        case 2:
            last_shown_message_count = TCP_client_messages->shownMessageCount();
            break;
        case 3:
            last_shown_message_count = TCP_server_messages->shownMessageCount();
            break;
        default:
            last_shown_message_count = 0;
            break;
    }
}

void MainWindow::resizeWindowMessages()
{
    int last_count = last_shown_message_count;
    updateLastShownMessageCount();

    int difference{last_shown_message_count - last_count};

    if(difference > 0)
    {
        resize(width(), height() + (MESSAGE_HEIGHT * difference));
        setMinimumHeight(minimumHeight() + (MESSAGE_HEIGHT * difference));
    }
    else if(difference < 0)
    {
        setMinimumHeight(minimumHeight() + (MESSAGE_HEIGHT * difference));
        resize(width(), height() + (MESSAGE_HEIGHT * difference));
    }
}

void MainWindow::refreshSerialPorts()
{
    ui->serial_selection_COM->clear();
    for(QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {
        ui->serial_selection_COM->addItem(port.portName());
    }
    emit ui->serial_selection_COM->activated(ui->serial_selection_COM->currentText());
}

void MainWindow::refreshTCPServerClients(QVector<QHostAddress> address_list)
{
    ui->TCP_server_list_clients->clear();
    foreach(QHostAddress address, address_list)
    {
        ui->TCP_server_list_clients->addItem(QHostAddress(address.toIPv4Address()).toString());
    }
}

void MainWindow::updateSerialInterface(bool is_running)
{
    status_bar->togglePortSerial(is_running);
    ui->serial_button_start->setText(is_running ? "Stop" : "Start");
    ui->serial_button_refresh->setEnabled(!is_running);
    ui->serial_selection_COM->setEnabled(!is_running);
    ui->serial_selection_baud->setEnabled(!is_running);
    ui->serial_selection_dataSize->setEnabled(!is_running);
    ui->serial_selection_parity->setEnabled(!is_running);
}

void MainWindow::updateUDPInterface(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        status_bar->togglePortUDP(false);
        ui->UDP_button_start->setText("Start");
        ui->UDP_button_addresses->setEnabled(true);
        ui->UDP_edit_address->setEnabled(true);
        ui->UDP_edit_port->setEnabled(true);
        ui->UDP_edit_port_local->setEnabled(true);
    }
    else
    {
        status_bar->togglePortUDP(true);
        ui->UDP_button_start->setText("Stop");
        ui->UDP_button_addresses->setEnabled(false);
        ui->UDP_edit_address->setEnabled(false);
        ui->UDP_edit_port->setEnabled(false);
        ui->UDP_edit_port_local->setEnabled(false);
    }
}

void MainWindow::updateTCPClientInterface(QAbstractSocket::SocketState state)
{
    status_bar->setPortTCPClient(state);
    if(state == QAbstractSocket::UnconnectedState)
    {
        ui->TCP_client_button_start->setText("Start");
        ui->TCP_client_edit_address->setEnabled(true);
        ui->TCP_client_edit_port->setEnabled(true);
    }
    else if(state == QAbstractSocket::ConnectedState)
    {
        ui->TCP_client_button_start->setText("Stop");
        ui->TCP_client_edit_address->setEnabled(false);
        ui->TCP_client_edit_port->setEnabled(false);
    }
    else
    {
        ui->TCP_client_button_start->setText("Stop");
        ui->TCP_client_edit_address->setEnabled(false);
        ui->TCP_client_edit_port->setEnabled(false);
    }
}

void MainWindow::updateTCPServerInterface(bool is_running)
{
    status_bar->togglePortTCPServer(is_running);
    ui->TCP_server_button_start->setText(is_running ? "Stop" : "Start");
    ui->TCP_server_edit_port->setEnabled(!is_running);
}

void MainWindow::toggleSerialFile(bool checked)
{
    if(checked)
    {
        ui->serial_button_files->setEnabled(false);
        serial_file_dialog->hide();
        connect(serial_client, SIGNAL(dataRead(QByteArray)), serial_file, SLOT(writeBytes(QByteArray)));
    }
    else
    {
        ui->serial_button_files->setEnabled(true);
        disconnect(serial_client, SIGNAL(dataRead(QByteArray)), serial_file, SLOT(writeBytes(QByteArray)));
    }
}

void MainWindow::toggleUDPFile(bool checked)
{
    if(checked)
    {
        ui->UDP_button_files->setEnabled(false);
        UDP_file_dialog->hide();
        connect(UDP_client, SIGNAL(dataRead(QByteArray)), UDP_file, SLOT(writeBytes(QByteArray)));
    }
    else
    {
        ui->UDP_button_files->setEnabled(true);
        disconnect(UDP_client, SIGNAL(dataRead(QByteArray)), UDP_file, SLOT(writeBytes(QByteArray)));
    }
}

void MainWindow::toggleTCPClientFile(bool checked)
{
    if(checked)
    {
        ui->TCP_client_button_files->setEnabled(false);
        TCP_client_file_dialog->hide();
        connect(TCP_client, SIGNAL(dataRead(QByteArray)), TCP_client_file, SLOT(writeBytes(QByteArray)));
    }
    else
    {
        ui->TCP_client_button_files->setEnabled(true);
        disconnect(TCP_client, SIGNAL(dataRead(QByteArray)), TCP_client_file, SLOT(writeBytes(QByteArray)));
    }
}

void MainWindow::toggleTCPServerFile(bool checked)
{
    if(checked)
    {
        ui->TCP_server_button_files->setEnabled(false);
        TCP_server_file_dialog->hide();
        connect(TCP_server, SIGNAL(dataRead(QByteArray)), TCP_server_file, SLOT(writeBytes(QByteArray)));
    }
    else
    {
        ui->TCP_server_button_files->setEnabled(true);
        disconnect(TCP_server, SIGNAL(dataRead(QByteArray)), TCP_server_file, SLOT(writeBytes(QByteArray)));
    }
}
