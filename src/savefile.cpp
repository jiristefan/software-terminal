#include "savefile.h"

SaveFile::SaveFile()
{
    connect(timer_sync, SIGNAL(timeout()), this, SLOT(sync()));
}

SaveFile::~SaveFile()
{
    stop();
}

void SaveFile::toggle(bool state)
{
    if(!isOpen() && state)
    {
        start();
    }
    else
    {
        stop();
    }
}

void SaveFile::start()
{
    if(!file_name.isEmpty() && open(file_mode))
    {
        emit statusChanged(true, QFileInfo(file_name).fileName());
        timer_sync->start(INT_FILE_SYNC_TIME);
    }
    else
    {
        emit failedToStart(false);
    }
}

void SaveFile::stop()
{
    timer_sync->stop();
    close();
    emit statusChanged(false, QFileInfo(file_name).fileName());
}

void SaveFile::writeBytes(QByteArray data)
{
    if(file_type == 0) // TXT
    {
        write(data);
    }
    else if(file_type == 1) // CSV
    {
        //write(data);
    }
    else if(file_type == 2) // MAT
    {
        //QByteArray name = file_name.toLocal8Bit();
        //MATFile* pmat = matOpen(name.data(), "w");
        //mxArray* pa1 = mxCreateDoubleMatrix(3,3,mxREAL);
        //matPutVariable(pmat, "LocalDouble", pa1);
        //matClose(pmat);
        //mxDestroyArray(pa1);
        //write(data);
    }
}

void SaveFile::sync()
{
    close();
    open(QIODevice::WriteOnly | QIODevice::Append);
}

void SaveFile::setType(int type)
{
    file_type = type;
}

void SaveFile::setName(QString name)
{
    if(!isOpen())
    {
        file_name = name;
        setFileName(name);
    }
}

void SaveFile::setOverwrite(bool overwrite)
{
    file_mode = QIODevice::WriteOnly | (overwrite ? QIODevice::Truncate : QIODevice::Append);
}
