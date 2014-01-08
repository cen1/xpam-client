/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab0;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *tab1;
    QTextBrowser *textBrowser;
    QWidget *tab2;
    QPushButton *pushButton_3;
    QTextBrowser *textBrowserUpdate;
    QLineEdit *betapinbox;
    QWidget *tab3;
    QLabel *label;
    QLabel *label_2;
    QLabel *statusLabel;
    QLabel *debugLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 350);
        MainWindow->setMinimumSize(QSize(500, 350));
        MainWindow->setMaximumSize(QSize(500, 350));
        QIcon icon;
        icon.addFile(QStringLiteral(":/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(500, 330));
        centralWidget->setMaximumSize(QSize(500, 350));
        centralWidget->setStyleSheet(QLatin1String("#centralWidget {\n"
"	background-color: black;\n"
"}\n"
"\n"
"#tabWidget {\n"
"	margin: 0px\n"
"}\n"
"\n"
"#tab0 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}\n"
"#tab1 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}\n"
"#tab2 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}\n"
"#tab3 {\n"
"	background-image: url(:/eb_back_small.png);\n"
"}\n"
"\n"
"QLabel {\n"
"	color: white;\n"
"}\n"
"\n"
"QCheckBox {\n"
"	color:white;\n"
"}"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 501, 331));
        tab0 = new QWidget();
        tab0->setObjectName(QStringLiteral("tab0"));
        checkBox = new QCheckBox(tab0);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(200, 220, 73, 17));
        pushButton = new QPushButton(tab0);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 160, 121, 41));
        pushButton_2 = new QPushButton(tab0);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 100, 121, 41));
        tabWidget->addTab(tab0, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        textBrowser = new QTextBrowser(tab1);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 90, 471, 221));
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        pushButton_3 = new QPushButton(tab2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 90, 111, 23));
        textBrowserUpdate = new QTextBrowser(tab2);
        textBrowserUpdate->setObjectName(QStringLiteral("textBrowserUpdate"));
        textBrowserUpdate->setGeometry(QRect(10, 120, 471, 171));
        betapinbox = new QLineEdit(tab2);
        betapinbox->setObjectName(QStringLiteral("betapinbox"));
        betapinbox->setGeometry(QRect(10, 90, 41, 20));
        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QStringLiteral("tab3"));
        label = new QLabel(tab3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 100, 181, 16));
        label->setWordWrap(true);
        label_2 = new QLabel(tab3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 160, 341, 16));
        tabWidget->addTab(tab3, QString());
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(10, 330, 391, 16));
        debugLabel = new QLabel(centralWidget);
        debugLabel->setObjectName(QStringLiteral("debugLabel"));
        debugLabel->setGeometry(QRect(420, 330, 71, 20));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Eurobattle.net Client", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Windowed", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Start without GProxy", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Start with GProxy", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab0), QApplication::translate("MainWindow", "Launcher", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "GProxy console", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Get Beta patch", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Update", 0));
        label->setText(QApplication::translate("MainWindow", "Eurobattle.net Client version 0.2.0.1", 0));
        label_2->setText(QApplication::translate("MainWindow", "We are searching for Qt/ C++ developers to further expand this client.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("MainWindow", "About", 0));
        statusLabel->setText(QString());
        debugLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
