#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QStringList>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initialize();
    bool insertLogs(const QList<QStringList> &logs);
    bool clearAllLogs();
    QSqlDatabase getDatabase() const;

private:
    bool createLogTable();
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
