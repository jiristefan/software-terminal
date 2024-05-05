#ifndef MESSAGEDATA_H
#define MESSAGEDATA_H

#include "macros.h"

#include "messagewidget.h"

#include <QObject>
#include <QVBoxLayout>
#include <QString>
#include <QByteArray>
#include <QRegularExpression>

class MessageData : public QObject
{
    Q_OBJECT
public:
    MessageData(QWidget* p_main_window = nullptr,
                QWidget* p_tab = nullptr,
                QVBoxLayout* p_layout = nullptr,
                QWidget* p_dialog = nullptr,
                QVBoxLayout* p_layout_copy = nullptr);
    ~MessageData();

private:
    MessageWidget* widget{nullptr};
    QByteArray message_bytes;
    const QRegularExpression message_regex{REGEX_MESSAGE};
    const QRegularExpression message_regex_hex{REGEX_MESSAGE_HEX};

public slots:
    void interpretText();

    void setText(QString text);
    void setColor(QString style);
    QString getText() const;
    QByteArray getMessage() const;
    void setShortcut(QString shortcut);
    QString getShortcut() const;

    void setHex(bool state);
    bool isHex() const;

    void setShown(bool state);
    bool isShown() const;

private slots:
    void on_toggledShow();
    void on_clickedSend();
    void on_clickedDelete();

signals:
    void toggledShow(MessageData*);
    void clickedSend(QByteArray);
    void clickedDelete(MessageData*);
};

#endif // MESSAGEDATA_H
