#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QTextEdit>

class ErrorHandler : public QObject
{
    Q_OBJECT

public:
    ErrorHandler(QTextEdit *textEdit = nullptr);

public slots:
    void printError(QString errorText);

signals:
    void emitError(QString errorText);

private:
    QTextEdit *_textEdit;
};

#endif // ERRORHANDLER_H
