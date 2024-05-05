#include "messagedata.h"

MessageData::MessageData(QWidget* p_main_window,
                         QWidget* p_tab,
                         QVBoxLayout* p_layout,
                         QWidget* p_dialog,
                         QVBoxLayout* p_layout_copy)
{
    widget = new MessageWidget(p_main_window, p_tab, p_layout, p_dialog, p_layout_copy);

    connect(widget, SIGNAL(textEdited(QString)), this, SLOT(interpretText()));
    connect(widget, SIGNAL(toggledHex(bool)), this, SLOT(interpretText()));

    // Connect widget signals
    connect(widget, SIGNAL(toggledShow(bool)), this, SLOT(on_toggledShow()));
    connect(widget, SIGNAL(clickedSend()), this, SLOT(on_clickedSend()));
    connect(widget, SIGNAL(clickedDelete()), this, SLOT(on_clickedDelete()));
}

MessageData::~MessageData()
{
    widget->deleteLater();
}

void MessageData::interpretText()
{
    QString text{widget->getText()};

    if(widget->isHex())
    {
        if(text.size() % 2 != 0)
        {
            message_bytes = "";
            setColor(STYLESHEET_RED);
            return;
        }

        QRegularExpressionMatch match = message_regex_hex.match(text);
        if(match.hasMatch())
        {
            message_bytes = "";
            setColor(STYLESHEET_RED);
            return;
        }

        QString text_out = text;
        message_bytes.clear();
        while(text_out.size() > 1)
        {
            message_bytes.append(QChar(text_out.left(2).toUInt(nullptr, 16)));
            text_out.remove(0, 2);
        }
        setColor(STYLESHEET_DEFAULT);

    }
    else
    {
        QByteArray bytes_out;
        bytes_out.append(text);
        QRegularExpressionMatchIterator matches = message_regex.globalMatch(text);
        while(matches.hasNext())
        {
            bytes_out.replace(matches.peekNext().captured(0), QByteArray::fromHex(matches.peekNext().captured(0).remove('$').toLatin1()));
            matches.next();
        }
        message_bytes = bytes_out;
        setColor(STYLESHEET_DEFAULT);
    }
}

void MessageData::setText(QString text)
{
    widget->setText(text);
    interpretText();
}

void MessageData::setColor(QString style)
{
    widget->setColor(style);
}

QString MessageData::getText() const
{
    return widget->getText();
}

QByteArray MessageData::getMessage() const
{
    return message_bytes;
}

void MessageData::setShortcut(QString shortcut)
{
    widget->setShortcut(shortcut);
}

QString MessageData::getShortcut() const
{
    return widget->getShortcut();
}

void MessageData::setHex(bool state)
{
    widget->setHex(state);
    interpretText();
}

bool MessageData::isHex() const
{
    return widget->isHex();
}

void MessageData::setShown(bool state)
{
    widget->setShown(state);
}

bool MessageData::isShown() const
{
    return widget->isShown();
}

void MessageData::on_toggledShow()
{
    emit toggledShow(this);
}

void MessageData::on_clickedSend()
{
    emit clickedSend(message_bytes);
}

void MessageData::on_clickedDelete()
{
    emit clickedDelete(this);
}
