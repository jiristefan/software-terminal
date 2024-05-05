#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include "macros.h"

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include <QHostAddress>
#include <QToolTip>

#include <QString>
#include <QFont>

class AddressWidget : public QWidget
{
    Q_OBJECT
public:
    AddressWidget(QWidget* parent = nullptr,
                  QString address = "",
                  QString port = "");
    ~AddressWidget();

    QHostAddress getAddress() const;
    quint16 getPort() const;
    QString getTextAddress() const;
    QString getTextPort() const;

private:
    QLineEdit* edit_address{new QLineEdit(this)};
    QLineEdit* edit_port{new QLineEdit(this)};
    QPushButton* button_delete{new QPushButton(this)};
    QHBoxLayout* layout_main{new QHBoxLayout()};

    QHostAddress address{""};
    quint16 port{0};

public slots:


private slots:
    bool checkAddress(QString address_string);
    bool checkPort(QString port_string);

    void onClickedDelete();

signals:
    void dataEdited(AddressWidget* a);
    void clickedDelete(AddressWidget* a);
};

#endif // ADDRESSWIDGET_H
