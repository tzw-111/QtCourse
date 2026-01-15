#include "chartmanager.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QDateTime>

QT_USE_NAMESPACE

ChartManager::ChartManager(QObject *parent) : QObject(parent)
{
}

ChartManager::~ChartManager()
{
}

QChart *ChartManager::createLogLevelPieChart()
{
    QMap<QString, int> levelCount = countLogLevels();
    QPieSeries *series = new QPieSeries();

    for (auto it = levelCount.constBegin(); it != levelCount.constEnd(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        series->append(label, it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("日志级别占比统计");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    return chart;
}

QChart *ChartManager::createLogTimeLineChart()
{
    QMap<QDateTime, int> timeCount = countLogsByTime(true);
    QLineSeries *series = new QLineSeries();

    for (auto it = timeCount.constBegin(); it != timeCount.constEnd(); ++it) {
        series->append(it.key().toMSecsSinceEpoch(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("日志时间趋势统计（按小时）");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(10);
    axisX->setFormat("yyyy-MM-dd HH:mm");
    axisX->setTitleText("时间");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("日志数量");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return chart;
}

void ChartManager::updateCharts()
{
    emit updateCharts();
}

QMap<QString, int> ChartManager::countLogLevels()
{
    QMap<QString, int> countMap;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        return countMap;
    }

    QSqlQuery query("SELECT log_level, COUNT(*) FROM logs GROUP BY log_level");
    while (query.next()) {
        QString level = query.value(0).toString();
        int count = query.value(1).toInt();
        countMap[level] = count;
    }

    return countMap;
}

QMap<QDateTime, int> ChartManager::countLogsByTime(bool byHour)
{
    QMap<QDateTime, int> countMap;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        return countMap;
    }

    QSqlQuery query;
    QString sql;

    if (byHour) {
        sql = "SELECT strftime('%Y-%m-%d %H:00:00', log_time) as hour, COUNT(*) FROM logs GROUP BY hour ORDER BY hour";
    } else {
        sql = "SELECT strftime('%Y-%m-%d %H:%M:00', log_time) as minute, COUNT(*) FROM logs GROUP BY minute ORDER BY minute";
    }

    if (query.exec(sql)) {
        while (query.next()) {
            QString timeStr = query.value(0).toString();
            int count = query.value(1).toInt();
            QDateTime time = QDateTime::fromString(timeStr, "yyyy-MM-dd HH:mm:ss");
            countMap[time] = count;
        }
    }

    return countMap;
}
