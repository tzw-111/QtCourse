#include "databasemanager.h"
#include <QSqlError>
#include <QDebug>
#include <QFile>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initialize()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("log_analysis.db");

    if (!m_db.open()) {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    return createLogTable();
}

bool DatabaseManager::createLogTable()
{
    QSqlQuery query;
    QString createTableSql = R"(
        CREATE TABLE IF NOT EXISTS logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            log_time TEXT,
            log_level TEXT,
            log_content TEXT,
            log_source TEXT
        );
    )";

    if (!query.exec(createTableSql)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::insertLogs(const QList<QStringList> &logs)
{
    if (logs.isEmpty()) {
        return true;
    }

    QSqlQuery query;
    if (!query.exec("BEGIN TRANSACTION")) {
        qDebug() << "Failed to begin transaction:" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO logs (log_time, log_level, log_content, log_source) VALUES (?, ?, ?, ?)");

    for (const QStringList &log : logs) {
        if (log.size() < 3) {
            continue;
        }

        query.addBindValue(log[0]);
        query.addBindValue(log[1]);
        query.addBindValue(log[2]);
        query.addBindValue(log.size() > 3 ? log[3] : QString());

        if (!query.exec()) {
            qDebug() << "Failed to insert log:" << query.lastError().text();
            query.exec("ROLLBACK");
            return false;
        }
    }

    if (!query.exec("COMMIT")) {
        qDebug() << "Failed to commit transaction:" << query.lastError().text();
        query.exec("ROLLBACK");
        return false;
    }

    return true;
}

bool DatabaseManager::clearAllLogs()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM logs")) {
        qDebug() << "Failed to clear logs:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_db;
}
