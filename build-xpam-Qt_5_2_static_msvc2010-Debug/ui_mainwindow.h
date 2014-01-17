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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayoutMain;
    QWidget *logoBar;
    QHBoxLayout *horizontalLayoutX;
    QPushButton *minButton;
    QPushButton *maxButton;
    QPushButton *closeButton;
    QTabWidget *tabWidget;
    QWidget *tab0;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayoutLauncher;
    QPushButton *pushButtonSWGP;
    QPushButton *pushButtonSWOGP;
    QCheckBox *checkBoxWindowed;
    QWidget *tab1;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textBrowser;
    QWidget *tab2;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QTextBrowser *textBrowserUpdate;
    QWidget *layoutWidget1;
    QFormLayout *formLayoutBU;
    QLineEdit *betapinbox;
    QPushButton *pushButtonBU;
    QWidget *tab3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayoutAbout;
    QLabel *labelVersion;
    QLabel *labelHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(900, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(900, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(900, 580));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setStyleSheet(QLatin1String("#centralWidget {\n"
"  background-color: #222222;\n"
"  margin: 0px;\n"
"  padding: 0px;\n"
"  font-size: 14px;\n"
"  color: white;\n"
"}\n"
"\n"
"QTabWidget QPushButton {\n"
"	box-shadow:inset 0px 1px 0px 0px #54a3f7;\n"
"	background:linear-gradient(to bottom, #007dc1 5%, #0061a7 100%);\n"
"	background-color:#007dc1;\n"
"	border-radius:3px;\n"
"	border:1px solid #124d77;\n"
"	display:inline-block;\n"
"	cursor:pointer;\n"
"	color:#ffffff;\n"
"	font-family:arial;\n"
"	font-size:13px;\n"
"	padding:3px 20px;\n"
"	text-decoration:none;\n"
"	text-shadow:0px 1px 0px #154682;\n"
"}\n"
"\n"
"QTabWidget QPushButton:hover {\n"
"	background:linear-gradient(to bottom, #0061a7 5%, #007dc1 100%);\n"
"	background-color:#0061a7;\n"
"}\n"
"\n"
"#closeButton {\n"
"  background-image: url(\":/close_window.png\");\n"
"  border: none;\n"
"}\n"
"\n"
"#maxButton {\n"
"  background-image: url(\":/maximize_window.png\");\n"
"  border: none;\n"
"}\n"
"\n"
"#minButton {\n"
"  background-image: url(\":/minimize_window.png\");\n"
"  borde"
                        "r: none;\n"
"}\n"
"\n"
"#closeButton:hover {\n"
"  background-image: url(\":/close_window_hover.png\");\n"
"}\n"
"\n"
"#maxButton:hover {\n"
"  background-image: url(\":/maximize_window_hover.png\");\n"
"}\n"
"\n"
"#minButton:hover {\n"
"  background-image: url(\":/minimize_window_hover.png\");\n"
"}\n"
"\n"
"#closeButton:pressed {\n"
"  background-image: url(\":/close_window_hover.png\");\n"
"}\n"
"\n"
"#maxButton:pressed {\n"
"  background-image: url(\":/maximize_window_hover.png\");\n"
"}\n"
"\n"
"#minButton:pressed {\n"
"  background-image: url(\":/minimize_window_hover.png\");\n"
"}\n"
"\n"
"#logoBar {\n"
"  background-image:url(\":/logo_color.png\");\n"
"  background-position: center;\n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
"#logoBar QPushButton:pressed {\n"
"  background-color: #959292;  \n"
"}\n"
"\n"
"#logoBar QPushButton:hover {\n"
"  background-color: #626161;\n"
"  border: 1px white solid; \n"
"}\n"
"\n"
"#tabWidget {\n"
" \n"
"}\n"
"\n"
"#tabWidget:pane {\n"
"  /*borde-top: none;    */  "
                        "\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"  box-shadow:inset 0px 1px 0px 0px #54a3f7;\n"
"  background:linear-gradient(to bottom, #707072 5%, #707072 100%);  \n"
"  color:#ffffff;\n"
"  height: 30px;\n"
"  background-color: rgba(150, 150, 150, 0.5)\n"
" \n"
"}\n"
"QTabBar::tab:hover{  \n"
"  background-color: rgba(150, 150, 150, 0.8)\n"
"}\n"
"\n"
"QTabBar::tab:selected{  \n"
"  background-color: rgba(150, 150, 150, 0.8)\n"
"}\n"
"\n"
"#tab0 {\n"
"	background-color: #222222;\n"
"}\n"
"#tab1 {\n"
"	background-color: #222222;\n"
"}\n"
"#tab2 {\n"
"	background-color: #222222;\n"
"}\n"
"#tab3 {\n"
"	background-color: #222222;\n"
"}\n"
"\n"
"QLabel {\n"
"	color: white;\n"
"}\n"
"\n"
"#horizontalLayoutX {\n"
"  \n"
"}\n"
"\n"
"#horizontalLayoutLogo {\n"
" \n"
"}\n"
"\n"
"\n"
"\n"
"QCheckBox {\n"
"  color:white;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"  border: 1px solid grey;\n"
"  border-radius: 2px;\n"
"  padding: 1px 1px 1px 1px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"  background-color: white;\n"
"}\n"
""
                        "\n"
"QCheckBox::indicator:unchecked:hover {\n"
"  border: 1px solid grey;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"  background: #007dc1;\n"
"}\n"
"\n"
" QCheckBox::indicator:checked:hover {\n"
"      border: 1px solid grey;\n"
" }\n"
""));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutMain = new QGridLayout();
        gridLayoutMain->setSpacing(0);
        gridLayoutMain->setObjectName(QStringLiteral("gridLayoutMain"));
        logoBar = new QWidget(centralWidget);
        logoBar->setObjectName(QStringLiteral("logoBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logoBar->sizePolicy().hasHeightForWidth());
        logoBar->setSizePolicy(sizePolicy1);
        logoBar->setMinimumSize(QSize(0, 60));

        gridLayoutMain->addWidget(logoBar, 0, 0, 1, 1);

        horizontalLayoutX = new QHBoxLayout();
        horizontalLayoutX->setSpacing(2);
        horizontalLayoutX->setObjectName(QStringLiteral("horizontalLayoutX"));
        horizontalLayoutX->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayoutX->setContentsMargins(-1, -1, -1, 38);
        minButton = new QPushButton(centralWidget);
        minButton->setObjectName(QStringLiteral("minButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(minButton->sizePolicy().hasHeightForWidth());
        minButton->setSizePolicy(sizePolicy2);
        minButton->setMinimumSize(QSize(20, 20));
        minButton->setMaximumSize(QSize(20, 20));
        minButton->setFlat(false);

        horizontalLayoutX->addWidget(minButton);

        maxButton = new QPushButton(centralWidget);
        maxButton->setObjectName(QStringLiteral("maxButton"));
        sizePolicy2.setHeightForWidth(maxButton->sizePolicy().hasHeightForWidth());
        maxButton->setSizePolicy(sizePolicy2);
        maxButton->setMinimumSize(QSize(20, 20));
        maxButton->setMaximumSize(QSize(20, 20));
        maxButton->setFlat(false);

        horizontalLayoutX->addWidget(maxButton);

        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        sizePolicy2.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy2);
        closeButton->setMinimumSize(QSize(20, 20));
        closeButton->setMaximumSize(QSize(20, 20));
        closeButton->setFlat(false);

        horizontalLayoutX->addWidget(closeButton);


        gridLayoutMain->addLayout(horizontalLayoutX, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tab0 = new QWidget();
        tab0->setObjectName(QStringLiteral("tab0"));
        sizePolicy.setHeightForWidth(tab0->sizePolicy().hasHeightForWidth());
        tab0->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(tab0);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 201, 101));
        verticalLayoutLauncher = new QVBoxLayout(layoutWidget);
        verticalLayoutLauncher->setSpacing(6);
        verticalLayoutLauncher->setContentsMargins(11, 11, 11, 11);
        verticalLayoutLauncher->setObjectName(QStringLiteral("verticalLayoutLauncher"));
        verticalLayoutLauncher->setContentsMargins(0, 0, 0, 0);
        pushButtonSWGP = new QPushButton(layoutWidget);
        pushButtonSWGP->setObjectName(QStringLiteral("pushButtonSWGP"));
        sizePolicy2.setHeightForWidth(pushButtonSWGP->sizePolicy().hasHeightForWidth());
        pushButtonSWGP->setSizePolicy(sizePolicy2);

        verticalLayoutLauncher->addWidget(pushButtonSWGP);

        pushButtonSWOGP = new QPushButton(layoutWidget);
        pushButtonSWOGP->setObjectName(QStringLiteral("pushButtonSWOGP"));
        sizePolicy2.setHeightForWidth(pushButtonSWOGP->sizePolicy().hasHeightForWidth());
        pushButtonSWOGP->setSizePolicy(sizePolicy2);

        verticalLayoutLauncher->addWidget(pushButtonSWOGP);

        checkBoxWindowed = new QCheckBox(layoutWidget);
        checkBoxWindowed->setObjectName(QStringLiteral("checkBoxWindowed"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBoxWindowed->sizePolicy().hasHeightForWidth());
        checkBoxWindowed->setSizePolicy(sizePolicy3);

        verticalLayoutLauncher->addWidget(checkBoxWindowed);

        tabWidget->addTab(tab0, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        sizePolicy.setHeightForWidth(tab1->sizePolicy().hasHeightForWidth());
        tab1->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(tab1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textBrowser = new QTextBrowser(tab1);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(textBrowser);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        sizePolicy.setHeightForWidth(tab2->sizePolicy().hasHeightForWidth());
        tab2->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(tab2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        splitter = new QSplitter(tab2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        textBrowserUpdate = new QTextBrowser(splitter);
        textBrowserUpdate->setObjectName(QStringLiteral("textBrowserUpdate"));
        splitter->addWidget(textBrowserUpdate);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        formLayoutBU = new QFormLayout(layoutWidget1);
        formLayoutBU->setSpacing(6);
        formLayoutBU->setContentsMargins(11, 11, 11, 11);
        formLayoutBU->setObjectName(QStringLiteral("formLayoutBU"));
        formLayoutBU->setContentsMargins(0, 5, 0, 0);
        betapinbox = new QLineEdit(layoutWidget1);
        betapinbox->setObjectName(QStringLiteral("betapinbox"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(betapinbox->sizePolicy().hasHeightForWidth());
        betapinbox->setSizePolicy(sizePolicy4);

        formLayoutBU->setWidget(0, QFormLayout::LabelRole, betapinbox);

        pushButtonBU = new QPushButton(layoutWidget1);
        pushButtonBU->setObjectName(QStringLiteral("pushButtonBU"));
        sizePolicy4.setHeightForWidth(pushButtonBU->sizePolicy().hasHeightForWidth());
        pushButtonBU->setSizePolicy(sizePolicy4);

        formLayoutBU->setWidget(0, QFormLayout::FieldRole, pushButtonBU);

        splitter->addWidget(layoutWidget1);

        horizontalLayout_3->addWidget(splitter);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QStringLiteral("tab3"));
        sizePolicy.setHeightForWidth(tab3->sizePolicy().hasHeightForWidth());
        tab3->setSizePolicy(sizePolicy);
        layoutWidget2 = new QWidget(tab3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 345, 34));
        verticalLayoutAbout = new QVBoxLayout(layoutWidget2);
        verticalLayoutAbout->setSpacing(6);
        verticalLayoutAbout->setContentsMargins(11, 11, 11, 11);
        verticalLayoutAbout->setObjectName(QStringLiteral("verticalLayoutAbout"));
        verticalLayoutAbout->setContentsMargins(0, 0, 0, 0);
        labelVersion = new QLabel(layoutWidget2);
        labelVersion->setObjectName(QStringLiteral("labelVersion"));
        labelVersion->setWordWrap(true);

        verticalLayoutAbout->addWidget(labelVersion);

        labelHelp = new QLabel(layoutWidget2);
        labelHelp->setObjectName(QStringLiteral("labelHelp"));

        verticalLayoutAbout->addWidget(labelHelp);

        tabWidget->addTab(tab3, QString());

        gridLayoutMain->addWidget(tabWidget, 1, 0, 1, 3);


        horizontalLayout->addLayout(gridLayoutMain);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Eurobattle.net Client", 0));
        minButton->setText(QString());
        maxButton->setText(QString());
        closeButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonSWGP->setToolTip(QApplication::translate("MainWindow", "Starting with GProxy is required for some DotA leagues<br />\n"
"to be able to join their games. It also provides reconnection<br />\n"
"in case you drop in the middle of the game.<br />\n"
"YOU CAN'T PLAY PG OR MANUALLY HOST GAMES IN THIS MODE!", 0));
#endif // QT_NO_TOOLTIP
        pushButtonSWGP->setText(QApplication::translate("MainWindow", "Start with GProxy", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonSWOGP->setToolTip(QApplication::translate("MainWindow", "Start without GProxy to play PG<br />\n"
"or manually host your games.", 0));
#endif // QT_NO_TOOLTIP
        pushButtonSWOGP->setText(QApplication::translate("MainWindow", "Start without GProxy", 0));
        checkBoxWindowed->setText(QApplication::translate("MainWindow", "Windowed", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab0), QApplication::translate("MainWindow", "Launcher", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "GProxy console", 0));
        pushButtonBU->setText(QApplication::translate("MainWindow", "Get Beta patch", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Update", 0));
        labelVersion->setText(QApplication::translate("MainWindow", "Eurobattle.net Client version 0.3.0.0", 0));
        labelHelp->setText(QApplication::translate("MainWindow", "We are searching for Qt/ C++ developers to further expand this client.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
