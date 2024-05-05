#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "macros.h"

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QTimer>

class SaveFile : public QFile
{
    Q_OBJECT
public:
    SaveFile();
    ~SaveFile();

private:
    int file_type{0};
    QString file_name{""};
    QIODevice::OpenMode file_mode{QIODevice::WriteOnly | QIODevice::Append};

    QTimer* timer_sync{new QTimer(this)};

    //MATFile* pmat;

public slots:
    void toggle(bool state);
    void start();
    void stop();
    void writeBytes(QByteArray data);
    void sync();

    void setType(int type);
    void setName(QString name);
    void setOverwrite(bool overwrite);

signals:
    void statusChanged(bool is_running, QString file_name);
    void failedToStart(bool is_running);
};

#endif // SAVEFILE_H
