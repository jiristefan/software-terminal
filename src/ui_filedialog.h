/********************************************************************************
** Form generated from reading UI file 'filedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEDIALOG_H
#define UI_FILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileDialog
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_txt;
    QGridLayout *gridLayout_2;
    QGroupBox *txt_group_file;
    QVBoxLayout *verticalLayout;
    QPushButton *txt_button_select_file;
    QLineEdit *txt_lineEdit_file_name;
    QGroupBox *txt_group_settings;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *txt_selection_add;
    QRadioButton *txt_selection_overwrite;
    QWidget *tab_csv;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *csv_button_select_file;
    QLineEdit *csv_lineEdit_file_name;
    QWidget *tab_mat;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_3;
    QPushButton *mat_button_select_file;
    QLineEdit *mat_lineEdit_file_name;

    void setupUi(QDialog *FileDialog)
    {
        if (FileDialog->objectName().isEmpty())
            FileDialog->setObjectName(QString::fromUtf8("FileDialog"));
        FileDialog->resize(198, 206);
        gridLayout = new QGridLayout(FileDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(FileDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab_txt = new QWidget();
        tab_txt->setObjectName(QString::fromUtf8("tab_txt"));
        gridLayout_2 = new QGridLayout(tab_txt);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txt_group_file = new QGroupBox(tab_txt);
        txt_group_file->setObjectName(QString::fromUtf8("txt_group_file"));
        verticalLayout = new QVBoxLayout(txt_group_file);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        txt_button_select_file = new QPushButton(txt_group_file);
        txt_button_select_file->setObjectName(QString::fromUtf8("txt_button_select_file"));

        verticalLayout->addWidget(txt_button_select_file, 0, Qt::AlignLeft);

        txt_lineEdit_file_name = new QLineEdit(txt_group_file);
        txt_lineEdit_file_name->setObjectName(QString::fromUtf8("txt_lineEdit_file_name"));
        txt_lineEdit_file_name->setEnabled(true);
        txt_lineEdit_file_name->setEchoMode(QLineEdit::Normal);
        txt_lineEdit_file_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        txt_lineEdit_file_name->setReadOnly(true);
        txt_lineEdit_file_name->setClearButtonEnabled(false);

        verticalLayout->addWidget(txt_lineEdit_file_name);


        gridLayout_2->addWidget(txt_group_file, 1, 0, 1, 1, Qt::AlignBottom);

        txt_group_settings = new QGroupBox(tab_txt);
        txt_group_settings->setObjectName(QString::fromUtf8("txt_group_settings"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txt_group_settings->sizePolicy().hasHeightForWidth());
        txt_group_settings->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(txt_group_settings);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        txt_selection_add = new QRadioButton(txt_group_settings);
        txt_selection_add->setObjectName(QString::fromUtf8("txt_selection_add"));
        txt_selection_add->setChecked(true);

        verticalLayout_4->addWidget(txt_selection_add);

        txt_selection_overwrite = new QRadioButton(txt_group_settings);
        txt_selection_overwrite->setObjectName(QString::fromUtf8("txt_selection_overwrite"));

        verticalLayout_4->addWidget(txt_selection_overwrite);


        gridLayout_2->addWidget(txt_group_settings, 0, 0, 1, 1);

        tabWidget->addTab(tab_txt, QString());
        tab_csv = new QWidget();
        tab_csv->setObjectName(QString::fromUtf8("tab_csv"));
        gridLayout_3 = new QGridLayout(tab_csv);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_4 = new QGroupBox(tab_csv);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab_csv);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        csv_button_select_file = new QPushButton(groupBox_3);
        csv_button_select_file->setObjectName(QString::fromUtf8("csv_button_select_file"));

        verticalLayout_2->addWidget(csv_button_select_file, 0, Qt::AlignLeft);

        csv_lineEdit_file_name = new QLineEdit(groupBox_3);
        csv_lineEdit_file_name->setObjectName(QString::fromUtf8("csv_lineEdit_file_name"));
        csv_lineEdit_file_name->setEnabled(true);
        csv_lineEdit_file_name->setEchoMode(QLineEdit::Normal);
        csv_lineEdit_file_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        csv_lineEdit_file_name->setReadOnly(true);
        csv_lineEdit_file_name->setClearButtonEnabled(false);

        verticalLayout_2->addWidget(csv_lineEdit_file_name);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        tabWidget->addTab(tab_csv, QString());
        tab_mat = new QWidget();
        tab_mat->setObjectName(QString::fromUtf8("tab_mat"));
        gridLayout_4 = new QGridLayout(tab_mat);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_5 = new QGroupBox(tab_mat);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(groupBox_5, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(tab_mat);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_3 = new QVBoxLayout(groupBox_6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        mat_button_select_file = new QPushButton(groupBox_6);
        mat_button_select_file->setObjectName(QString::fromUtf8("mat_button_select_file"));

        verticalLayout_3->addWidget(mat_button_select_file, 0, Qt::AlignLeft);

        mat_lineEdit_file_name = new QLineEdit(groupBox_6);
        mat_lineEdit_file_name->setObjectName(QString::fromUtf8("mat_lineEdit_file_name"));
        mat_lineEdit_file_name->setEnabled(true);
        mat_lineEdit_file_name->setEchoMode(QLineEdit::Normal);
        mat_lineEdit_file_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        mat_lineEdit_file_name->setReadOnly(true);
        mat_lineEdit_file_name->setClearButtonEnabled(false);

        verticalLayout_3->addWidget(mat_lineEdit_file_name);


        gridLayout_4->addWidget(groupBox_6, 1, 0, 1, 1);

        tabWidget->addTab(tab_mat, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(FileDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FileDialog);
    } // setupUi

    void retranslateUi(QDialog *FileDialog)
    {
        FileDialog->setWindowTitle(QCoreApplication::translate("FileDialog", "Dialog", nullptr));
        txt_group_file->setTitle(QCoreApplication::translate("FileDialog", "File name", nullptr));
        txt_button_select_file->setText(QCoreApplication::translate("FileDialog", "Select File...", nullptr));
        txt_group_settings->setTitle(QCoreApplication::translate("FileDialog", "Settings", nullptr));
        txt_selection_add->setText(QCoreApplication::translate("FileDialog", "Add to file", nullptr));
        txt_selection_overwrite->setText(QCoreApplication::translate("FileDialog", "Overwrite file", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_txt), QCoreApplication::translate("FileDialog", ".txt", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("FileDialog", "Settings", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("FileDialog", "File name", nullptr));
        csv_button_select_file->setText(QCoreApplication::translate("FileDialog", "Select File...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_csv), QCoreApplication::translate("FileDialog", ".csv", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("FileDialog", "Settings", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("FileDialog", "File name", nullptr));
        mat_button_select_file->setText(QCoreApplication::translate("FileDialog", "Select File...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_mat), QCoreApplication::translate("FileDialog", ".mat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileDialog: public Ui_FileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEDIALOG_H
