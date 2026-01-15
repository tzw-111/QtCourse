/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport_Logs;
    QAction *actionClear_Data;
    QAction *actionExit;
    QAction *actionExport_Logs;
    QAction *actionExport_Chart;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *filterGroupBox;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *levelLabel;
    QComboBox *levelFilter;
    QLabel *keywordLabel;
    QLineEdit *keywordFilter;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *searchButton;
    QPushButton *clearFiltersButton;
    QGroupBox *pieChartGroupBox;
    QVBoxLayout *verticalLayout_3;
    QChartView *pieChartView;
    QGroupBox *lineChartGroupBox;
    QVBoxLayout *verticalLayout_5;
    QChartView *lineChartView;
    QVBoxLayout *verticalLayout;
    QGroupBox *logListGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTableView *logTableView;
    QHBoxLayout *horizontalLayout_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuChart;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        actionImport_Logs = new QAction(MainWindow);
        actionImport_Logs->setObjectName("actionImport_Logs");
        actionClear_Data = new QAction(MainWindow);
        actionClear_Data->setObjectName("actionClear_Data");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionExport_Logs = new QAction(MainWindow);
        actionExport_Logs->setObjectName("actionExport_Logs");
        actionExport_Chart = new QAction(MainWindow);
        actionExport_Chart->setObjectName("actionExport_Chart");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        filterGroupBox = new QGroupBox(centralWidget);
        filterGroupBox->setObjectName("filterGroupBox");
        verticalLayout_4 = new QVBoxLayout(filterGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName("formLayout");
        levelLabel = new QLabel(filterGroupBox);
        levelLabel->setObjectName("levelLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, levelLabel);

        levelFilter = new QComboBox(filterGroupBox);
        levelFilter->addItem(QString());
        levelFilter->addItem(QString());
        levelFilter->addItem(QString());
        levelFilter->addItem(QString());
        levelFilter->addItem(QString());
        levelFilter->setObjectName("levelFilter");

        formLayout->setWidget(0, QFormLayout::FieldRole, levelFilter);

        keywordLabel = new QLabel(filterGroupBox);
        keywordLabel->setObjectName("keywordLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, keywordLabel);

        keywordFilter = new QLineEdit(filterGroupBox);
        keywordFilter->setObjectName("keywordFilter");

        formLayout->setWidget(1, QFormLayout::FieldRole, keywordFilter);


        verticalLayout_4->addLayout(formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        searchButton = new QPushButton(filterGroupBox);
        searchButton->setObjectName("searchButton");

        horizontalLayout_2->addWidget(searchButton);

        clearFiltersButton = new QPushButton(filterGroupBox);
        clearFiltersButton->setObjectName("clearFiltersButton");

        horizontalLayout_2->addWidget(clearFiltersButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        pieChartGroupBox = new QGroupBox(filterGroupBox);
        pieChartGroupBox->setObjectName("pieChartGroupBox");
        verticalLayout_3 = new QVBoxLayout(pieChartGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        pieChartView = new QChartView(pieChartGroupBox);
        pieChartView->setObjectName("pieChartView");

        verticalLayout_3->addWidget(pieChartView);


        verticalLayout_4->addWidget(pieChartGroupBox);

        lineChartGroupBox = new QGroupBox(filterGroupBox);
        lineChartGroupBox->setObjectName("lineChartGroupBox");
        verticalLayout_5 = new QVBoxLayout(lineChartGroupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        lineChartView = new QChartView(lineChartGroupBox);
        lineChartView->setObjectName("lineChartView");

        verticalLayout_5->addWidget(lineChartView);


        verticalLayout_4->addWidget(lineChartGroupBox);


        horizontalLayout->addWidget(filterGroupBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        logListGroupBox = new QGroupBox(centralWidget);
        logListGroupBox->setObjectName("logListGroupBox");
        verticalLayout_2 = new QVBoxLayout(logListGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        logTableView = new QTableView(logListGroupBox);
        logTableView->setObjectName("logTableView");
        logTableView->setAlternatingRowColors(true);
        logTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        logTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_2->addWidget(logTableView);


        verticalLayout->addWidget(logListGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1200, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuChart = new QMenu(menuBar);
        menuChart->setObjectName("menuChart");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuChart->menuAction());
        menuFile->addAction(actionImport_Logs);
        menuFile->addAction(actionExport_Logs);
        menuFile->addSeparator();
        menuFile->addAction(actionClear_Data);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuChart->addAction(actionExport_Chart);
        mainToolBar->addAction(actionImport_Logs);
        mainToolBar->addAction(actionClear_Data);

        retranslateUi(MainWindow);
        QObject::connect(keywordFilter, &QLineEdit::returnPressed, searchButton, qOverload<>(&QPushButton::click));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\345\210\206\346\236\220\345\271\263\345\217\260", nullptr));
        actionImport_Logs->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\227\245\345\277\227", nullptr));
        actionClear_Data->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionExport_Logs->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\227\245\345\277\227", nullptr));
        actionExport_Chart->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\233\276\350\241\250", nullptr));
        filterGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\255\233\351\200\211\346\235\241\344\273\266", nullptr));
        levelLabel->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\347\272\247\345\210\253:", nullptr));
        levelFilter->setItemText(0, QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250", nullptr));
        levelFilter->setItemText(1, QCoreApplication::translate("MainWindow", "INFO", nullptr));
        levelFilter->setItemText(2, QCoreApplication::translate("MainWindow", "ERROR", nullptr));
        levelFilter->setItemText(3, QCoreApplication::translate("MainWindow", "WARN", nullptr));
        levelFilter->setItemText(4, QCoreApplication::translate("MainWindow", "DEBUG", nullptr));

        keywordLabel->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\224\256\350\257\215:", nullptr));
        keywordFilter->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\205\263\351\224\256\350\257\215", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        clearFiltersButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\347\255\233\351\200\211", nullptr));
        pieChartGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\272\247\345\210\253\347\273\237\350\256\241", nullptr));
        lineChartGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264\350\266\213\345\212\277", nullptr));
        logListGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\345\210\227\350\241\250", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuChart->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
