#include "shortcutedit.h"

ShortcutEdit::ShortcutEdit(QWidget* parent) : QLineEdit(parent)
{
    setReadOnly(true);
    setAlignment(Qt::AlignCenter);
    setContextMenuPolicy(Qt::PreventContextMenu);
}

int ShortcutEdit::getModifier(QKeyEvent* e)
{
    if(e->modifiers() & Qt::ControlModifier)
    {
        return Qt::ControlModifier;
    }
    else if(e->modifiers() & Qt::ShiftModifier)
    {
        return Qt::ShiftModifier;
    }
    return Qt::NoModifier;
}

void ShortcutEdit::keyPressEvent(QKeyEvent* e)
{
    int key = e->key();
    if(Qt::Key_F1 <= key && key <= Qt::Key_F12)
    {
        key_sequence = (getModifier(e) + key);
        setText(key_sequence.toString());
        emit shortcutSet(key_sequence);
    }
    else if(key != Qt::Key_Shift && key != Qt::Key_Control)
    {
        key_sequence = 0;
        setText(key_sequence.toString());
        emit shortcutSet(key_sequence);
    }
}

void ShortcutEdit::focusInEvent(QFocusEvent* e)
{
    setStyleSheet(STYLESHEET_BLUE);
    QLineEdit::focusInEvent(e);
}

void ShortcutEdit::focusOutEvent(QFocusEvent* e)
{
    setStyleSheet(STYLESHEET_DEFAULT);
    QLineEdit::focusOutEvent(e);
}
