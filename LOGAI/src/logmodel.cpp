#include "logmodel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LogModel::LogModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    m_levelColors["ERROR"] = QColor(Qt::red);
    m_levelColors["WARN"] = QColor(Qt::yellow);
    m_levelColors["INFO"] = QColor(Qt::black);
    m_levelColors["DEBUG"] = QColor(Qt::blue);
}

LogModel::~LogModel()
{
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::ForegroundRole && index.column() == 1) {
        QVariant level = QSqlTableModel::data(this->index(index.row(), 1), Qt::DisplayRole);
        if (m_levelColors.contains(level.toString())) {
            return m_levelColors[level.toString()];
        }
    }

    if (role == Qt::TextAlignmentRole && index.column() == 0) {
        return Qt::AlignCenter;
    }

    if (role == Qt::TextAlignmentRole && index.column() == 1) {
        return Qt::AlignCenter;
    }

    return QSqlTableModel::data(index, role);
}

bool LogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    return QSqlTableModel::setData(index, value, role);
}

Qt::ItemFlags LogModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return QSqlTableModel::flags(index);
}

void LogModel::setLogLevelColor(const QString &level, const QColor &color)
{
    m_levelColors[level] = color;
    emit dataChanged(index(0, 1), index(rowCount() - 1, 1));
}
