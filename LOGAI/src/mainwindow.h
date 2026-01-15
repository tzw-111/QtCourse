#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QProgressDialog>
#include <QChartView>
#include <QTimer>

QT_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class DatabaseManager;
class LogParserThread;
class ChartManager;
class LogModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionImport_Logs_triggered();
    void on_actionClear_Data_triggered();
    void on_actionExit_triggered();
    void on_searchButton_clicked();
    void on_clearFiltersButton_clicked();
    void on_levelFilter_currentIndexChanged(int index);
    void on_keywordFilter_textChanged(const QString &arg1);
    void on_actionExport_Logs_triggered();
    void on_actionExport_Chart_triggered();

    void handleProgressUpdated(int progress);
    void handleParsingFinished(const QList<QStringList> &parsedLogs, int totalLines, int failedLines);
    void handleParsingCancelled();

private:
    void setupUI();
    void setupDatabase();
    void setupCharts();
    void updateCharts();
    void applyFilters();
    void showStatusMessage(const QString &message, int timeout = 3000);
    void addToRecentFiles(const QStringList &filePaths);
    void loadRecentFiles();

    Ui::MainWindow *ui;
    DatabaseManager *m_dbManager;
    LogModel *m_logModel;
    ChartManager *m_chartManager;
    LogParserThread *m_parserThread;
    QProgressDialog *m_progressDialog;
    QTimer *m_chartUpdateTimer;
    QStringList m_recentFiles;
};

#endif // MAINWINDOW_H
