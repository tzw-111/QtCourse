#ifndef LOGPARSERTHREAD_H
#define LOGPARSERTHREAD_H

#include <QThread>
#include <QStringList>
#include <QProgressDialog>

class LogParserThread : public QThread
{
    Q_OBJECT
public:
    explicit LogParserThread(const QStringList &filePaths, QObject *parent = nullptr);
    ~LogParserThread() override;

    void cancel();

signals:
    void progressUpdated(int progress);
    void parsingFinished(const QList<QStringList> &parsedLogs, int totalLines, int failedLines);
    void parsingCancelled();

protected:
    void run() override;

private:
    QStringList parseLogLine(const QString &line);
    bool isValidLogLevel(const QString &level);

    QStringList m_filePaths;
    bool m_cancelled;
};

#endif // LOGPARSERTHREAD_H
