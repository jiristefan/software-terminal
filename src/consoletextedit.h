#ifndef CONSOLE_H
#define CONSOLE_H

#include "macros.h"

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QScrollBar>
#include <QByteArray>
#include <QKeyEvent>
#include <QFont>
#include <QColor>
#include <QTextCharFormat>
#include <QCoreApplication>

class ConsoleTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleTextEdit(QWidget* parent = nullptr, QColor p_color = Qt::black);

private:
    QFont font{FONT_MONOSPACE};
    QColor default_color{Qt::black};

public slots:
    void insertText(const QByteArray &data);
    void insertColoredText(const QByteArray &data, const QColor color);

private slots:
    void on_cursorPositionChanged();

signals:
    void userInput(QByteArray data);

protected:
    void keyPressEvent(QKeyEvent* e) override;

};

#endif // CONSOLE_H
