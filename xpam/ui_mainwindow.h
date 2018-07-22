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
    QTabWidget *tabWidget;
    QWidget *tabLauncher;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *hs1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutLauncher;
    QPushButton *pushButtonGWN;
    QFormLayout *formLayout;
    QPushButton *pushButtonGWG;
    QPushButton *pushButtonGWD;
    QHBoxLayout *horizontalLayoutOptions;
    QSpacerItem *verticalSpacer;
    QSpacerItem *hs2;
    QWidget *tabGproxy;
    QLabel *preloaderLabel1;
    QLabel *labelGproxyout;
    QLabel *labelGproxywarnings;
    QPushButton *pushButtonGPCL;
    QPushButton *pushButtonGPNOTEPAD;
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
    QWidget *tabW3;
    QPushButton *pushButtonClientLog;
    QGroupBox *war_latest_groupbox;
    QLabel *war_latest_label_2;
    QLabel *label_WarLatestPath;
    QPushButton *pushButton_warLatestPath;
    QGroupBox *groupBox_latest;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_gb_latest;
    QCheckBox *checkBox_fullscreen_latest;
    QCheckBox *checkBox_opengl_latest;
    QCheckBox *checkBox_windowed_latest;
    QCheckBox *check_useGproxy_latest;
    QGroupBox *war_latest_groupbox_2;
    QLabel *label_War126Path;
    QLabel *label;
    QPushButton *pushButton_war126Path;
    QLabel *label_2;
    QGroupBox *groupBox_126;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout__gb_126;
    QCheckBox *checkBox_opengl_126;
    QCheckBox *checkBox_windowed_126;
    QCheckBox *checkBox_useGproxy_126;
    QWidget *tabUpdate;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_6;
    QTextBrowser *textBrowserUpdate;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *betapinbox;
    QPushButton *pushButtonBU;
    QCheckBox *checkBox_updates;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tabAbout;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelAbout;
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
" color: #85c3e5;\n"
"}\n"
"\n"
"a span {\n"
" color: #85c3e5;\n"
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
"  c"
                        "olor:#ffffff;\n"
"  height: 30px;\n"
"  font-family: \"Lucida Sans Unicode\";\n"
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
"#tabLauncher {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tabGproxy {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tabW3 {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tabUpdate {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"#tabAbout {\n"
"  border-image: url(\":/back.png\") 0 0 0 0 stretch stretch;\n"
"  border-width: 0px;\n"
"}\n"
"\n"
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
"  font-family: \"Lucida San"
                        "s Unicode\";\n"
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
"#pushButtonGWN {\n"
"  background-image: url(\":/gwselect1.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"#pushButtonGWG {\n"
"  background-image: url(\":/gwselect2.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"#pushButtonGWD {\n"
"  background-image: url(\":/gwselect3.png\");\n"
"  background-repeat: no-repeat;\n"
"}\n"
"\n"
"#pushButtonGWN:hover {\n"
"  border-color: #007dc1;\n"
"}\n"
"#pushButtonGWG:hover {\n"
"  border-color: #007dc1;\n"
"}\n"
"#pushButtonGWD:hover {\n"
"  border-color: #007dc1;\n"
"}\n"
"\n"
"#checkBoxNoG"
                        "p {\n"
"  margin-left: 6px;	\n"
"}"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutMain = new QGridLayout();
        gridLayoutMain->setSpacing(0);
        gridLayoutMain->setObjectName(QStringLiteral("gridLayoutMain"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabLauncher = new QWidget();
        tabLauncher->setObjectName(QStringLiteral("tabLauncher"));
        sizePolicy.setHeightForWidth(tabLauncher->sizePolicy().hasHeightForWidth());
        tabLauncher->setSizePolicy(sizePolicy);
        horizontalLayout_6 = new QHBoxLayout(tabLauncher);
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
        pushButtonGWN = new QPushButton(tabLauncher);
        pushButtonGWN->setObjectName(QStringLiteral("pushButtonGWN"));
        pushButtonGWN->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonGWN->sizePolicy().hasHeightForWidth());
        pushButtonGWN->setSizePolicy(sizePolicy1);
        pushButtonGWN->setMinimumSize(QSize(0, 370));
        pushButtonGWN->setMaximumSize(QSize(0, 0));

        horizontalLayoutLauncher->addWidget(pushButtonGWN);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));

        horizontalLayoutLauncher->addLayout(formLayout);

        pushButtonGWG = new QPushButton(tabLauncher);
        pushButtonGWG->setObjectName(QStringLiteral("pushButtonGWG"));
        sizePolicy1.setHeightForWidth(pushButtonGWG->sizePolicy().hasHeightForWidth());
        pushButtonGWG->setSizePolicy(sizePolicy1);
        pushButtonGWG->setMinimumSize(QSize(400, 350));
        pushButtonGWG->setMaximumSize(QSize(400, 350));
        QFont font1;
        font1.setFamily(QStringLiteral("Lucida Sans Unicode"));
        pushButtonGWG->setFont(font1);
        pushButtonGWG->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayoutLauncher->addWidget(pushButtonGWG);

        pushButtonGWD = new QPushButton(tabLauncher);
        pushButtonGWD->setObjectName(QStringLiteral("pushButtonGWD"));
        pushButtonGWD->setEnabled(true);
        pushButtonGWD->setMinimumSize(QSize(400, 350));
        pushButtonGWD->setMaximumSize(QSize(400, 350));
        pushButtonGWD->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayoutLauncher->addWidget(pushButtonGWD);


        verticalLayout->addLayout(horizontalLayoutLauncher);

        horizontalLayoutOptions = new QHBoxLayout();
        horizontalLayoutOptions->setSpacing(6);
        horizontalLayoutOptions->setObjectName(QStringLiteral("horizontalLayoutOptions"));

        verticalLayout->addLayout(horizontalLayoutOptions);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);

        hs2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(hs2);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        tabWidget->addTab(tabLauncher, QString());
        tabGproxy = new QWidget();
        tabGproxy->setObjectName(QStringLiteral("tabGproxy"));
        sizePolicy.setHeightForWidth(tabGproxy->sizePolicy().hasHeightForWidth());
        tabGproxy->setSizePolicy(sizePolicy);
        preloaderLabel1 = new QLabel(tabGproxy);
        preloaderLabel1->setObjectName(QStringLiteral("preloaderLabel1"));
        preloaderLabel1->setGeometry(QRect(20, 20, 16, 16));
        labelGproxyout = new QLabel(tabGproxy);
        labelGproxyout->setObjectName(QStringLiteral("labelGproxyout"));
        labelGproxyout->setGeometry(QRect(40, 20, 581, 21));
        labelGproxyout->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        labelGproxywarnings = new QLabel(tabGproxy);
        labelGproxywarnings->setObjectName(QStringLiteral("labelGproxywarnings"));
        labelGproxywarnings->setGeometry(QRect(40, 50, 841, 20));
        labelGproxywarnings->setTextFormat(Qt::RichText);
        labelGproxywarnings->setOpenExternalLinks(true);
        labelGproxywarnings->setTextInteractionFlags(Qt::TextBrowserInteraction);
        pushButtonGPCL = new QPushButton(tabGproxy);
        pushButtonGPCL->setObjectName(QStringLiteral("pushButtonGPCL"));
        pushButtonGPCL->setGeometry(QRect(40, 80, 171, 23));
        pushButtonGPNOTEPAD = new QPushButton(tabGproxy);
        pushButtonGPNOTEPAD->setObjectName(QStringLiteral("pushButtonGPNOTEPAD"));
        pushButtonGPNOTEPAD->setGeometry(QRect(220, 80, 111, 23));
        gpoptionsgroupBox = new QGroupBox(tabGproxy);
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

        tabWidget->addTab(tabGproxy, QString());
        tabW3 = new QWidget();
        tabW3->setObjectName(QStringLiteral("tabW3"));
        pushButtonClientLog = new QPushButton(tabW3);
        pushButtonClientLog->setObjectName(QStringLiteral("pushButtonClientLog"));
        pushButtonClientLog->setGeometry(QRect(30, 30, 150, 19));
        pushButtonClientLog->setMaximumSize(QSize(150, 16777215));
        war_latest_groupbox = new QGroupBox(tabW3);
        war_latest_groupbox->setObjectName(QStringLiteral("war_latest_groupbox"));
        war_latest_groupbox->setGeometry(QRect(30, 90, 391, 331));
        war_latest_label_2 = new QLabel(war_latest_groupbox);
        war_latest_label_2->setObjectName(QStringLiteral("war_latest_label_2"));
        war_latest_label_2->setGeometry(QRect(10, 20, 131, 16));
        war_latest_label_2->setTextFormat(Qt::AutoText);
        label_WarLatestPath = new QLabel(war_latest_groupbox);
        label_WarLatestPath->setObjectName(QStringLiteral("label_WarLatestPath"));
        label_WarLatestPath->setGeometry(QRect(130, 20, 251, 20));
        pushButton_warLatestPath = new QPushButton(war_latest_groupbox);
        pushButton_warLatestPath->setObjectName(QStringLiteral("pushButton_warLatestPath"));
        pushButton_warLatestPath->setGeometry(QRect(10, 40, 150, 19));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_warLatestPath->sizePolicy().hasHeightForWidth());
        pushButton_warLatestPath->setSizePolicy(sizePolicy2);
        pushButton_warLatestPath->setMaximumSize(QSize(150, 16777215));
        groupBox_latest = new QGroupBox(war_latest_groupbox);
        groupBox_latest->setObjectName(QStringLiteral("groupBox_latest"));
        groupBox_latest->setGeometry(QRect(9, 139, 371, 101));
        verticalLayoutWidget = new QWidget(groupBox_latest);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 92, 77));
        verticalLayout_gb_latest = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_gb_latest->setSpacing(6);
        verticalLayout_gb_latest->setContentsMargins(11, 11, 11, 11);
        verticalLayout_gb_latest->setObjectName(QStringLiteral("verticalLayout_gb_latest"));
        verticalLayout_gb_latest->setContentsMargins(0, 0, 0, 0);
        checkBox_fullscreen_latest = new QCheckBox(verticalLayoutWidget);
        checkBox_fullscreen_latest->setObjectName(QStringLiteral("checkBox_fullscreen_latest"));

        verticalLayout_gb_latest->addWidget(checkBox_fullscreen_latest);

        checkBox_opengl_latest = new QCheckBox(verticalLayoutWidget);
        checkBox_opengl_latest->setObjectName(QStringLiteral("checkBox_opengl_latest"));

        verticalLayout_gb_latest->addWidget(checkBox_opengl_latest);

        checkBox_windowed_latest = new QCheckBox(verticalLayoutWidget);
        checkBox_windowed_latest->setObjectName(QStringLiteral("checkBox_windowed_latest"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox_windowed_latest->sizePolicy().hasHeightForWidth());
        checkBox_windowed_latest->setSizePolicy(sizePolicy3);

        verticalLayout_gb_latest->addWidget(checkBox_windowed_latest);

        check_useGproxy_latest = new QCheckBox(verticalLayoutWidget);
        check_useGproxy_latest->setObjectName(QStringLiteral("check_useGproxy_latest"));

        verticalLayout_gb_latest->addWidget(check_useGproxy_latest);

        war_latest_groupbox_2 = new QGroupBox(tabW3);
        war_latest_groupbox_2->setObjectName(QStringLiteral("war_latest_groupbox_2"));
        war_latest_groupbox_2->setGeometry(QRect(440, 90, 391, 331));
        label_War126Path = new QLabel(war_latest_groupbox_2);
        label_War126Path->setObjectName(QStringLiteral("label_War126Path"));
        label_War126Path->setGeometry(QRect(160, 20, 151, 16));
        label = new QLabel(war_latest_groupbox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 131, 16));
        label->setTextFormat(Qt::AutoText);
        pushButton_war126Path = new QPushButton(war_latest_groupbox_2);
        pushButton_war126Path->setObjectName(QStringLiteral("pushButton_war126Path"));
        pushButton_war126Path->setGeometry(QRect(10, 40, 150, 19));
        sizePolicy2.setHeightForWidth(pushButton_war126Path->sizePolicy().hasHeightForWidth());
        pushButton_war126Path->setSizePolicy(sizePolicy2);
        pushButton_war126Path->setMaximumSize(QSize(150, 16777215));
        label_2 = new QLabel(war_latest_groupbox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 241, 16));
        label_2->setOpenExternalLinks(true);
        groupBox_126 = new QGroupBox(war_latest_groupbox_2);
        groupBox_126->setObjectName(QStringLiteral("groupBox_126"));
        groupBox_126->setGeometry(QRect(10, 140, 371, 101));
        verticalLayoutWidget_2 = new QWidget(groupBox_126);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 69, 57));
        verticalLayout__gb_126 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout__gb_126->setSpacing(6);
        verticalLayout__gb_126->setContentsMargins(11, 11, 11, 11);
        verticalLayout__gb_126->setObjectName(QStringLiteral("verticalLayout__gb_126"));
        verticalLayout__gb_126->setContentsMargins(0, 0, 0, 0);
        checkBox_opengl_126 = new QCheckBox(verticalLayoutWidget_2);
        checkBox_opengl_126->setObjectName(QStringLiteral("checkBox_opengl_126"));

        verticalLayout__gb_126->addWidget(checkBox_opengl_126);

        checkBox_windowed_126 = new QCheckBox(verticalLayoutWidget_2);
        checkBox_windowed_126->setObjectName(QStringLiteral("checkBox_windowed_126"));
        sizePolicy3.setHeightForWidth(checkBox_windowed_126->sizePolicy().hasHeightForWidth());
        checkBox_windowed_126->setSizePolicy(sizePolicy3);

        verticalLayout__gb_126->addWidget(checkBox_windowed_126);

        checkBox_useGproxy_126 = new QCheckBox(verticalLayoutWidget_2);
        checkBox_useGproxy_126->setObjectName(QStringLiteral("checkBox_useGproxy_126"));
        checkBox_useGproxy_126->setEnabled(true);
        checkBox_useGproxy_126->setCheckable(true);
        checkBox_useGproxy_126->setChecked(true);

        verticalLayout__gb_126->addWidget(checkBox_useGproxy_126);

        tabWidget->addTab(tabW3, QString());
        tabUpdate = new QWidget();
        tabUpdate->setObjectName(QStringLiteral("tabUpdate"));
        sizePolicy.setHeightForWidth(tabUpdate->sizePolicy().hasHeightForWidth());
        tabUpdate->setSizePolicy(sizePolicy);
        layoutWidget1 = new QWidget(tabUpdate);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(8, 8, 881, 531));
        verticalLayout_6 = new QVBoxLayout(layoutWidget1);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        textBrowserUpdate = new QTextBrowser(layoutWidget1);
        textBrowserUpdate->setObjectName(QStringLiteral("textBrowserUpdate"));

        verticalLayout_6->addWidget(textBrowserUpdate);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        betapinbox = new QLineEdit(layoutWidget1);
        betapinbox->setObjectName(QStringLiteral("betapinbox"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(betapinbox->sizePolicy().hasHeightForWidth());
        betapinbox->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(betapinbox);

        pushButtonBU = new QPushButton(layoutWidget1);
        pushButtonBU->setObjectName(QStringLiteral("pushButtonBU"));
        sizePolicy1.setHeightForWidth(pushButtonBU->sizePolicy().hasHeightForWidth());
        pushButtonBU->setSizePolicy(sizePolicy1);
        pushButtonBU->setMinimumSize(QSize(150, 20));
        pushButtonBU->setMaximumSize(QSize(150, 20));

        horizontalLayout_3->addWidget(pushButtonBU);


        verticalLayout_5->addLayout(horizontalLayout_3);

        checkBox_updates = new QCheckBox(layoutWidget1);
        checkBox_updates->setObjectName(QStringLiteral("checkBox_updates"));

        verticalLayout_5->addWidget(checkBox_updates);


        horizontalLayout_4->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_4);

        tabWidget->addTab(tabUpdate, QString());
        tabAbout = new QWidget();
        tabAbout->setObjectName(QStringLiteral("tabAbout"));
        sizePolicy.setHeightForWidth(tabAbout->sizePolicy().hasHeightForWidth());
        tabAbout->setSizePolicy(sizePolicy);
        layoutWidget2 = new QWidget(tabAbout);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 395, 501));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelAbout = new QLabel(layoutWidget2);
        labelAbout->setObjectName(QStringLiteral("labelAbout"));
        sizePolicy.setHeightForWidth(labelAbout->sizePolicy().hasHeightForWidth());
        labelAbout->setSizePolicy(sizePolicy);
        labelAbout->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelAbout->setOpenExternalLinks(true);

        verticalLayout_3->addWidget(labelAbout);

        tabWidget->addTab(tabAbout, QString());

        gridLayoutMain->addWidget(tabWidget, 0, 0, 1, 1);


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
#ifndef QT_NO_TOOLTIP
        pushButtonGWN->setToolTip(QApplication::translate("MainWindow", "Start without GProxy to play PG<br />\n"
"or manually host your games.", 0));
#endif // QT_NO_TOOLTIP
        pushButtonGWN->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonGWG->setToolTip(QApplication::translate("MainWindow", "Starting with GProxy is required for some DotA leagues<br />\n"
"to be able to join their games. It also provides reconnection<br />\n"
"in case you drop in the middle of the game.<br />\n"
"YOU CAN'T PLAY PG OR MANUALLY HOST GAMES IN THIS MODE!", 0));
#endif // QT_NO_TOOLTIP
        pushButtonGWG->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonGWD->setToolTip(QApplication::translate("MainWindow", "Warcraft 1.26a gateway", 0));
#endif // QT_NO_TOOLTIP
        pushButtonGWD->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabLauncher), QApplication::translate("MainWindow", " LAUNCHER ", 0));
        preloaderLabel1->setText(QString());
        labelGproxyout->setText(QApplication::translate("MainWindow", "GProxy output", 0));
        labelGproxywarnings->setText(QString());
        pushButtonGPCL->setText(QApplication::translate("MainWindow", "Copy GProxy log to clipboard", 0));
        pushButtonGPNOTEPAD->setText(QApplication::translate("MainWindow", "Open log file", 0));
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
        tabWidget->setTabText(tabWidget->indexOf(tabGproxy), QApplication::translate("MainWindow", "  GPROXY  ", 0));
        pushButtonClientLog->setText(QApplication::translate("MainWindow", "Open Client log file", 0));
        war_latest_groupbox->setTitle(QApplication::translate("MainWindow", "Latest Warcraft gateway (1.28.5)", 0));
        war_latest_label_2->setText(QApplication::translate("MainWindow", "Warcraft location", 0));
        label_WarLatestPath->setText(QApplication::translate("MainWindow", "Loading...", 0));
        pushButton_warLatestPath->setText(QApplication::translate("MainWindow", "Change", 0));
        groupBox_latest->setTitle(QApplication::translate("MainWindow", "Options", 0));
        checkBox_fullscreen_latest->setText(QApplication::translate("MainWindow", "Native fullscreen", 0));
        checkBox_opengl_latest->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        checkBox_windowed_latest->setText(QApplication::translate("MainWindow", "Windowed", 0));
        check_useGproxy_latest->setText(QApplication::translate("MainWindow", "Use GProxy", 0));
        war_latest_groupbox_2->setTitle(QApplication::translate("MainWindow", "Warcraft 1.26a gateway", 0));
        label_War126Path->setText(QApplication::translate("MainWindow", "Loading...", 0));
        label->setText(QApplication::translate("MainWindow", "Warcraft 1.26a location", 0));
        pushButton_war126Path->setText(QApplication::translate("MainWindow", "Change", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Do not have Warcraft 1.26a? Download it <a href=\"http://wiki.eurobattle.net/index.php?title=Warcraft_III_1.26\"><span style=\" text-decoration: underline; color: #85c3e5;\">here</span></a>.</p></body></html>", 0));
        groupBox_126->setTitle(QApplication::translate("MainWindow", "Options", 0));
        checkBox_opengl_126->setText(QApplication::translate("MainWindow", "OpenGL", 0));
        checkBox_windowed_126->setText(QApplication::translate("MainWindow", "Windowed", 0));
        checkBox_useGproxy_126->setText(QApplication::translate("MainWindow", "Use GProxy", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabW3), QApplication::translate("MainWindow", " WARCRAFT", 0));
        pushButtonBU->setText(QApplication::translate("MainWindow", "Get Beta patch", 0));
        checkBox_updates->setText(QApplication::translate("MainWindow", "Automatic updates enabled", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabUpdate), QApplication::translate("MainWindow", " UPDATE ", 0));
        labelAbout->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Eurobattle.net Client version 1.1 (August 2018), developed by cen, additional contributions by deer</p><p><br/>We are searching for Qt/ C++ developers to further expand this client.</p><p><br/></p><p>TODO:</p><p>-bnet Chat client</p><p>-TS integration</p><p>-Displaying player's profile and league stats in the client</p><p>- Native Warkeys?</p><p>-and more...</p><p><br/></p><p>Special thanks to:</p><p><span style=\" font-weight:600;\">IStealSkills</span> - help with desig</p><p><span style=\" font-weight:600;\">Stefos007</span> - original GProxy implementation</p><p>BNETtdocs, Stormlib, PvPGN and GHost projects</p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabAbout), QApplication::translate("MainWindow", " ABOUT ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
