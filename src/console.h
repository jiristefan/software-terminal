#ifndef CONSOLESTACKEDWIDGET_H
#define CONSOLESTACKEDWIDGET_H

#include "macros.h"

#include "consoletextedit.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMenu>
#include <QInputDialog>
#include <QStyle>
#include <QStyleFactory>
#include <QTimer>

struct ConsoleSettings
{
    QString separator{""};
    int mode{0};
    int time_EOL_value{0};
    bool hide_EOL_enabled{false};
    bool separate_IO{true};

    friend QDataStream & operator<<(QDataStream &out, const ConsoleSettings &object)
    {
        out << object.separator;
        out << object.mode;
        out << object.time_EOL_value;
        out << object.hide_EOL_enabled;
        out << object.separate_IO;
        return out;
    }

    friend QDataStream & operator>>(QDataStream &out, ConsoleSettings &object)
    {
        out >> object.separator;
        out >> object.mode;
        out >> object.time_EOL_value;
        out >> object.hide_EOL_enabled;
        out >> object.separate_IO;
        return out;
    }
};
Q_DECLARE_METATYPE(ConsoleSettings)

class Console : public QStackedWidget
{
    Q_OBJECT
public:
    Console(QWidget* parent = nullptr);
    ~Console();
    enum DisplayMode { Text = 0, Hexadecimal = 1, ASCII = 2};
    Q_ENUM(DisplayMode)

private:
    void setupContextMenu();

private:
    QByteArray data_buffer;

    QTimer* timer_GUI{new QTimer(this)};

    QWidget* page_1{new QWidget(this)};
    QWidget* page_2{new QWidget(this)};

    QVBoxLayout* layout_1{new QVBoxLayout(page_1)};
    QVBoxLayout* layout_2{new QVBoxLayout(page_2)};

    ConsoleTextEdit* console_IO{new ConsoleTextEdit(page_1, COLOR_SENT_DATA)};
    ConsoleTextEdit* console_I{new ConsoleTextEdit(page_2, COLOR_RECEIVED_DATA)};
    ConsoleTextEdit* console_O{new ConsoleTextEdit(page_2, COLOR_SENT_DATA)};

    QLabel* label_IO{new QLabel("Received/Sent data:", page_1)};
    QLabel* label_I{new QLabel("Received data:", page_2)};
    QLabel* label_O{new QLabel("Sent data:", page_2)};

    QMenu* context_menu{new QMenu(this)};

    QTimer* timer_eol{new QTimer(this)};

    QString separator{""};
    DisplayMode mode{DisplayMode::Text};
    int time_EOL_value{0};
    bool hide_EOL_enabled{false};
    bool separate_IO{false};

public slots:
    void dataInput(QByteArray data);
    void insertText(QByteArray data);
    void clear();

    void loadSettings(ConsoleSettings settings);
    ConsoleSettings saveSettings();

private slots:
    void addEOL();
    QByteArray formatText(QByteArray data);
    void setSeparator(QAction* action);
    void setMode(QAction* action);
    void setTimeEOL(QAction* action);
    void toggleDeleteEOL(bool state);
    void toggleIODisplay(bool state);
    void showContextMenu(QPoint pos);
    void updateGUI();

signals:
    void userInput(QByteArray data);
};

#endif // CONSOLESTACKEDWIDGET_H
