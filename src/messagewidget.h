#ifndef MESSAGESPACE_H
#define MESSAGESPACE_H

#include "macros.h"

#include "shortcutedit.h"

#include <QObject>
#include <QString>
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QShortcut>

// Forward declaring class
class MessageDialog;

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    MessageWidget(QWidget* p_main_window = nullptr,
                  QWidget* p_tab = nullptr,
                  QVBoxLayout* p_layout = nullptr,
                  QWidget* p_dialog = nullptr,
                  QVBoxLayout* p_layout_copy = nullptr);
    ~MessageWidget();

private:
    QWidget* main_window{nullptr};
    QWidget* tab{nullptr};
    QVBoxLayout* layout_parent{nullptr};
    MessageDialog* dialog{nullptr};
    QVBoxLayout* layout_parent_copy{nullptr};

    QCheckBox* checkBox_show{new QCheckBox(this)};
    QLineEdit* lineEdit_message{new QLineEdit(this)};
    QCheckBox* checkBox_hex{new QCheckBox(this)};
    ShortcutEdit* hotkeyEdit{new ShortcutEdit(this)};
    QPushButton* button_send{new QPushButton(this)};
    QPushButton* button_delete{new QPushButton(this)};
    QHBoxLayout* layout_main{new QHBoxLayout()};

    QLineEdit* lineEdit_message_copy{new QLineEdit(this)};
    QCheckBox* checkBox_hex_copy{new QCheckBox(this)};
    QPushButton* button_send_copy{new QPushButton(this)};
    QHBoxLayout* layout_main_copy{new QHBoxLayout()};

    QShortcut* shortcut_tab{nullptr};
    QShortcut* shortcut_dialog{nullptr};

    QFont font{FONT_MONOSPACE};

public slots:
    void toggleWidget(bool state);

    void setColor(QString style);
    void setText(QString text);
    QString getText() const;
    void setShortcut(QKeySequence key_sequence);
    QString getShortcut() const;

    void setHex(bool state);
    bool isHex() const;

    void setShown(bool state);
    bool isShown() const;

signals:
    void toggledShow(bool);
    void textEdited(QString);
    void toggledHex(bool);
    void clickedSend();
    void clickedDelete();
};

#endif // MESSAGESPACE_H
