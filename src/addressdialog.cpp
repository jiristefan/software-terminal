#include "addressdialog.h"

AddressDialog::AddressDialog(QString name,
                             QWidget* parent,
                             QLineEdit* edit_address,
                             QLineEdit* edit_port,
                             QPushButton* dialog_button) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    edit_address_copy = edit_address;
    edit_port_copy = edit_port;
    dialog_button_copy = dialog_button;

    ui->setupUi(this);
    setWindowTitle(name);
    setWindowIcon(QIcon(ICON_LIST));

    connect(ui->button_add, SIGNAL(clicked()), this, SLOT(createAddress()));
    connect(ui->button_delete, SIGNAL(clicked()), this, SLOT(deleteAllAddresses()));

    connect(edit_address_copy, SIGNAL(textEdited(QString)), ui->edit_address, SLOT(setText(QString)));
    connect(ui->edit_address, SIGNAL(textEdited(QString)), edit_address_copy, SLOT(setText(QString)));
    connect(edit_port_copy, SIGNAL(textEdited(QString)), ui->edit_port, SLOT(setText(QString)));
    connect(ui->edit_port, SIGNAL(textEdited(QString)), edit_port_copy, SLOT(setText(QString)));

    connect(ui->edit_address, SIGNAL(textChanged(QString)), this, SLOT(checkMainAddress(QString)));
    connect(ui->edit_port, SIGNAL(textEdited(QString)), this, SLOT(checkMainPort(QString)));
    connect(edit_address_copy, SIGNAL(textEdited(QString)), ui->edit_address, SLOT(setText(QString)));
    connect(edit_port_copy, SIGNAL(textEdited(QString)), this, SLOT(checkMainPort(QString)));

    checkMainAddress(ui->edit_address->text());
    checkMainPort(ui->edit_port->text());
}

AddressDialog::~AddressDialog()
{
    delete ui;
}

bool AddressDialog::checkMainAddress(QString address_string)
{
    if(address_string.isEmpty())
    {
        edit_address_copy->setStyleSheet(STYLESHEET_DEFAULT);
        return true;
    }

    bool ok{false};
    ok = main_address.setAddress(address_string);
    ui->edit_address->setStyleSheet(ok ? STYLESHEET_DEFAULT : STYLESHEET_RED);
    updateAddressData();
    if(isVisible())
    {
        QToolTip::showText(mapToGlobal(ui->edit_address->pos()) - QPoint(-8, -30), main_address.toString(), ui->edit_address);
    }
    return ok;
}

bool AddressDialog::checkMainPort(QString port_string)
{
    if(port_string.isEmpty())
    {
        edit_port_copy->setStyleSheet(STYLESHEET_DEFAULT);
        return true;
    }

    bool ok{false};
    main_port = port_string.toUShort(&ok, 10);
    ui->edit_port->setStyleSheet(ok ? STYLESHEET_DEFAULT : STYLESHEET_RED);
    updateAddressData();
    return ok;
}

void AddressDialog::createAddress(QString address, QString port)
{
    AddressWidget* address_widget{new AddressWidget(this, address, port)};
    address_widget_list.append(address_widget);
    address_list.append(address_widget->getAddress());
    port_list.append(address_widget->getPort());

    connect(address_widget, SIGNAL(clickedDelete(AddressWidget*)), this, SLOT(deleteAddress(AddressWidget*)));
    connect(address_widget, SIGNAL(dataEdited(AddressWidget*)), this, SLOT(updateAddressData()));

    ui->layout_addresses->addWidget(address_widget);
    updateAddressData();
}

void AddressDialog::deleteAddress(AddressWidget* a)
{
    int index = address_widget_list.indexOf(a);
    address_widget_list.remove(index);
    address_list.remove(index);
    port_list.remove(index);
    a->deleteLater();
    updateAddressData();
}

void AddressDialog::deleteAllAddresses()
{
    foreach(AddressWidget* a, address_widget_list)
    {
        deleteAddress(a);
    }
    address_widget_list.clear();
    address_list.clear();
    port_list.clear();
    updateAddressData();
}

void AddressDialog::updateAddressData()
{
    for(int i = 0; i < address_widget_list.size(); i++)
    {
        AddressWidget* a{address_widget_list.at(i)};
        address_list.replace(i, a->getAddress());
        port_list.replace(i, a->getPort());
    }
    sendAddressData();

    dialog_button_copy->setText("Address List (" + QString::number(address_widget_list.size()) + ")");
}

void AddressDialog::sendAddressData()
{
    QVector<QHostAddress> temp_address_list;
    QVector<quint16> temp_port_list;

    temp_address_list.append(main_address);
    temp_address_list.append(address_list);
    temp_port_list.append(main_port);
    temp_port_list.append(port_list);

    emit addressData(temp_address_list, temp_port_list);
}

void AddressDialog::setMainAddress(QString address_string)
{
    ui->edit_address->setText(address_string);
    edit_address_copy->setText(address_string);
    checkMainAddress(address_string);
}

void AddressDialog::setMainPort(QString port_string)
{
    ui->edit_port->setText(port_string);
    edit_port_copy->setText(port_string);
    checkMainPort(port_string);
}

void AddressDialog::loadSettings(QVector<AddressSettings> settings, QRect geo)
{
    last_geometry = geo;
    setGeometry(last_geometry);

    foreach(AddressSettings s, settings)
    {
        createAddress(s.address, s.port);
    }

    updateAddressData();
}

QVector<AddressSettings> AddressDialog::saveSettings()
{
    QVector<AddressSettings> settings;
    foreach(AddressWidget* a, address_widget_list)
    {
        AddressSettings s;
        s.address = a->getTextAddress();
        s.port = a->getTextPort();
        settings.append(s);
    }
    return settings;
}
