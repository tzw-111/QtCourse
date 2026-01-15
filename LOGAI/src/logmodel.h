#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QSqlTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QColor>

class LogModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit LogModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~LogModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void setLogLevelColor(const QString &level, const QColor &color);

private:
    QMap<QString, QColor> m_levelColors;
};

#endif // LOGMODEL_H
