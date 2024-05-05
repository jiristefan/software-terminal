#include "consoletextedit.h"

ConsoleTextEdit::ConsoleTextEdit(QWidget* parent, QColor p_color) : QTextEdit(parent)
{
    default_color = p_color;

    font.setStyleHint(QFont::Monospace);
    font.setPointSize(10);
    setFont(font);
    setTextColor(default_color);
    setContextMenuPolicy(Qt::NoContextMenu);

    connect(this, SIGNAL(cursorPositionChanged()),this, SLOT(on_cursorPositionChanged()));
}

void ConsoleTextEdit::insertText(const QByteArray& data)
{
    setPlainText(toPlainText().append(data).right(INT_MAX_CONSOLE_CHARACTERS));
}

void ConsoleTextEdit::insertColoredText(const QByteArray &data, const QColor color)
{
    setTextColor(color);
    insertText(data);
    setTextColor(default_color);
}

void ConsoleTextEdit::on_cursorPositionChanged()
{
    moveCursor(QTextCursor::End);
}

void ConsoleTextEdit::keyPressEvent(QKeyEvent* e)
{
    if((Qt::Key_Space <= e->key() && e->key() <= Qt::Key_exclamdown) || e->modifiers() == (Qt::ShiftModifier | Qt::KeypadModifier))
    {
        QTextEdit::keyPressEvent(e);
        emit userInput(e->text().toLatin1());
    }
}

