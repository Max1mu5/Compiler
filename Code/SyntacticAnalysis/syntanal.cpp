#include "syntanal.h"

SyntAnal::SyntAnal(QString code, QStringList terminals,
                   QList<QList<QString>> recedenceMat,
                   QList<QPair<int, int>> numTokens,
                   QList<QStringList> tokens,
                   QString formalLang)
{
    _code = code;
    _terminals = terminals;
    _recedenceMat = recedenceMat;
    _numTokens = numTokens;
    _tokens = tokens;
    _formalLang = formalLang;
}

void SyntAnal::startSyntAnal()
{
    _numTokens.append({-1, -1});
    _stack.append("@entryPoint@");
    QList<QPair<int, int>>::Iterator itNumTokens = _numTokens.begin();

    int i = 0;
    while (itNumTokens != _numTokens.end())
    {
        findFirstTerm(); // Ищем первый терминал в стеке





        i++;
        itNumTokens++;
    }
}
