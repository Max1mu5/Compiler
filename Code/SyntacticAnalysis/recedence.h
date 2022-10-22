#ifndef RECEDENCE_H
#define RECEDENCE_H

#include "recedenceitem.h"

class Recedence
{
public:
    Recedence();

    void constructRecedenceTable(QString formalLang);
    QList<RecedenceItem> getFinalRecedence();
    QList<RecedenceItem> getNonTerm();
    QList<RecedenceItem> getTerm();
    QStringList getTerminals();
    QList<QList<QString>> getRecedenceMat();
    int find(QList<RecedenceItem> list, QString termName);


private:
    QList<RecedenceItem> _finalRecedence;
    QList<RecedenceItem> _nonTerm;
    QList<RecedenceItem> _term;
    QStringList _terminals;
    QString _formalLang;
    QList<QStringList> _tokens;
    QList<QList<QString>> _recedenceMat;


    void generateNonTerm(QList<QStringList> tokens);
    void generateTerm(QList<QStringList> tokens);
    void generateRecedence();
    QList<QStringList> parseLanguage();
    int findTerminalIndex(QString terminal);
    QPair<int, int> findTerminal(QString terminal);

};

#endif // RECEDENCE_H
