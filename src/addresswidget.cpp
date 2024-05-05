#include "addresswidget.h"

AddressWidget::AddressWidget(QWidget* parent,
                             QString address,
                             QString port) :
    QWidget(parent)
{
    setLayout(layout_main);

    layout_main->setContentsMargins(0, 0, 0, 0);

    edit_address->setMinimumHeight(22);
    edit_address->setAlignment(Qt::AlignCenter);
    edit_address->setContextMenuPolicy(Qt::NoContextMenu);

    edit_port->setMinimumHeight(22);
    edit_port->setMaximumWidth(50);
    edit_port->setAlignment(Qt::AlignCenter);
    edit_port->setContextMenuPolicy(Qt::NoContextMenu);

    button_delete->setIcon(QIcon(ICON_DELETE));
    button_delete->setMaximumHeight(24);
    button_delete->setMaximumWidth(24);
    button_delete->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    layout_main->addWidget(edit_address);
    layout_main->addWidget(edit_port);
    layout_main->addWidget(button_delete);

    connect(edit_address, SIGNAL(textEdited(QString)), this, SLOT(checkAddress(QString)));
    connect(edit_port, SIGNAL(textEdited(QString)), this, SLOT(checkPort(QString)));

    connect(button_delete, SIGNAL(clicked()), this, SLOT(onClickedDelete()));

    edit_address->setText(address);
    edit_port->setText(port);

    checkAddress(edit_address->text());
    checkPort(edit_port->text());
}

AddressWidget::~AddressWidget()
{
    edit_address->deleteLater();
    edit_port->deleteLater();
    button_delete->deleteLater();
}

QHostAddress AddressWidget::getAddress() const
{
    return address;
}

quint16 AddressWidget::getPort() const
{
    return port;
}

QString AddressWidget::getTextAddress() const
{
    return edit_address->text();
}

QString AddressWidget::getTextPort() const
{
    return edit_port->text();
}

bool AddressWidget::checkAddress(QString address_string)
{
    if(address_string.isEmpty())
    {
        edit_address->setStyleSheet(STYLESHEET_DEFAULT);
        return true;
    }

    bool ok{false};
    ok = address.setAddress(address_string);
    edit_address->setStyleSheet(ok ? STYLESHEET_DEFAULT : STYLESHEET_RED);
    emit dataEdited(this);
    QToolTip::showText(mapToGlobal(edit_address->pos() - QPoint(0, -5)), address.toString(), edit_address);
    return ok;
}

bool AddressWidget::checkPort(QString port_string)
{
    if(port_string.isEmpty())
    {
        edit_port->setStyleSheet(STYLESHEET_DEFAULT);
        return true;
    }

    bool ok{false};
    port = port_string.toUShort(&ok, 10);
    edit_port->setStyleSheet(ok ? STYLESHEET_DEFAULT : STYLESHEET_RED);
    emit dataEdited(this);
    return ok;
}

void AddressWidget::onClickedDelete()
{
    emit clickedDelete(this);
}
