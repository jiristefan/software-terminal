#include "console.h"

Console::Console(QWidget* parent) : QStackedWidget(parent)
{
    addWidget(page_1);
    addWidget(page_2);

    page_1->setLayout(layout_1);
    layout_1->setContentsMargins(2, 2, 2, 2);
    layout_1->setSpacing(2);

    page_2->setLayout(layout_2);
    layout_2->setContentsMargins(2, 2, 2, 2);
    layout_2->setSpacing(2);

    layout_1->addWidget(label_IO);
    layout_1->addWidget(console_IO);

    layout_2->addWidget(label_I);
    layout_2->addWidget(console_I);
    layout_2->addWidget(label_O);
    layout_2->addWidget(console_O);

    console_I->setReadOnly(true);

    setCurrentIndex(1);

    connect(console_IO, SIGNAL(userInput(QByteArray)), this, SIGNAL(userInput(QByteArray)));
    connect(console_O, SIGNAL(userInput(QByteArray)), this, SIGNAL(userInput(QByteArray)));

    connect(console_O, SIGNAL(userInput(QByteArray)), console_IO, SLOT(insertText(QByteArray)));
    connect(console_IO, SIGNAL(userInput(QByteArray)), console_O, SLOT(insertText(QByteArray)));

    timer_eol->setTimerType(Qt::PreciseTimer);
    timer_eol->setSingleShot(true);

    connect(timer_GUI, SIGNAL(timeout()), this, SLOT(updateGUI()));

    timer_GUI->start(INT_GUI_SYNC_TIME);
}

Console::~Console()
{
    timer_GUI->deleteLater();

    timer_eol->deleteLater();

    context_menu->deleteLater();

    label_IO->deleteLater();
    label_I->deleteLater();
    label_O->deleteLater();

    console_IO->deleteLater();
    console_I->deleteLater();
    console_O->deleteLater();

    layout_1->deleteLater();
    layout_2->deleteLater();

    page_1->deleteLater();
    page_2->deleteLater();
}

void Console::setupContextMenu()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    context_menu->setStyle(QStyleFactory::create("windowsvista"));


        QMenu* submenu_separator{new QMenu("Separator", context_menu)};
        QActionGroup* group_separator{new QActionGroup(submenu_separator)};
        submenu_separator->setStyle(QStyleFactory::create("windowsvista"));

            QAction* action_separator_none{new QAction("None", group_separator)};
            action_separator_none->setCheckable(true);
            action_separator_none->setData(QVariant(""));
            submenu_separator->addAction(action_separator_none);

            QAction* action_separator_space{new QAction("Space", group_separator)};
            action_separator_space->setCheckable(true);
            action_separator_space->setData(QVariant(" "));
            submenu_separator->addAction(action_separator_space);

            QAction* action_separator_comma{new QAction("Comma", group_separator)};
            action_separator_comma->setCheckable(true);
            action_separator_comma->setData(QVariant(","));
            submenu_separator->addAction(action_separator_comma);


        QMenu* submenu_mode{new QMenu("Mode", context_menu)};
        QActionGroup* group_mode = new QActionGroup(submenu_mode);
        submenu_mode->setStyle(QStyleFactory::create("windowsvista"));

            QAction* action_mode_text{new QAction("Text", group_mode)};
            action_mode_text->setCheckable(true);
            action_mode_text->setData(QVariant(DisplayMode::Text));
            submenu_mode->addAction(action_mode_text);

            QAction* action_mode_hexadecimal{new QAction("Hexadecimal", group_mode)};
            action_mode_hexadecimal->setCheckable(true);
            action_mode_hexadecimal->setData(QVariant(DisplayMode::Hexadecimal));
            submenu_mode->addAction(action_mode_hexadecimal);

            QAction* action_mode_ASCII{new QAction("ASCII names", group_mode)};
            action_mode_ASCII->setCheckable(true);
            action_mode_ASCII->setData(QVariant(DisplayMode::ASCII));
            submenu_mode->addAction(action_mode_ASCII);


        QMenu* submenu_time_EOL{new QMenu("Add timed EOL", context_menu)};
        QActionGroup* group_time = new QActionGroup(submenu_time_EOL);
        submenu_time_EOL->setStyle(QStyleFactory::create("windowsvista"));

            QAction* action_time_off{new QAction("Off", group_time)};
            action_time_off->setCheckable(true);
            action_time_off->setData(QVariant(0));
            submenu_time_EOL->addAction(action_time_off);

            QAction* action_time_custom{new QAction("- ms (Custom)", group_time)};
            action_time_custom->setCheckable(true);
            action_time_custom->setData(QVariant(-1));
            submenu_time_EOL->addAction(action_time_custom);

            QAction* action_time_10{new QAction("10 ms", group_time)};
            action_time_10->setCheckable(true);
            action_time_10->setData(QVariant(10));
            submenu_time_EOL->addAction(action_time_10);

            QAction* action_time_100{new QAction("100 ms", group_time)};
            action_time_100->setCheckable(true);
            action_time_100->setData(QVariant(100));
            submenu_time_EOL->addAction(action_time_100);

            QAction* action_time_1000{new QAction("1000 ms", group_time)};
            action_time_1000->setCheckable(true);
            action_time_1000->setData(QVariant(1000));
            submenu_time_EOL->addAction(action_time_1000);


        QAction* action_hide_EOL{new QAction("Hide received EOL", context_menu)};
        action_hide_EOL->setCheckable(true);
        action_hide_EOL->setChecked(hide_EOL_enabled);


        QAction* action_toggle_display{new QAction("Separate I/O", context_menu)};
        action_toggle_display->setCheckable(true);
        action_toggle_display->setChecked(currentIndex());


        QAction* action_clear_window{new QAction("Clear window", context_menu)};


    connect(group_separator, SIGNAL(triggered(QAction*)), this, SLOT(setSeparator(QAction*)));
    connect(group_mode, SIGNAL(triggered(QAction*)), this, SLOT(setMode(QAction*)));
    connect(group_time, SIGNAL(triggered(QAction*)), this, SLOT(setTimeEOL(QAction*)));
    connect(action_hide_EOL, SIGNAL(triggered(bool)), this, SLOT(toggleDeleteEOL(bool)));
    connect(action_toggle_display, SIGNAL(triggered(bool)), this, SLOT(toggleIODisplay(bool)));
    connect(action_clear_window, SIGNAL(triggered(bool)), this, SLOT(clear()));

    context_menu->addMenu(submenu_separator);
    context_menu->addMenu(submenu_mode);
    context_menu->addSeparator();
    context_menu->addMenu(submenu_time_EOL);
    context_menu->addAction(action_hide_EOL);
    context_menu->addSeparator();
    context_menu->addAction(action_toggle_display);
    context_menu->addAction(action_clear_window);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(timer_eol, SIGNAL(timeout()), this, SLOT(addEOL()));

    // Set separator
    if(separator == " ")
    {
        action_separator_space->setChecked(true);
    }
    else if(separator == ",")
    {
        action_separator_comma->setChecked(true);
    }
    else
    {
        action_separator_none->setChecked(true);
    }

    // Set mode
    if(mode == DisplayMode::Hexadecimal)
    {
        action_mode_hexadecimal->setChecked(true);
    }
    else if(mode == DisplayMode::ASCII)
    {
        action_mode_ASCII->setChecked(true);
    }
    else
    {
        action_mode_text->setChecked(true);
    }

    // Set timed EOL
    if(time_EOL_value == 0)
    {
        action_time_off->setChecked(true);
    }
    else if(time_EOL_value == 10)
    {
        action_time_10->setChecked(true);
    }
    else if(time_EOL_value == 100)
    {
        action_time_100->setChecked(true);
    }
    else if(time_EOL_value == 1000)
    {
        action_time_1000->setChecked(true);
    }
    else
    {
        action_time_custom->setChecked(true);
        action_time_custom->setText(QString::number(time_EOL_value) + " ms (Custom)");
    }

    //Set hide EOL
    if(hide_EOL_enabled)
    {
        action_hide_EOL->setChecked(true);
    }

    // Set separate IO
    if(separate_IO)
    {
        action_toggle_display->setChecked(true);
    }
}

void Console::dataInput(QByteArray data)
{
    data_buffer.append(data);

    if(time_EOL_value != 0 && data.size() > 0)
    {
        timer_eol->start(time_EOL_value);
    }
}

void Console::insertText(QByteArray data)
{
    data = formatText(data);
    console_O->insertText(data);
    console_IO->insertText(data);
}

void Console::clear()
{
    if(console_IO->hasFocus())
    {
        console_IO->clear();
    }
    else if(console_I->hasFocus())
    {
        console_I->clear();
        console_I->setTextColor(COLOR_RECEIVED_DATA);
    }
    else if(console_O->hasFocus())
    {
        console_O->clear();
    }
}

void Console::loadSettings(ConsoleSettings settings)
{
    mode = Console::DisplayMode(settings.mode);
    separator = settings.separator;
    time_EOL_value = settings.time_EOL_value;
    hide_EOL_enabled = settings.hide_EOL_enabled;
    separate_IO = settings.separate_IO;
    toggleIODisplay(separate_IO);
    setupContextMenu();
}

ConsoleSettings Console::saveSettings()
{
    ConsoleSettings settings;
    settings.mode = mode;
    settings.separator = separator;
    settings.time_EOL_value = time_EOL_value;
    settings.hide_EOL_enabled = hide_EOL_enabled;
    settings.separate_IO = currentIndex();
    return settings;
}

void Console::addEOL()
{
    data_buffer.append(QByteArray::fromHex("0A"));
}

QByteArray Console::formatText(QByteArray data)
{
    if(hide_EOL_enabled)
    {
        data.replace(QByteArray::fromHex("0A"), "");
    }

    QByteArray data_out;

    if(mode == DisplayMode::Text)
    {
        for(int i = 0; i < data.size(); i++)
        {
            const char byte{data.at(i)};
            if((byte >= 32 &&  byte <= 126) || byte == 10)
            {
                data_out.append(byte);
                data_out.append(separator);
            }
        }
    }
    else if(mode == DisplayMode::Hexadecimal)
    {
        data_out.append(data.toHex(separator.isEmpty() ? 0 : separator.at(0).toLatin1()));
        data_out.append(separator);
    }
    else if(mode == DisplayMode::ASCII)
    {
        for(int i = 0; i < data.size(); i++)
        {
            const char byte{data.at(i)};
            switch(byte)
            {
                case 0: data_out.append("#NUL"); break;
                case 1: data_out.append("#SOH"); break;
                case 2: data_out.append("#STX"); break;
                case 3: data_out.append("#ETX"); break;
                case 4: data_out.append("#EOT"); break;
                case 5: data_out.append("#ENQ"); break;
                case 6: data_out.append("#ACK"); break;
                case 7: data_out.append("#BEL"); break;
                case 8: data_out.append("#BS"); break;
                case 9: data_out.append("#TAB"); break;
                case 10: data_out.append("#LF"); break;
                case 11: data_out.append("#VT"); break;
                case 12: data_out.append("#FF"); break;
                case 13: data_out.append("#CR"); break;
                case 14: data_out.append("#SO"); break;
                case 15: data_out.append("#SI"); break;
                case 16: data_out.append("#DLE"); break;
                case 17: data_out.append("#DC1"); break;
                case 18: data_out.append("#DC2"); break;
                case 19: data_out.append("#DC3"); break;
                case 20: data_out.append("#DC4"); break;
                case 21: data_out.append("#NAK"); break;
                case 22: data_out.append("#SYN"); break;
                case 23: data_out.append("#ETB"); break;
                case 24: data_out.append("#CAN"); break;
                case 25: data_out.append("#EM"); break;
                case 26: data_out.append("#SUB"); break;
                case 27: data_out.append("#ESC"); break;
                case 28: data_out.append("#FS"); break;
                case 29: data_out.append("#GS"); break;
                case 30: data_out.append("#RS"); break;
                case 31: data_out.append("#US"); break;
                case 127: data_out.append("#DEL"); break;
                default: data_out.append(byte); break;
            }
            data_out.append(separator);
        }
    }

    return data_out;
}

void Console::setSeparator(QAction* action)
{
    separator = action->data().toString();
}

void Console::setMode(QAction* action)
{
    mode = action->data().value<DisplayMode>();
}

void Console::setTimeEOL(QAction* action)
{
    int time{action->data().toInt()};
    if(time == -1)
    {
        bool ok;
        int input_time = QInputDialog::getInt(this,
                                              "Time input",
                                              "Set time value",
                                              INT_DEFAULT_TIMER_VALUE,
                                              INT_MIN_TIMER_VALUE,
                                              INT_MAX_TIMER_VALUE,
                                              1, &ok);

        if(ok)
        {
            action->setText(QString::number(input_time) + " ms (Custom)");
            time_EOL_value = input_time;
        }
    }
    else
    {
        time_EOL_value = time;
    }
}

void Console::toggleDeleteEOL(bool state)
{
    hide_EOL_enabled = state;
}

void Console::toggleIODisplay(bool state)
{
    separate_IO = state;
    setCurrentIndex(state ? 1 : 0);
}

void Console::showContextMenu(QPoint pos)
{
    context_menu->popup(mapToGlobal(pos));
}

void Console::updateGUI()
{
    if(data_buffer.isEmpty())
    {
        return;
    }

    QByteArray data{formatText(data_buffer)};
    console_I->insertText(data);
    console_IO->insertColoredText(data, COLOR_RECEIVED_DATA);
    data_buffer.clear();
}
