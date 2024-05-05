#include "savefiledialog.h"

SaveFileDialog::SaveFileDialog(QString name, QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint)
{
    ui->setupUi(this);
    setWindowTitle(name);
    setWindowIcon(QIcon(ICON_FILE));

    ui->txt_lineEdit_file_name->setStyleSheet(STYLESHEET_GRAY);
    ui->csv_lineEdit_file_name->setStyleSheet(STYLESHEET_GRAY);
    ui->mat_lineEdit_file_name->setStyleSheet(STYLESHEET_GRAY);

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(refreshIcons()));

    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

    refreshIcons();
}

SaveFileDialog::~SaveFileDialog()
{
    delete ui;
}

void SaveFileDialog::sendSettings()
{
    emit fileType(ui->tabWidget->currentIndex());
    switch(ui->tabWidget->currentIndex())
    {
        case 0:
            emit fileName(ui->txt_lineEdit_file_name->text());
            emit fileOverwrite(ui->txt_selection_overwrite->isChecked());
            break;
        case 1:
            emit fileName(ui->csv_lineEdit_file_name->text());
            break;
        case 2:
            emit fileName(ui->mat_lineEdit_file_name->text());
            break;
    }
}

void SaveFileDialog::loadSettings(FileSettings settings, QRect geo)
{
    last_geometry = geo;
    setGeometry(last_geometry);

    txt_file_name = settings.file_name;
    ui->txt_lineEdit_file_name->setText(txt_file_name);
    ui->txt_lineEdit_file_name->setCursorPosition(ui->txt_lineEdit_file_name->text().size());

    ui->txt_selection_add->setChecked(settings.append);
    ui->txt_selection_overwrite->setChecked(!settings.append);

    sendSettings();
}

FileSettings SaveFileDialog::saveSettings()
{
    FileSettings settings;
    settings.file_name = txt_file_name;
    settings.append = ui->txt_selection_add->isChecked();
    return settings;
}

void SaveFileDialog::refreshIcons()
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        if(i == ui->tabWidget->currentIndex())
        {
            ui->tabWidget->setTabIcon(i, icon_selected);
        }
        else
        {
            ui->tabWidget->setTabIcon(i, icon_not_selected);
        }
    }
}

void SaveFileDialog::on_txt_button_select_file_clicked()
{
    txt_file_name = QFileDialog::getSaveFileName(this,
                                                 "Select file",
                                                 QDir::currentPath(),
                                                 "TXT files (*.txt)",
                                                 nullptr,
                                                 QFileDialog::DontConfirmOverwrite);

    ui->txt_lineEdit_file_name->setText(txt_file_name);
    ui->txt_lineEdit_file_name->setCursorPosition(ui->txt_lineEdit_file_name->text().size());
}

void SaveFileDialog::on_csv_button_select_file_clicked()
{
    csv_file_name = QFileDialog::getSaveFileName(this,
                                                 "Select file",
                                                 QDir::currentPath(),
                                                 "CSV files (*.csv)",
                                                 nullptr,
                                                 QFileDialog::DontConfirmOverwrite);

    ui->csv_lineEdit_file_name->setText(csv_file_name);
    ui->csv_lineEdit_file_name->setCursorPosition(ui->csv_lineEdit_file_name->text().size());
}

void SaveFileDialog::on_mat_button_select_file_clicked()
{
    mat_file_name = QFileDialog::getSaveFileName(this,
                                                 "Select file",
                                                 QDir::currentPath(),
                                                 "MAT files (*.mat)",
                                                 nullptr,
                                                 QFileDialog::DontConfirmOverwrite);

    ui->mat_lineEdit_file_name->setText(mat_file_name);
    ui->mat_lineEdit_file_name->setCursorPosition(ui->mat_lineEdit_file_name->text().size());
}

void SaveFileDialog::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    setGeometry(last_geometry);
}

void SaveFileDialog::hideEvent(QHideEvent* event)
{

    last_geometry = geometry();
    QWidget::hideEvent(event);
}
