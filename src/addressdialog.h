#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include "macros.h"

#include "addresswidget.h"

#include <QDialog>
#include <QLineEdit>

#include "ui_addressdialog.h"

struct AddressSettings
{
    QString address{""};
    QString port{""};

    friend QDataStream & operator<<(QDataStream &out, const AddressSettings &object)
    {
        out << object.address;
        out << object.port;
        return out;
    }

    friend QDataStream & operator>>(QDataStream &out, AddressSettings &object)
    {
        out >> object.address;
        out >> object.port;
        return out;
    }
};
Q_DECLARE_METATYPE(AddressSettings)

namespace Ui { class AddressDialog; }

class AddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressDialog(QString name = "Address List",
                           QWidget* parent = nullptr,
                           QLineEdit* edit_address = nullptr,
                           QLineEdit* edit_port = nullptr,
                           QPushButton* dialog_button = nullptr);
    ~AddressDialog();

private:
    Ui::AddressDialog* ui{new Ui::AddressDialog()};
    QLineEdit* edit_address_copy{nullptr};
    QLineEdit* edit_port_copy{nullptr};
    QPushButton* dialog_button_copy{nullptr};

    QVector<AddressWidget*> address_widget_list;
    QVector<QHostAddress> address_list;
    QVector<quint16> port_list;
    QHostAddress main_address{""};
    quint16 main_port{0};

    QRect last_geometry{QPoint(200, 200), QSize(0, 0)};

public slots:
    void updateAddressData();
    void sendAddressData();

    void setMainAddress(QString address_string);
    void setMainPort(QString port_string);

    void loadSettings(QVector<AddressSettings> settings, QRect geo);
    QVector<AddressSettings> saveSettings();

private slots:
    bool checkMainAddress(QString address_string);
    bool checkMainPort(QString port_string);
    void createAddress(QString address = "", QString port = "");
    void deleteAddress(AddressWidget* a);
    void deleteAllAddresses();

signals:
    void addressData(QVector<QHostAddress> a_list, QVector<quint16> p_list);
};

#endif // ADDRESSDIALOG_H
