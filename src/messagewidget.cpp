#include "messagewidget.h"
#include "messagedialog.h"

MessageWidget::MessageWidget(QWidget* p_main_window,
                             QWidget* p_tab,
                             QVBoxLayout* p_layout,
                             QWidget* p_dialog,
                             QVBoxLayout* p_layout_copy)
{
    main_window = p_main_window;
    tab = p_tab;
    layout_parent = p_layout;
    dialog = static_cast<MessageDialog*>(p_dialog);
    layout_parent_copy = p_layout_copy;

    // Setup font
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(10);

    // Setup show checkbox
    layout_main->addWidget(checkBox_show);

    // Setup line edit
    lineEdit_message->setMaxLength(INT_MAX_MESSAGE_CHARACTERS);
    lineEdit_message->setMinimumHeight(22);
    lineEdit_message->setFont(font);
    lineEdit_message->setContextMenuPolicy(Qt::NoContextMenu);
    layout_main->addWidget(lineEdit_message);

    // Setup hex checkbox
    checkBox_hex->setText("HEX");
    layout_main->addWidget(checkBox_hex);

    // Setup hotkey edit
    hotkeyEdit->setMinimumSize(57, 18);
    hotkeyEdit->setMaximumSize(57, 18);
    hotkeyEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout_main->addWidget(hotkeyEdit);

    // Setup send button
    button_send->setText("Send");
    button_send->setMaximumHeight(24);
    button_send->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    layout_main->addWidget(button_send);

    // Setup delete button
    button_delete->setIcon(QIcon(ICON_DELETE));
    button_delete->setMaximumHeight(24);
    button_delete->setMaximumWidth(24);
    button_delete->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    layout_main->addWidget(button_delete);

    // Setup line edit copy
    lineEdit_message_copy->setMaxLength(INT_MAX_MESSAGE_CHARACTERS);
    lineEdit_message_copy->setMinimumHeight(22);
    lineEdit_message_copy->setFont(font);
    lineEdit_message_copy->hide();
    layout_main_copy->addWidget(lineEdit_message_copy);

    // Setup hex checkbox copy
    checkBox_hex_copy->setText("HEX");
    checkBox_hex_copy->hide();
    layout_main_copy->addWidget(checkBox_hex_copy);

    // Setup send button copy
    button_send_copy->setText("Send");
    button_send_copy->setMaximumHeight(24);
    button_send_copy->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    button_send_copy->hide();
    layout_main_copy->addWidget(button_send_copy);

    //Connect widgets together
    connect(lineEdit_message, SIGNAL(textEdited(QString)), lineEdit_message_copy, SLOT(setText(QString)));
    connect(lineEdit_message_copy, SIGNAL(textEdited(QString)), lineEdit_message, SLOT(setText(QString)));
    connect(checkBox_hex, SIGNAL(toggled(bool)), checkBox_hex_copy, SLOT(setChecked(bool)));
    connect(checkBox_hex_copy, SIGNAL(toggled(bool)), checkBox_hex, SLOT(setChecked(bool)));

    connect(checkBox_show, SIGNAL(toggled(bool)), this, SLOT(toggleWidget(bool)));
    //connect(checkBox_show, SIGNAL(toggled(bool)), this, SIGNAL(toggledShow(bool)));
    connect(lineEdit_message, SIGNAL(textEdited(QString)), this, SIGNAL(textEdited(QString)));
    connect(checkBox_hex, SIGNAL(toggled(bool)), this, SIGNAL(toggledHex(bool)));
    connect(hotkeyEdit, SIGNAL(shortcutSet(QKeySequence)), this, SLOT(setShortcut(QKeySequence)));
    connect(button_send, SIGNAL(clicked()), this, SIGNAL(clickedSend()));
    connect(button_delete, SIGNAL(clicked()), this, SIGNAL(clickedDelete()));

    connect(lineEdit_message_copy, SIGNAL(textEdited(QString)), this, SIGNAL(textEdited(QString)));
    connect(checkBox_hex_copy, SIGNAL(toggled(bool)), this, SIGNAL(toggledHex(bool)));
    connect(button_send_copy, SIGNAL(clicked()), this, SIGNAL(clickedSend()));

    // Setup parent layout
    if(layout_parent != nullptr)
    {
        layout_parent->addLayout(layout_main);
    }

    // Setup parent layout copy
    if(layout_parent_copy != nullptr)
    {
        layout_parent_copy->addLayout(layout_main_copy);
    }
}

MessageWidget::~MessageWidget()
{
    if(isShown())
    {
        dialog->decrementShownMessageCount();
    }

    lineEdit_message_copy->deleteLater();
    checkBox_hex_copy->deleteLater();
    button_send_copy->deleteLater();
    layout_main_copy->deleteLater();

    delete shortcut_tab;
    delete shortcut_dialog;

    checkBox_show->deleteLater();
    lineEdit_message->deleteLater();
    checkBox_hex->deleteLater();
    hotkeyEdit->deleteLater();
    button_send->deleteLater();
    button_delete->deleteLater();
    layout_main->deleteLater();
}

void MessageWidget::toggleWidget(bool state)
{
    if(state == true)
    {
        dialog->incrementShownMessageCount();
        lineEdit_message_copy->show();
        checkBox_hex_copy->show();
        button_send_copy->show();
    }
    else
    {
        dialog->decrementShownMessageCount();
        lineEdit_message_copy->hide();
        checkBox_hex_copy->hide();
        button_send_copy->hide();
    }
    emit toggledShow(state);
}

void MessageWidget::setColor(QString style)
{
    lineEdit_message->setStyleSheet(style);
    lineEdit_message_copy->setStyleSheet(style);
}

void MessageWidget::setText(QString text)
{
    lineEdit_message->setText(text);
    lineEdit_message_copy->setText(text);
}

QString MessageWidget::getText() const
{
    return lineEdit_message->text();
}

void MessageWidget::setShortcut(QKeySequence key_sequence)
{
    delete shortcut_tab;
    delete shortcut_dialog;

    hotkeyEdit->setText(key_sequence.toString());

    if(!key_sequence.isEmpty())
    {
        shortcut_tab = new QShortcut(key_sequence, tab, nullptr, nullptr, Qt::WidgetWithChildrenShortcut);
        connect(shortcut_tab, SIGNAL(activated()), this, SIGNAL(clickedSend()));

        shortcut_dialog = new QShortcut(key_sequence, dialog, nullptr, nullptr, Qt::WidgetWithChildrenShortcut);
        connect(shortcut_dialog, SIGNAL(activated()), this, SIGNAL(clickedSend()));
    }
    dialog->setFocus();
}

QString MessageWidget::getShortcut() const
{
    return hotkeyEdit->text();
}

void MessageWidget::setHex(bool state)
{
    checkBox_hex->setChecked(state);
    checkBox_hex_copy->setChecked(state);
}

bool MessageWidget::isHex() const
{
    return checkBox_hex->isChecked();
}

void MessageWidget::setShown(bool state)
{
    checkBox_show->setChecked(state);
}

bool MessageWidget::isShown() const
{
    return checkBox_show->isChecked();
}
