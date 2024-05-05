#include "messagedialog.h"

/*QDebug operator<<(QDebug debug, const MessageSettings &object)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "(" << object.shown << ", ";
    debug.nospace() << object.message << ", ";
    debug.nospace() << object.hex << ", ";
    debug.nospace() << object.shortcut << ")";
    return debug;
}*/

MessageDialog::MessageDialog(QString name,
                             QWidget* parent,
                             QWidget* p_main_window,
                             QWidget* p_tab,
                             QVBoxLayout* p_layout_copy)
                             : QDialog(parent, Qt::WindowCloseButtonHint)
{
    main_window = p_main_window;
    tab = p_tab;
    layout_messages_copy = p_layout_copy;

    ui->setupUi(this);
    setWindowTitle(name);
    setWindowIcon(QIcon(ICON_MESSAGE));
}

MessageDialog::~MessageDialog()
{
    delete ui;
    foreach(MessageData* m, message_list)
    {
        delete m;
    }
}

int MessageDialog::shownMessageCount() const
{
    return shown_message_count;
}

void MessageDialog::incrementShownMessageCount()
{
    shown_message_count++;
}

void MessageDialog::decrementShownMessageCount()
{
    shown_message_count--;
}

void MessageDialog::resetShownMessageCount()
{
    shown_message_count = 0;
}

void MessageDialog::loadSettings(QVector<MessageSettings> settings_list, QRect geo)
{
    last_geometry = geo;
    setGeometry(last_geometry);
    foreach(MessageSettings s, settings_list)
    {
        addMessage(s.shown, s.message, s.hex, s.shortcut);
    }
}

QVector<MessageSettings> MessageDialog::saveSettings()
{
    QVector<MessageSettings> settings_list;
    foreach(MessageData* m, message_list)
    {
        MessageSettings s;
        s.shown = m->isShown();
        s.message = m->getText();
        s.hex = m->isHex();
        s.shortcut = m->getShortcut();
        settings_list.append(s);
    }
    return settings_list;
}

void MessageDialog::addMessage(bool shown, QString text, bool hex, QString shortcut)
{
    MessageData* message = new MessageData(main_window, tab, ui->layout_messages, this, layout_messages_copy);
    message_list.append(message);

    connect(message, SIGNAL(clickedDelete(MessageData*)), this, SLOT(deleteMessage(MessageData*)));
    connect(message, SIGNAL(clickedSend(QByteArray)), this, SIGNAL(requestToSend(QByteArray)));
    connect(message, SIGNAL(toggledShow(MessageData*)), this, SIGNAL(toggledMessage()));

    // Check if shortcut already exists
    bool ok{true};
    foreach(MessageData* m, message_list)
    {
        if(m->getShortcut() == shortcut)
        {
            ok = false;
            break;
        }
    }
    if(ok)
    {
        message->setShortcut(shortcut);
    }
    message->setHex(hex);
    message->setText(text);
    message->setShown(shown);
}

void MessageDialog::deleteMessage(MessageData* m)
{
    message_list.removeAll(m);
    delete m;
}

void MessageDialog::on_button_add_clicked()
{
    addMessage();
}

void MessageDialog::on_button_import_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Select file"),
                                                     QDir::currentPath(),
                                                     "TXT files (*.txt)");

    if(file_name.isEmpty())
    {
        return;
    }

    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parameters = line.split(",");
            if(parameters.size() == 3)
            {
                bool shown = parameters.at(0) == "Y" ? true : false;
                bool hex = parameters.at(1) == "Y" ? true : false;
                QString shortcut = parameters.at(2);
                if(!in.atEnd())
                {
                    QString line = in.readLine();
                    addMessage(shown, line, hex, shortcut);
                }
                else
                {
                    addMessage(shown, "", hex, shortcut);
                }
            }
            else
            {
                break;
            }
        }
        file.close();
    }
}

void MessageDialog::on_button_export_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Select file"),
                                                     QDir::currentPath(),
                                                     "TXT files (*.txt)");

    if(file_name.isEmpty())
    {
        return;
    }

    QSaveFile file(file_name);
    if(file.open(QIODevice::WriteOnly))
    {
        foreach(MessageData* m, message_list)
        {
            file.write(m->isShown() ? "Y," : "N,");
            file.write(m->isHex() ? "Y," : "N,");
            file.write(m->getShortcut().toUtf8());
            file.write("\n");
            file.write(m->getText().toUtf8());
            file.write("\n");
        }
        file.commit();
    }
}

void MessageDialog::on_button_delete_clicked()
{
    foreach(MessageData* m, message_list)
    {
        deleteMessage(m);
    }
}

void MessageDialog::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if(!event->spontaneous())
    {
        setGeometry(last_geometry);
    }
}

void MessageDialog::hideEvent(QHideEvent* event)
{
    if(!event->spontaneous())
    {
        last_geometry = geometry();
    }
    QWidget::hideEvent(event);
}
