#ifndef SYNTANAL_H
#define SYNTANAL_H

#include <QString>
#include <QStack>

class SyntAnal
{
public:
    SyntAnal(QString code, QStringList terminals,
             QList<QList<QString>> recedenceMat,
             QList<QPair<int, int>> numTokens,
             QList<QStringList> tokens,
             QString formalLang);
    void startSyntAnal();

private:
    QString _code;
    QStringList _terminals;
    QList<QList<QString>> _recedenceMat;
    QList<QString> _stack;
    QList<QPair<int, int>> _numTokens;
    QList<QStringList> _tokens;
    QString _formalLang;
};

#endif // SYNTANAL_H
