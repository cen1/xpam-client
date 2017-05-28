/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelTitle;
    QHBoxLayout *horizontalLayoutX;
    QPushButton *minButton;
    QPushButton *maxButton;
    QPushButton *closeButton;
    QTabWidget *tabWidget;
    QWidget *tab0;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *hs1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutLauncher;
    QPushButton *pushButtonSWOGP;
    QPushButton *pushButtonSWGP;
    QCheckBox *checkBox_windowed;
    QCheckBox *checkBox_fullscreen;
    QCheckBox *checkBox_opengl;
    QSpacerItem *verticalSpacer;
    QSpacerItem *hs2;
    QWidget *tab1;
    QLabel *preloaderLabel1;
    QLabel *labelGproxyout;
    QLabel *labelGproxywarnings;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *gpoptionsgroupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_console;
    QCheckBox *checkBox_option_sounds;
    QCheckBox *checkBox_sound_1;
    QCheckBox *checkBox_sound_2;
    QCheckBox *checkBox_sound_3;
    QCheckBox *checkBox_sound_4;
    QCheckBox *checkBox_sound_5;
    QCheckBox *checkBox_sound_6;
    QCheckBox *checkBox_sound_7;
    QCheckBox *checkBox_sound_8;
    QCheckBox *checkBox_sound_9;
    QCheckBox *checkBox_sound_10;
    QCheckBox *checkBox_chatbuffer;
    QCheckBox *checkBox_debug;
    QCheckBox *checkBox_telemetry;
    QPushButton *pushButton_w3path;
    QWidget *tab2;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QTextBrowser *textBrowserUpdate;
    QWidget *layoutWidget1;
    QFormLayout *formLayoutBU;
    QLineEdit *betapinbox;
    QPushButton *pushButtonBU;
    QCheckBox *checkBox_updates;
    QWidget *tab3;
    QLabel *labelAbout;
    QLabel *labelW3Version;
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
        MainWindow->setStyleSheet(QLatin1String("QStatusBar {\n"
"     /*background: #878787;*/\n"
"  background: #4C4C4C;\n"
"    color:white;\n"
"    font-family: \"Lucida Sans Unicode\";\n"
" }"));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(900, 580));
        QFont font;
        centralWidget->setFont(font);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setStyleSheet(QLatin1String("#centralWidget {\n"
"  background-color: rgba(150, 150, 150);\n"
"  margin: 0px;\n"
"  padding: 0px;\n"
"  font-size: 14px;\n"
"  color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"  border: 2px solid #4C4C4C;\n"
"  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(63,63,63,1), stop:1 rgba(14,14,14,1));\n"
"  color: #ffffff;\n"
"  font-family: \"Lucida Sans Unicode\";\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(84,84,84,1), stop:1 rgba(14,14,14,1));\n"
"}\n"
"\n"
"QGroupBox {\n"
"  color: white;\n"
"}\n"
"\n"
"#logoBar {\n"
"  background-color: #007dc1;\n"
"  text-align: center;\n"
"}\n"
"\n"
"#labelTitle {\n"
"  font-weight: bold;\n"
"  \n"
"}\n"
"\n"
"#hs1 {\n"
"  width: 10%;\n"
"}\n"
"\n"
"a {\n"
" color: #007dc1;\n"
"}\n"
"\n"
"#tabWidget {\n"
" \n"
"}\n"
"\n"
"#tabWidget:pane {\n"
"  /*borde-top: none;    */  \n"
"}\n"
"\n"
"QTabBar::tab {\n"
"  background-color: rgba(150, 150, 150);\n"
"  color:#ffffff;\n"
"  height: 30px;\n"
"  font-"
                        "family: \"Lucida Sans Unicode\";\n"
"\n"
"}\n"
"QTabBar::tab:hover{  \n"
"  background-color: rgba(180, 180, 180);\n"
"}\n"
"\n"
"QTabBar::tab:selected{  \n"
"  background-color: rgba(180, 180, 180);\n"
"}\n"
"\n"
"#tab0 {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tab1 {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tab2 {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tab3 {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
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
"QCheckBox {\n"
"  color:white;\n"
"  font-family: \"Lucida Sans Unicode\";\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"  border: 1px solid grey;\n"
"  border-radius: 2px;\n"
"  padding: 1px 1px 1px 1px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unche"
                        "cked {\n"
"  background-color: white;\n"
"}\n"
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
"\n"
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
"  border: none;\n"
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
"  "
                        "background-image: url(\":/maximize_window_hover.png\");\n"
"}\n"
"\n"
"#minButton:pressed {\n"
"  background-image: url(\":/minimize_window_hover.png\");\n"
"}\n"
"\n"
"#pushButtonSWGP {\n"
"  background-image: url(\":/gproxygate.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
"#pushButtonSWGP:hover {\n"
"  background-image: url(\":/gproxygate_hover.png\");  \n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
"#pushButtonSWOGP {\n"
"  background-image: url(\":/normalgate.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
"#pushButtonSWOGP:hover {\n"
"  background-image: url(\":/normalgate_hover.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
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
        logoBar->setMinimumSize(QSize(0, 20));
        logoBar->setMaximumSize(QSize(16777215, 20));
        horizontalLayout_4 = new QHBoxLayout(logoBar);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelTitle = new QLabel(logoBar);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        sizePolicy.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy);
        labelTitle->setLayoutDirection(Qt::LeftToRight);
        labelTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(labelTitle);


        gridLayoutMain->addWidget(logoBar, 0, 0, 1, 1);

        horizontalLayoutX = new QHBoxLayout();
        horizontalLayoutX->setSpacing(0);
        horizontalLayoutX->setObjectName(QStringLiteral("horizontalLayoutX"));
        horizontalLayoutX->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayoutX->setContentsMargins(-1, -1, -1, 0);
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
        horizontalLayout_6 = new QHBoxLayout(tab0);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        hs1 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(hs1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayoutLauncher = new QHBoxLayout();
        horizontalLayoutLauncher->setSpacing(0);
        horizontalLayoutLauncher->setObjectName(QStringLiteral("horizontalLayoutLauncher"));
        pushButtonSWOGP = new QPushButton(tab0);
        pushButtonSWOGP->setObjectName(QStringLiteral("pushButtonSWOGP"));
        sizePolicy2.setHeightForWidth(pushButtonSWOGP->sizePolicy().hasHeightForWidth());
        pushButtonSWOGP->setSizePolicy(sizePolicy2);
        pushButtonSWOGP->setMinimumSize(QSize(400, 367));
        pushButtonSWOGP->setMaximumSize(QSize(400, 367));

        horizontalLayoutLauncher->addWidget(pushButtonSWOGP);

        pushButtonSWGP = new QPushButton(tab0);
        pushButtonSWGP->setObjectName(QStringLiteral("pushButtonSWGP"));
        sizePolicy2.setHeightForWidth(pushButtonSWGP->sizePolicy().hasHeightForWidth());
        pushButtonSWGP->setSizePolicy(sizePolicy2);
        pushButtonSWGP->setMinimumSize(QSize(400, 367));
        pushButtonSWGP->setMaximumSize(QSize(400, 367));
        QFont font1;
        font1.setFamily(QStringLiteral("Lucida Sans Unicode"));
        pushButtonSWGP->setFont(font1);

        horizontalLayoutLauncher->addWidget(pushButtonSWGP);


        verticalLayout->addLayout(horizontalLayoutLauncher);

        checkBox_windowed = new QCheckBox(tab0);
        checkBox_windowed->setObjectName(QStringLiteral("checkBox_windowed"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox_windowed->sizePolicy().hasHeightForWidth());
        checkBox_windowed->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(checkBox_windowed);

        checkBox_fullscreen = new QCheckBox(tab0);
        checkBox_fullscreen->setObjectName(QStringLiteral("checkBox_fullscreen"));

        verticalLayout->addWidget(checkBox_fullscreen);

        checkBox_opengl = new QCheckBox(tab0);
        checkBox_opengl->setObjectName(QStringLiteral("checkBox_opengl"));

        verticalLayout->addWidget(checkBox_opengl);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);

        hs2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(hs2);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab0, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        sizePolicy.setHeightForWidth(tab1->sizePolicy().hasHeightForWidth());
        tab1->setSizePolicy(sizePolicy);
        preloaderLabel1 = new QLabel(tab1);
        preloaderLabel1->setObjectName(QStringLiteral("preloaderLabel1"));
        preloaderLabel1->setGeometry(QRect(20, 20, 16, 16));
        labelGproxyout = new QLabel(tab1);
        labelGproxyout->setObjectName(QStringLiteral("labelGproxyout"));
        labelGproxyout->setGeometry(QRect(40, 20, 581, 21));
        labelGproxyout->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        labelGproxywarnings = new QLabel(tab1);
        labelGproxywarnings->setObjectName(QStringLiteral("labelGproxywarnings"));
        labelGproxywarnings->setGeometry(QRect(40, 50, 841, 20));
        labelGproxywarnings->setTextFormat(Qt::RichText);
        labelGproxywarnings->setOpenExternalLinks(true);
        labelGproxywarnings->setTextInteractionFlags(Qt::TextBrowserInteraction);
        pushButton = new QPushButton(tab1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 80, 171, 23));
        pushButton_2 = new QPushButton(tab1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 80, 111, 23));
        gpoptionsgroupBox = new QGroupBox(tab1);
        gpoptionsgroupBox->setObjectName(QStringLiteral("gpoptionsgroupBox"));
        gpoptionsgroupBox->setGeometry(QRect(40, 120, 241, 351));
        gpoptionsgroupBox->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(gpoptionsgroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 221, 311));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_console = new QCheckBox(layoutWidget);
        checkBox_console->setObjectName(QStringLiteral("checkBox_console"));
        checkBox_console->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_console);

        checkBox_option_sounds = new QCheckBox(layoutWidget);
        checkBox_option_sounds->setObjectName(QStringLiteral("checkBox_option_sounds"));
        checkBox_option_sounds->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_option_sounds);

        checkBox_sound_1 = new QCheckBox(layoutWidget);
        checkBox_sound_1->setObjectName(QStringLiteral("checkBox_sound_1"));
        checkBox_sound_1->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_1);

        checkBox_sound_2 = new QCheckBox(layoutWidget);
        checkBox_sound_2->setObjectName(QStringLiteral("checkBox_sound_2"));
        checkBox_sound_2->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_2);

        checkBox_sound_3 = new QCheckBox(layoutWidget);
        checkBox_sound_3->setObjectName(QStringLiteral("checkBox_sound_3"));
        checkBox_sound_3->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_3);

        checkBox_sound_4 = new QCheckBox(layoutWidget);
        checkBox_sound_4->setObjectName(QStringLiteral("checkBox_sound_4"));
        checkBox_sound_4->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_4);

        checkBox_sound_5 = new QCheckBox(layoutWidget);
        checkBox_sound_5->setObjectName(QStringLiteral("checkBox_sound_5"));
        checkBox_sound_5->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_5);

        checkBox_sound_6 = new QCheckBox(layoutWidget);
        checkBox_sound_6->setObjectName(QStringLiteral("checkBox_sound_6"));
        checkBox_sound_6->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_6);

        checkBox_sound_7 = new QCheckBox(layoutWidget);
        checkBox_sound_7->setObjectName(QStringLiteral("checkBox_sound_7"));
        checkBox_sound_7->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_7);

        checkBox_sound_8 = new QCheckBox(layoutWidget);
        checkBox_sound_8->setObjectName(QStringLiteral("checkBox_sound_8"));
        checkBox_sound_8->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_8);

        checkBox_sound_9 = new QCheckBox(layoutWidget);
        checkBox_sound_9->setObjectName(QStringLiteral("checkBox_sound_9"));

        verticalLayout_2->addWidget(checkBox_sound_9);

        checkBox_sound_10 = new QCheckBox(layoutWidget);
        checkBox_sound_10->setObjectName(QStringLiteral("checkBox_sound_10"));
        checkBox_sound_10->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_sound_10);

        checkBox_chatbuffer = new QCheckBox(layoutWidget);
        checkBox_chatbuffer->setObjectName(QStringLiteral("checkBox_chatbuffer"));
        checkBox_chatbuffer->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(checkBox_chatbuffer);

        checkBox_debug = new QCheckBox(layoutWidget);
        checkBox_debug->setObjectName(QStringLiteral("checkBox_debug"));

        verticalLayout_2->addWidget(checkBox_debug);

        checkBox_telemetry = new QCheckBox(layoutWidget);
        checkBox_telemetry->setObjectName(QStringLiteral("checkBox_telemetry"));

        verticalLayout_2->addWidget(checkBox_telemetry);

        pushButton_w3path = new QPushButton(tab1);
        pushButton_w3path->setObjectName(QStringLiteral("pushButton_w3path"));
        pushButton_w3path->setGeometry(QRect(340, 80, 111, 23));
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
        sizePolicy2.setHeightForWidth(pushButtonBU->sizePolicy().hasHeightForWidth());
        pushButtonBU->setSizePolicy(sizePolicy2);
        pushButtonBU->setMinimumSize(QSize(150, 20));
        pushButtonBU->setMaximumSize(QSize(150, 20));

        formLayoutBU->setWidget(0, QFormLayout::FieldRole, pushButtonBU);

        checkBox_updates = new QCheckBox(layoutWidget1);
        checkBox_updates->setObjectName(QStringLiteral("checkBox_updates"));

        formLayoutBU->setWidget(1, QFormLayout::LabelRole, checkBox_updates);

        splitter->addWidget(layoutWidget1);

        horizontalLayout_3->addWidget(splitter);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QStringLiteral("tab3"));
        sizePolicy.setHeightForWidth(tab3->sizePolicy().hasHeightForWidth());
        tab3->setSizePolicy(sizePolicy);
        labelAbout = new QLabel(tab3);
        labelAbout->setObjectName(QStringLiteral("labelAbout"));
        labelAbout->setGeometry(QRect(20, 20, 351, 461));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(labelAbout->sizePolicy().hasHeightForWidth());
        labelAbout->setSizePolicy(sizePolicy5);
        labelAbout->setOpenExternalLinks(true);
        labelW3Version = new QLabel(tab3);
        labelW3Version->setObjectName(QStringLiteral("labelW3Version"));
        labelW3Version->setGeometry(QRect(20, 500, 351, 16));
        tabWidget->addTab(tab3, QString());

        gridLayoutMain->addWidget(tabWidget, 1, 0, 1, 3);


        horizontalLayout->addLayout(gridLayoutMain);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Eurobattle.net Client", 0));
        labelTitle->setText(QApplication::translate("MainWindow", "Eurobattle.net Client", 0));
        minButton->setText(QString());
        maxButton->setText(QString());
        closeButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonSWOGP->setToolTip(QApplication::translate("MainWindow", "Start without GProxy to play PG<br />\n"
"or manually host your games.", 0));
#endif // QT_NO_TOOLTIP
        pushButtonSWOGP->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonSWGP->setToolTip(QApplication::translate("MainWindow", "Starting with GProxy is required for some DotA leagues<br />\n"
"to be able to join their games. It also provides reconnection<br />\n"
"in case you drop in the middle of the game.<br />\n"
"YOU CAN'T PLAY PG OR MANUALLY HOST GAMES IN THIS MODE!", 0));
#endif // QT_NO_TOOLTIP
        pushButtonSWGP->setText(QString());
        checkBox_windowed->setText(QApplication::translate("MainWindow", "Windowed", 0));
        checkBox_fullscreen->setText(QApplication::translate("MainWindow", "Native fullscreen", 0));
        checkBox_opengl->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab0), QApplication::translate("MainWindow", " LAUNCHER ", 0));
        preloaderLabel1->setText(QString());
        labelGproxyout->setText(QApplication::translate("MainWindow", "GProxy output", 0));
        labelGproxywarnings->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Copy GProxy log to clipboard", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Open log file", 0));
        gpoptionsgroupBox->setTitle(QApplication::translate("MainWindow", "GProxy Options", 0));
        checkBox_console->setText(QApplication::translate("MainWindow", "Visible console (must start manually)", 0));
        checkBox_option_sounds->setText(QApplication::translate("MainWindow", "Enable sounds", 0));
        checkBox_sound_1->setText(QApplication::translate("MainWindow", "\"Game started\" sound", 0));
        checkBox_sound_2->setText(QApplication::translate("MainWindow", "\"Join the game\" sound", 0));
        checkBox_sound_3->setText(QApplication::translate("MainWindow", "\"Slap\" sound", 0));
        checkBox_sound_4->setText(QApplication::translate("MainWindow", "\"Channel moderated\" sound", 0));
        checkBox_sound_5->setText(QApplication::translate("MainWindow", "\"Channel unmoderated\" sound", 0));
        checkBox_sound_6->setText(QApplication::translate("MainWindow", "\"Challenge started\" sound", 0));
        checkBox_sound_7->setText(QApplication::translate("MainWindow", "\"Challenge completed\" sound", 0));
        checkBox_sound_8->setText(QApplication::translate("MainWindow", "\"Friend joined game\" sound", 0));
        checkBox_sound_9->setText(QApplication::translate("MainWindow", "\"Whisper\" sound", 0));
        checkBox_sound_10->setText(QApplication::translate("MainWindow", "\"You were kicked\" sound", 0));
        checkBox_chatbuffer->setText(QApplication::translate("MainWindow", "Chat buffer (experimental)", 0));
        checkBox_debug->setText(QApplication::translate("MainWindow", "Debugging", 0));
        checkBox_telemetry->setText(QApplication::translate("MainWindow", "Telemetry", 0));
        pushButton_w3path->setText(QApplication::translate("MainWindow", "Change W3 path", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "  GPROXY  ", 0));
        pushButtonBU->setText(QApplication::translate("MainWindow", "Get Beta patch", 0));
        checkBox_updates->setText(QApplication::translate("MainWindow", "Enable automatic updates", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", " UPDATE ", 0));
        labelAbout->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Eurobattle.net Client version 0.81 (May 2017), developed by cen</p><p><br/>We are searching for Qt/ C++ developers to further expand this client.</p><p><br/></p><p>TODO:</p><p>-bnet Chat client</p><p>-TS integration</p><p>-Displaying player's profile and league stats in the client</p><p>-and more...</p><p><br/></p><p>Special thanks to:</p><p><span style=\" font-weight:600;\">IStealSkills</span> - help with desig</p><p><span style=\" font-weight:600;\">Stefos007</span> - original GProxy implementation</p><p>BNETtdocs, Stormlib, PvPGN and GHost projects</p></body></html>", 0));
        labelW3Version->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("MainWindow", " ABOUT ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
