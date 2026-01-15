#include "logparserthread.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

LogParserThread::LogParserThread(const QStringList &filePaths, QObject *parent)
    : QThread(parent), m_filePaths(filePaths), m_cancelled(false)
{
}

LogParserThread::~LogParserThread()
{
}

void LogParserThread::cancel()
{
    m_cancelled = true;
}

void LogParserThread::run()
{
    QList<QStringList> parsedLogs;
    int totalLines = 0;
    int failedLines = 0;
    int processedLines = 0;
    int totalFiles = m_filePaths.size();

    for (int i = 0; i < totalFiles; ++i) {
        const QString &filePath = m_filePaths[i];
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        QTextStream in(&file);
        QString line;

        while (!in.atEnd()) {
            if (m_cancelled) {
                emit parsingCancelled();
                return;
            }

            line = in.readLine().trimmed();
            if (line.isEmpty()) {
                continue;
            }

            totalLines++;
            QStringList logParts = parseLogLine(line);

            if (!logParts.isEmpty()) {
                logParts << filePath; // Add source
                parsedLogs << logParts;
            } else {
                failedLines++;
            }

            processedLines++;
            if (processedLines % 100 == 0) {
                int progress = (processedLines * 100) / (totalLines + 1);
                emit progressUpdated(progress);
            }
        }

        file.close();

        int fileProgress = ((i + 1) * 100) / totalFiles;
        emit progressUpdated(fileProgress);
    }

    emit progressUpdated(100);
    emit parsingFinished(parsedLogs, totalLines, failedLines);
}

QStringList LogParserThread::parseLogLine(const QString &line)
{
    QRegularExpression logRegex(R"(^(\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}:\d{2}(\.\d+)?\s+)(INFO|ERROR|WARN|DEBUG)\s*:\s*(.*)$)");
    QRegularExpressionMatch match = logRegex.match(line);

    if (match.hasMatch()) {
        QString time = match.captured(1).trimmed();
        QString level = match.captured(3).trimmed();
        QString content = match.captured(4).trimmed();
        return {time, level, content};
    }
// Add source
    // Add source
    // Add source
// Add source// Add source// Add sou
    return {};
}
