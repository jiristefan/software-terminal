#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include "macros.h"

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QDir>
#include <QFileDialog>

#include "ui_savefiledialog.h"

struct FileSettings
{
    bool append{true};
    QString file_name{""};

    friend QDataStream & operator<<(QDataStream &out, const FileSettings &object)
    {
        out << object.append;
        out << object.file_name;
        return out;
    }

    friend QDataStream & operator>>(QDataStream &out, FileSettings &object)
    {
        out >> object.append;
        out >> object.file_name;
        return out;
    }
};
Q_DECLARE_METATYPE(FileSettings)

namespace Ui { class SaveFileDialog; }

class SaveFileDialog : public QDialog
{
    Q_OBJECT
public:
    SaveFileDialog(QString name = "File Settings", QWidget *parent = nullptr);
    ~SaveFileDialog();

private:
    Ui::SaveFileDialog* ui{new Ui::SaveFileDialog()};
    const QIcon icon_selected{ICON_SELECTED};
    const QIcon icon_not_selected{ICON_NOT_SELECTED};

    QString txt_file_name;
    QString csv_file_name;
    QString mat_file_name;

    QRect last_geometry{QPoint(200, 200), QSize(0, 0)};

public slots:
    void sendSettings();

    void loadSettings(FileSettings settings, QRect geo);
    FileSettings saveSettings();

private slots:
    void refreshIcons();
    void on_txt_button_select_file_clicked();
    void on_csv_button_select_file_clicked();
    void on_mat_button_select_file_clicked();

signals:
    void fileType(int type);
    void fileName(QString name);
    void fileOverwrite(bool overwrite);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
};

#endif // FILEDIALOG_H
