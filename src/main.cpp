#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

#include <QTextBlock>
#include <QTextCursor>

Q_DECLARE_METATYPE(QVector<QHostAddress>)
Q_DECLARE_METATYPE(QVector<quint16>)
Q_DECLARE_METATYPE(QVector<MessageSettings>)
Q_DECLARE_METATYPE(QVector<AddressSettings>)

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<QHostAddress>>();
    qRegisterMetaType<QVector<quint16>>();
    qRegisterMetaType<QAbstractSocket::SocketState>();
    qRegisterMetaType<MessageSettings>();
    qRegisterMetaType<QVector<MessageSettings>>();
    qRegisterMetaType<FileSettings>();
    qRegisterMetaType<AddressSettings>();
    qRegisterMetaType<QVector<AddressSettings>>();
    qRegisterMetaType<ConsoleSettings>();

    qRegisterMetaTypeStreamOperators<MessageSettings>("MessageSettings");
    qRegisterMetaTypeStreamOperators<QVector<MessageSettings>>("QVector<MessageSettings>");
    qRegisterMetaTypeStreamOperators<FileSettings>("FileSettings");
    qRegisterMetaTypeStreamOperators<AddressSettings>("AddressSettings");
    qRegisterMetaTypeStreamOperators<QVector<AddressSettings>>("QVector<AddressSettings>");
    qRegisterMetaTypeStreamOperators<ConsoleSettings>("ConsoleSettings");

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Windows"));

    MainWindow w;
    w.show();

    return a.exec();
}
