#include "errorhandler.h"

#include <QTime>


ErrorHandler::ErrorHandler(QTextEdit *textEdit)
{
    _textEdit = textEdit;
}

void ErrorHandler::printError(QString errorText)
{
    _textEdit->append("[" + QTime().currentTime().toString("hh:mm:ss") + "]: " + errorText);
}
