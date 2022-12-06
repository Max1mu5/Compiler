#ifndef SYNTANAL_H
#define SYNTANAL_H

#include <QString>
#include <QStack>

#include "errorhandler.h"
#include "ast.h"

class SyntAnal : public ErrorHandler
{
public:
    SyntAnal(QString code, QStringList terminals,
             QList<QList<QString>> recedenceMat,
             QList<QPair<int, int>> numTokens,
             QList<QStringList> tokens,
             QString formalLang);
    void startSyntAnal();
    Ast* getAst();

private:
    QString _code;
    QStringList _terminals;
    QList<QList<QString>> _recedenceMat;
    QList<QString> _stack;
    QList<QPair<int, int>> _numTokens;
    QList<QStringList> _tokens;
    QList<QStringList>_formalLangRules;
    QString _formalLang;

    Ast *_ast;

    int findFirstTerm(int startPos);
    int getTerminalIndex(QString term);
    void parseCode();
    void parseFormalLang();
    void addNeighbours(QString *chain, int pos);
    int ruleNumber(QString chain);


};

#endif // SYNTANAL_H
