#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "macros.h"

#include "messagedata.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QVector>
#include <QSaveFile>
#include <QTextStream>

#include <QDebug>

#include "ui_messagedialog.h"

struct MessageSettings
{
    bool shown{false};
    QString message{""};
    bool hex{false};
    QString shortcut{""};

    friend QDataStream & operator<<(QDataStream &out, const MessageSettings &object)
    {
        out << object.shown;
        out << object.message;
        out << object.hex;
        out << object.shortcut;
        return out;
    }

    friend QDataStream & operator>>(QDataStream &out, MessageSettings &object)
    {
        out >> object.shown;
        out >> object.message;
        out >> object.hex;
        out >> object.shortcut;
        return out;
    }
};
Q_DECLARE_METATYPE(MessageSettings)

namespace Ui { class MessageDialog; }

class MessageDialog : public QDialog
{
    Q_OBJECT
public:
    MessageDialog(QString name = "Messages",
                  QWidget* parent = nullptr,
                  QWidget* p_main_window = nullptr,
                  QWidget* p_tab = nullptr,
                  QVBoxLayout* p_layout_copy = nullptr);
    ~MessageDialog();

    int shownMessageCount() const;
    void incrementShownMessageCount();
    void decrementShownMessageCount();
    void resetShownMessageCount();

private:
    QWidget* main_window{nullptr};
    QWidget* tab{nullptr};
    QVBoxLayout* layout_messages_copy{nullptr};

    Ui::MessageDialog* ui{new Ui::MessageDialog()};
    QVector<MessageData*> message_list;

    int shown_message_count{0};

    QRect last_geometry{QPoint(200, 200), QSize(0, 0)};

public slots:
    void loadSettings(QVector<MessageSettings> settings_list, QRect geo);
    QVector<MessageSettings> saveSettings();

private slots:
    void addMessage(bool shown = false, QString text = "", bool hex = false, QString shortcut = "");
    void deleteMessage(MessageData* m);
    void on_button_add_clicked();
    void on_button_import_clicked();
    void on_button_export_clicked();
    void on_button_delete_clicked();

signals:
    void requestToSend(QByteArray);
    void addedMessage();
    void deletedMessage();
    void toggledMessage();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
};

#endif // MESSAGEDIALOG_H
