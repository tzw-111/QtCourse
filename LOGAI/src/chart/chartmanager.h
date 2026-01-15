#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <QObject>
#include <QChart>
#include <QPieSeries>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>

QT_USE_NAMESPACE
class ChartManager : public QObject
{
    Q_OBJECT
public:
    explicit ChartManager(QObject *parent = nullptr);
    ~ChartManager() override;

    QChart *createLogLevelPieChart();
    QChart *createLogTimeLineChart();

public slots:
    void updateCharts();

private:
    QMap<QString, int> countLogLevels();
    QMap<QDateTime, int> countLogsByTime(bool byHour = true);
};

#endif // CHARTMANAGER_H
