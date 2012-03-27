/********************************************************************************
** Form generated from reading UI file 'mainwindow.old.ui'
**
** Created: Tue Mar 27 13:27:31 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionPreview;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionNew;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionExport;
    QAction *actionOptions;
    QAction *actionManage_Soundtrack;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QGraphicsView *graphicsView;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_2;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QLabel *label_2;
    QLCDNumber *lcdNumber;
    QProgressBar *timeBar;
    QLabel *label_3;
    QLCDNumber *totalDurationTime;
    QListView *listView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSlide_Show;
    QMenu *menuMovie;
    QMenu *menuSound;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QTreeView *dirView;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(984, 821);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/resources/slides.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QFont font1;
        font1.setPointSize(9);
        actionExit->setFont(font1);
        actionPreview = new QAction(MainWindow);
        actionPreview->setObjectName(QString::fromUtf8("actionPreview"));
        actionPreview->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/resources/go.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreview->setIcon(icon1);
        actionPreview->setFont(font1);
        actionPreview->setIconVisibleInMenu(true);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionOpen->setFont(font1);
        actionOpen->setIconVisibleInMenu(true);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setEnabled(false);
        actionClose->setFont(font1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/resources/save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionSave->setFont(font1);
        actionSave->setIconVisibleInMenu(true);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionSave_As->setEnabled(false);
        actionSave_As->setFont(font1);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/resources/new.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon4);
        actionNew->setFont(font1);
        actionNew->setIconVisibleInMenu(true);
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/resources/pause.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon5);
        actionPause->setFont(font1);
        actionPause->setIconVisibleInMenu(true);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionStop->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/resources/stop-red.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon6);
        actionStop->setFont(font1);
        actionStop->setIconVisibleInMenu(true);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        actionExport->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/resources/dvd.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon7);
        actionExport->setFont(font1);
        actionExport->setIconVisibleInMenu(true);
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/prefix1/resources/tools.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptions->setIcon(icon8);
        actionOptions->setFont(font1);
        actionOptions->setIconVisibleInMenu(true);
        actionManage_Soundtrack = new QAction(MainWindow);
        actionManage_Soundtrack->setObjectName(QString::fromUtf8("actionManage_Soundtrack"));
        actionManage_Soundtrack->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/new/prefix1/resources/notes.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionManage_Soundtrack->setIcon(icon9);
        actionManage_Soundtrack->setFont(font1);
        actionManage_Soundtrack->setIconVisibleInMenu(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        graphicsView = new QGraphicsView(frame);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(640, 480));
        graphicsView->setMaximumSize(QSize(640, 480));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 138, 138);"));
        graphicsView->setFrameShape(QFrame::Box);
        graphicsView->setFrameShadow(QFrame::Raised);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_3->addWidget(graphicsView, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        startButton = new QPushButton(frame);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        startButton->setIcon(icon1);

        gridLayout_2->addWidget(startButton, 0, 0, 1, 1);

        pauseButton = new QPushButton(frame);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setEnabled(false);
        pauseButton->setIcon(icon5);

        gridLayout_2->addWidget(pauseButton, 0, 1, 1, 1);

        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setEnabled(false);
        stopButton->setIcon(icon6);

        gridLayout_2->addWidget(stopButton, 0, 2, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        lcdNumber = new QLCDNumber(frame);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setLineWidth(2);
        lcdNumber->setNumDigits(6);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdNumber, 0, 4, 1, 1);

        timeBar = new QProgressBar(frame);
        timeBar->setObjectName(QString::fromUtf8("timeBar"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(timeBar->sizePolicy().hasHeightForWidth());
        timeBar->setSizePolicy(sizePolicy);
        timeBar->setMinimumSize(QSize(130, 0));
        timeBar->setValue(0);

        gridLayout_2->addWidget(timeBar, 0, 5, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 6, 1, 1);

        totalDurationTime = new QLCDNumber(frame);
        totalDurationTime->setObjectName(QString::fromUtf8("totalDurationTime"));
        totalDurationTime->setLineWidth(2);
        totalDurationTime->setNumDigits(6);
        totalDurationTime->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(totalDurationTime, 0, 7, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 1, 0, 1, 1);


        gridLayout_5->addWidget(frame, 0, 0, 1, 1);

        listView = new QListView(centralWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(0, 130));
        listView->setMaximumSize(QSize(16777215, 130));
        listView->setLayoutDirection(Qt::LeftToRight);
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        listView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        listView->setFlow(QListView::TopToBottom);
        listView->setViewMode(QListView::IconMode);

        gridLayout_5->addWidget(listView, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 984, 25));
        menuBar->setAutoFillBackground(false);
        menuBar->setNativeMenuBar(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setAutoFillBackground(false);
        menuFile->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.514286 rgba(232, 232, 232, 255), stop:1 rgba(197, 197, 197, 255));"));
        menuFile->setTearOffEnabled(false);
        menuSlide_Show = new QMenu(menuBar);
        menuSlide_Show->setObjectName(QString::fromUtf8("menuSlide_Show"));
        menuSlide_Show->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.514286 rgba(232, 232, 232, 255), stop:1 rgba(197, 197, 197, 255));"));
        menuMovie = new QMenu(menuBar);
        menuMovie->setObjectName(QString::fromUtf8("menuMovie"));
        menuMovie->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.514286 rgba(232, 232, 232, 255), stop:1 rgba(197, 197, 197, 255));"));
        menuSound = new QMenu(menuBar);
        menuSound->setObjectName(QString::fromUtf8("menuSound"));
        menuSound->setLayoutDirection(Qt::LeftToRight);
        menuSound->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.514286 rgba(232, 232, 232, 255), stop:1 rgba(197, 197, 197, 255));"));
        menuSound->setTearOffEnabled(false);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        QFont font2;
        font2.setPointSize(8);
        mainToolBar->setFont(font2);
        mainToolBar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.514286 rgba(232, 232, 232, 255), stop:1 rgba(197, 197, 197, 255));"));
        mainToolBar->setIconSize(QSize(28, 28));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        dirView = new QTreeView(dockWidgetContents);
        dirView->setObjectName(QString::fromUtf8("dirView"));
        dirView->setMinimumSize(QSize(250, 250));

        gridLayout->addWidget(dirView, 0, 1, 1, 1);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 150));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSlide_Show->menuAction());
        menuBar->addAction(menuMovie->menuAction());
        menuBar->addAction(menuSound->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSlide_Show->addAction(actionPreview);
        menuSlide_Show->addAction(actionPause);
        menuSlide_Show->addAction(actionStop);
        menuSlide_Show->addSeparator();
        menuMovie->addAction(actionOptions);
        menuMovie->addAction(actionExport);
        menuSound->addAction(actionManage_Soundtrack);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPreview);
        mainToolBar->addAction(actionPause);
        mainToolBar->addAction(actionStop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOptions);
        mainToolBar->addAction(actionExport);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionManage_Soundtrack);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionPreview->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        actionExport->setText(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "Options...", 0, QApplication::UnicodeUTF8));
        actionManage_Soundtrack->setText(QApplication::translate("MainWindow", "Soundtrack", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionManage_Soundtrack->setToolTip(QApplication::translate("MainWindow", "Manage Soundtrack", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pauseButton->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Total", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuSlide_Show->setTitle(QApplication::translate("MainWindow", "Preview", 0, QApplication::UnicodeUTF8));
        menuMovie->setTitle(QApplication::translate("MainWindow", "SlideShow", 0, QApplication::UnicodeUTF8));
        menuSound->setTitle(QApplication::translate("MainWindow", "Sound", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", ".", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
