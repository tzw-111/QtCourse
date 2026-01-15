#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db/databasemanager.h"
#include "thread/logparserthread.h"
#include "chart/chartmanager.h"
#include "logmodel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dbManager(new DatabaseManager(this))
    , m_chartManager(new ChartManager(this))
    , m_parserThread(nullptr)
    , m_progressDialog(nullptr)
    , m_chartUpdateTimer(new QTimer(this))
{
    ui->setupUi(this);
    setupUI();
    setupDatabase();
    setupCharts();
    loadRecentFiles();

    connect(m_chartUpdateTimer, &QTimer::timeout, this, &MainWindow::updateCharts);
    m_chartUpdateTimer->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    ui->levelFilter->setCurrentIndex(0);
    ui->keywordFilter->clear();

    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui->clearFiltersButton, &QPushButton::clicked, this, &MainWindow::on_clearFiltersButton_clicked);
    connect(ui->levelFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_levelFilter_currentIndexChanged);
    connect(ui->keywordFilter, &QLineEdit::textChanged, this, &MainWindow::on_keywordFilter_textChanged);
}

void MainWindow::setupDatabase()
{
    if (!m_dbManager->initialize()) {
        QMessageBox::critical(this, "错误", "数据库初始化失败！");
        close();
        return;
    }

    m_logModel = new LogModel(this, QSqlDatabase::database());
    m_logModel->setTable("logs");
    m_logModel->setHeaderData(1, Qt::Horizontal, "时间");
    m_logModel->setHeaderData(2, Qt::Horizontal, "级别");
    m_logModel->setHeaderData(3, Qt::Horizontal, "内容");
    m_logModel->setHeaderData(4, Qt::Horizontal, "来源");
    m_logModel->select();

    ui->logTableView->setModel(m_logModel);
    ui->logTableView->hideColumn(0);
    ui->logTableView->resizeColumnsToContents();
    ui->logTableView->setSortingEnabled(true);
    ui->logTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupCharts()
{
    ui->pieChartView->setChart(m_chartManager->createLogLevelPieChart());
    ui->lineChartView->setChart(m_chartManager->createLogTimeLineChart());
}

void MainWindow::updateCharts()
{
    QChart *pieChart = m_chartManager->createLogLevelPieChart();
    QChart *lineChart = m_chartManager->createLogTimeLineChart();

    ui->pieChartView->setChart(pieChart);
    ui->lineChartView->setChart(lineChart);
}

void MainWindow::applyFilters()
{
    QString levelFilter = ui->levelFilter->currentText();
    QString keywordFilter = ui->keywordFilter->text().trimmed();

    QString filter;

    if (levelFilter != "全部") {
        filter = QString("log_level = '%1'").arg(levelFilter);
    }

    if (!keywordFilter.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += QString("log_content LIKE '%%1%'").arg(keywordFilter);
    }

    m_logModel->setFilter(filter);
    m_logModel->select();
}

void MainWindow::on_actionImport_Logs_triggered()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(
        this,
        "选择日志文件",
        QString(),
        "日志文件 (*.log *.txt);;所有文件 (*.*)"
    );

    if (filePaths.isEmpty()) {
        return;
    }

    m_parserThread = new LogParserThread(filePaths, this);
    m_progressDialog = new QProgressDialog("正在解析日志文件...", "取消", 0, 100, this);
    m_progressDialog->setWindowModality(Qt::WindowModal);
    m_progressDialog->setMinimumDuration(0);

    connect(m_parserThread, &LogParserThread::progressUpdated, this, &MainWindow::handleProgressUpdated);
    connect(m_parserThread, &LogParserThread::parsingFinished, this, &MainWindow::handleParsingFinished);
    connect(m_parserThread, &LogParserThread::parsingCancelled, this, &MainWindow::handleParsingCancelled);
    connect(m_progressDialog, &QProgressDialog::canceled, m_parserThread, &LogParserThread::cancel);

    m_parserThread->start();
    m_progressDialog->exec();
}

void MainWindow::on_actionClear_Data_triggered()
{
    if (QMessageBox::question(this, "确认", "确定要清空所有日志数据吗？此操作不可恢复。") != QMessageBox::Yes) {
        return;
    }

    if (m_dbManager->clearAllLogs()) {
        m_logModel->select();
        updateCharts();
        showStatusMessage("数据已清空", 3000);
    } else {
        QMessageBox::warning(this, "错误", "清空数据失败！");
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_searchButton_clicked()
{
    applyFilters();
}

void MainWindow::on_clearFiltersButton_clicked()
{
    ui->levelFilter->setCurrentIndex(0);
    ui->keywordFilter->clear();
    applyFilters();
}

void MainWindow::on_levelFilter_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    applyFilters();
}

void MainWindow::on_keywordFilter_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    applyFilters();
}

void MainWindow::handleProgressUpdated(int progress)
{
    if (m_progressDialog) {
        m_progressDialog->setValue(progress);
    }
}

void MainWindow::handleParsingFinished(const QList<QStringList> &parsedLogs, int totalLines, int failedLines)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        delete m_progressDialog;
        m_progressDialog = nullptr;
    }

    if (!parsedLogs.isEmpty()) {
        if (m_dbManager->insertLogs(parsedLogs)) {
            m_logModel->select();
            updateCharts();

            QString message = QString("导入完成！共解析 %1 行，成功 %2 行，失败 %3 行。").arg(totalLines).arg(parsedLogs.size()).arg(failedLines);
            showStatusMessage(message, 5000);

            if (failedLines > 0) {
                QMessageBox::warning(this, "提示", message);
            }
        } else {
            QMessageBox::critical(this, "错误", "日志导入数据库失败！");
        }
    } else {
        QMessageBox::information(this, "提示", "未解析到有效日志数据！");
    }

    if (m_parserThread) {
        m_parserThread->wait();
        delete m_parserThread;
        m_parserThread = nullptr;
    }
}

void MainWindow::handleParsingCancelled()
{
    if (m_progressDialog) {
        m_progressDialog->close();
        delete m_progressDialog;
        m_progressDialog = nullptr;
    }

    showStatusMessage("解析已取消", 3000);

    if (m_parserThread) {
        m_parserThread->wait();
        delete m_parserThread;
        m_parserThread = nullptr;
    }
}

void MainWindow::showStatusMessage(const QString &message, int timeout)
{
    statusBar()->showMessage(message, timeout);
}

void MainWindow::addToRecentFiles(const QStringList &filePaths)
{
    QSettings settings("LOGAI", "LogAnalysis");
    QStringList recentFiles = settings.value("RecentFiles").toStringList();

    for (const QString &path : filePaths) {
        if (recentFiles.contains(path)) {
            recentFiles.removeOne(path);
        }
        recentFiles.prepend(path);
    }

    while (recentFiles.size() > 5) {
        recentFiles.removeLast();
    }

    settings.setValue("RecentFiles", recentFiles);
    m_recentFiles = recentFiles;
}

void MainWindow::loadRecentFiles()
{
    QSettings settings("LOGAI", "LogAnalysis");
    m_recentFiles = settings.value("RecentFiles").toStringList();
}

void MainWindow::on_actionExport_Logs_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "导出日志",
        QString(),
        "CSV 文件 (*.csv);;文本文件 (*.txt)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件！");
        return;
    }

    QTextStream out(&file);
    out << "时间,级别,内容,来源\n";

    QSqlQuery query(m_logModel->query());
    while (query.next()) {
        QString time = query.value("log_time").toString();
        QString level = query.value("log_level").toString();
        QString content = query.value("log_content").toString().replace(",", "，");
        QString source = query.value("log_source").toString();
        out << QString("%1,%2,%3,%4\n").arg(time).arg(level).arg(content).arg(source);
    }

    file.close();
    showStatusMessage("日志导出成功", 3000);
}

void MainWindow::on_actionExport_Chart_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "导出图表",
        QString(),
        "PDF 文件 (*.pdf);;PNG 文件 (*.png)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    if (filePath.endsWith(".pdf")) {
        QPdfWriter writer(filePath);
        writer.setPageSize(QPageSize(QPageSize::A4));
        QPainter painter(&writer);

        ui->pieChartView->render(&painter, QRectF(50, 50, 400, 400));
        writer.newPage();
        ui->lineChartView->render(&painter, QRectF(50, 50, 700, 400));
    } else if (filePath.endsWith(".png")) {
        QPixmap pixmap(ui->pieChartView->size());
        QPainter painter(&pixmap);
        ui->pieChartView->render(&painter);
        pixmap.save(filePath);
    }

    showStatusMessage("图表导出成功", 3000);
}
