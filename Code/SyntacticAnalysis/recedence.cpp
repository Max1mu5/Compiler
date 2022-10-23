#include "recedence.h"


Recedence::Recedence()
{

}

void Recedence::constructRecedenceTable(QString formalLang)
{
    _formalLang = formalLang;
    generateNonTerm(parseLanguage());
    generateTerm(parseLanguage());
    generateRecedence();
}

QList<RecedenceItem> Recedence::getFinalRecedence()
{
    return _finalRecedence;
}

QList<RecedenceItem> Recedence::getNonTerm()
{
    return _nonTerm;
}

QList<RecedenceItem> Recedence::getTerm()
{
    return _term;
}

QStringList Recedence::getTerminals()
{
    return _terminals;
}

QList<QList<QString> > Recedence::getRecedenceMat()
{
    return _recedenceMat;
}

QString Recedence::getFormalLang()
{
    return _formalLang;
}

int Recedence::find(QList<RecedenceItem> list, QString termName)
{
    for(int i = 0; i < list.length(); i++)
        if(list[i].getName() == termName)
            return i;

    return -1;
}

void Recedence::generateNonTerm(QList<QStringList> tokens)
{
    bool isCommandStart;
    for(int row = 0; row < tokens.length(); row++)
    {
        RecedenceItem temp;
        temp.setName(tokens[row][0]);
        isCommandStart = true;

        QString tempLeft, tempRight;
        for(int word = 2; word < tokens[row].length(); word++)
        {
            if(tokens[row][word] == "|")
            {
                isCommandStart = true;
                temp.appendLeft(tempLeft);
                temp.appendRight(tempRight);
                continue;
            }

            if(isCommandStart)
            {
                tempLeft = tokens[row][word];
                tempRight = tokens[row][word];
                isCommandStart = false;
            }
            else
                tempRight = tokens[row][word];
        }
        temp.appendLeft(tempLeft);
        temp.appendRight(tempRight);
        _nonTerm.append(temp);
    }


    QList<RecedenceItem> copy = _nonTerm;
    for(int row = _nonTerm.length() - 2; row >= 0; row--)
    {
        QStringList left = copy[row].getLeft();
        for(int leftIndex = 0; leftIndex < left.length(); leftIndex++)
        {
            if(find(_nonTerm, left[leftIndex]) >= 0 && find(_nonTerm, left[leftIndex]) != row)
            {
                copy[row].getLeft().append(copy[find(copy, left[leftIndex])].getLeft());
                //copy[row].getLeft().remove(leftIndex);
            }
        }

        QStringList right = copy[row].getRight();
        for(int rightIndex = 0; rightIndex < right.length(); rightIndex++)
            if(find(_nonTerm, right[rightIndex]) >= 0 && find(_nonTerm, right[rightIndex]) != row)
            {
                copy[row].getRight().append(copy[find(copy, right[rightIndex])].getRight());
                //copy[row].getRight().remove(rightIndex);
            }
    }
    _nonTerm = copy;

    for(int row = 0; row < _nonTerm.length(); row++)
    {
        for(int wordLeft = 0; wordLeft < _nonTerm[row].getLeft().length() - 1; wordLeft++)
        {
            for(int wordRight = wordLeft + 1; wordRight < _nonTerm[row].getLeft().length(); wordRight++)
            {
                if(_nonTerm[row].getLeft()[wordLeft] == _nonTerm[row].getLeft()[wordRight])
                    _nonTerm[row].getLeft().remove(wordRight--);
            }
        }
        for(int wordLeft = 0; wordLeft < _nonTerm[row].getRight().length() - 1; wordLeft++)
        {
            for(int wordRight = wordLeft + 1; wordRight < _nonTerm[row].getRight().length(); wordRight++)
            {
                if(_nonTerm[row].getRight()[wordLeft] == _nonTerm[row].getRight()[wordRight])
                    _nonTerm[row].getRight().remove(wordRight--);
            }
        }

    }

}

void Recedence::generateTerm(QList<QStringList> tokens)
{
    bool isCommandStart;
    for(int row = 0; row < _nonTerm.length(); row++)
    {
        RecedenceItem temp;
        temp.setName(tokens[row][0]);
        isCommandStart = true;

        QString tempLeft, tempRight;
        for(int word = 2; word < tokens[row].length(); word++)
        {
            if(tokens[row][word] == "|" && find(_nonTerm, tokens[row][word]) == -1)
            {
                isCommandStart = true;
                temp.appendLeft(tempLeft);
                temp.appendRight(tempRight);
                continue;
            }

            QString asd = tokens[row][word];
            if(isCommandStart && find(_nonTerm, asd) == -1)
            {
                tempLeft = tokens[row][word];
                tempRight = tokens[row][word];
                isCommandStart = false;
            }
            else if(find(_nonTerm, tokens[row][word]) == -1)
                tempRight = tokens[row][word];
        }
        temp.appendLeft(tempLeft);
        temp.appendRight(tempRight);
        _term.append(temp);
    }

    QList<RecedenceItem> copy = _nonTerm;
    for(int row = _nonTerm.length() - 2; row >= 0; row--)
    {
        QStringList left = copy[row].getLeft();
        for(int leftIndex = 0; leftIndex < left.length(); leftIndex++)
        {
            if(find(_nonTerm, left[leftIndex]) >= 0 && find(_nonTerm, left[leftIndex]) != row)
            {
                _term[row].getLeft().append(_term[find(copy, left[leftIndex])].getLeft());
            }
        }

        QStringList right = copy[row].getRight();
        for(int rightIndex = 0; rightIndex < right.length(); rightIndex++)
            if(find(_nonTerm, right[rightIndex]) >= 0 && find(_nonTerm, right[rightIndex]) != row)
            {
                _term[row].getRight().append(_term[find(copy, right[rightIndex])].getRight());
            }
    }

    for(int row = 0; row < _term.length(); row++)
    {
        for(int wordLeft = 0; wordLeft < _term[row].getLeft().length() - 1; wordLeft++)
        {
            for(int wordRight = wordLeft + 1; wordRight < _term[row].getLeft().length(); wordRight++)
            {
                if(_term[row].getLeft()[wordLeft] == _term[row].getLeft()[wordRight])
                    _term[row].getLeft().remove(wordRight--);
            }
        }
        for(int wordLeft = 0; wordLeft < _term[row].getRight().length() - 1; wordLeft++)
        {
            for(int wordRight = wordLeft + 1; wordRight < _term[row].getRight().length(); wordRight++)
            {
                if(_term[row].getRight()[wordLeft] == _term[row].getRight()[wordRight])
                    _term[row].getRight().remove(wordRight--);
            }
        }

    }
    for(int row = 0; row < _term.length(); row++)
    {
        for(int wordLeft = 0; wordLeft < _term[row].getLeft().length(); wordLeft++)
        {
            if(_term[row].getLeft()[wordLeft] == "") _term[row].getLeft().remove(wordLeft--);
        }
        for(int wordLeft = 0; wordLeft < _term[row].getRight().length(); wordLeft++)
        {
            if(_term[row].getRight()[wordLeft] == "") _term[row].getRight().remove(wordLeft--);
        }
    }
}

void Recedence::generateRecedence()
{
    QStringList list;
    QList<QStringList> tokens = parseLanguage();

    for(int row = 0; row < tokens.length(); row++)
    {
        for(int word = 0; word < tokens[row].length(); word++)
        {
            if(find(_nonTerm, tokens[row][word]) == -1 && tokens[row][word] != "|")
                list.append(tokens[row][word]);
        }
    }

    for(int wordLeft = 0; wordLeft < list.length() - 1; wordLeft++)
    {
        for(int wordRight = wordLeft + 1; wordRight < list.length(); wordRight++)
        {
            if(list[wordLeft] == list[wordRight])
                list.remove(wordRight--);
        }
    }
    list.remove(list.indexOf("->"));
    _terminals = list;

    for(int row = 0; row <_terminals.length() + 1; row++)
    {
        _recedenceMat.append(QList<QString>());
        for(int column = 0; column < _terminals.length() + 1; column++)
            _recedenceMat[row].append("");
    }

    for(int terminalRow = 0; terminalRow < _terminals.length(); terminalRow++)
    {
        for(int row = 0; row < _tokens.length(); row++)
        {
            for(int word = 0; word < _tokens[row].length(); word++)
            {
                if(_tokens[row][word] == _terminals[terminalRow])
                {
                    // Проверка на основание рядом
                    if(word + 1 < _tokens[row].length())
                    {
                        if(find(_nonTerm, _tokens[row][word + 1]) == -1 && _tokens[row][word + 1] != "|")
                            _recedenceMat[terminalRow][findTerminalIndex(_tokens[row][word + 1])] = "=.";
                    }

                    // Проверка на основание через нетерминал
                    if(word + 2 < _tokens[row].length())
                    {
                        if(find(_nonTerm, _tokens[row][word + 1]) >= 0 && find(_nonTerm, _tokens[row][word + 2]) == -1 && _tokens[row][word + 2] != "|")
                            _recedenceMat[terminalRow][findTerminalIndex(_tokens[row][word + 2])] = "=.";
                    }

                    //Проверка в столбик; Следование; ">."; T(R)
                    if(word >= 1)
                    {
                        int nonTermPos = find(_nonTerm, _tokens[row][word - 1]);
                        if(nonTermPos >= 0 && _tokens[row][word] != "|")
                        {
                            for(int terminal = 0; terminal < _term[nonTermPos].getRight().length(); terminal++)
                            {
                                if(_recedenceMat[findTerminalIndex(_term[nonTermPos].getRight()[terminal])][terminalRow] != ">.")
                                    _recedenceMat[findTerminalIndex(_term[nonTermPos].getRight()[terminal])][terminalRow] += ">.";
                            }
                        }
                    }

                    //Проверка в строку; Предшествование; "<."; T(L)
                    if(word + 1 < _tokens[row].length())
                    {
                        int nonTermPos = find(_nonTerm, _tokens[row][word + 1]);
                        if(nonTermPos >= 0 && _tokens[row][word] != "|")
                        {
                            for(int terminal = 0; terminal < _term[nonTermPos].getLeft().length(); terminal++)
                            {
                                if(_recedenceMat[terminalRow][findTerminalIndex(_term[nonTermPos].getLeft()[terminal])] != "<.")
                                    _recedenceMat[terminalRow][findTerminalIndex(_term[nonTermPos].getLeft()[terminal])] += "<.";
                            }
                        }
                    }

                    //Символ начала; "<."; T(L)
                    for(int terminal = 0; terminal < _term[0].getLeft().length(); terminal++)
                    {
                        if(_recedenceMat[_terminals.length()][findTerminalIndex(_term[0].getLeft()[terminal])] != "<.")
                            _recedenceMat[_terminals.length()][findTerminalIndex(_term[0].getLeft()[terminal])] += "<.";
                    }

                    //Символ конца; ">."; T(R)
                    for(int terminal = 0; terminal < _term[0].getRight().length(); terminal++)
                    {
                        if(_recedenceMat[findTerminalIndex(_term[0].getRight()[terminal])][_terminals.length()] != ">.")
                            _recedenceMat[findTerminalIndex(_term[0].getRight()[terminal])][_terminals.length()] += ">.";
                    }
                }
            }
        }


    }

}

QList<QStringList> Recedence::parseLanguage()
{
    QStringList list = _formalLang.split('\n');

    QList<QStringList> tokens;
    for(int i = 0; i < list.length(); i++)
        tokens.append(list[i].split(' '));

    _tokens = tokens;
    return tokens;
}

int Recedence::findTerminalIndex(QString terminal)
{
    for(int i = 0; i < _terminals.length(); i++)
        if(_terminals[i] == terminal) return i;
    return -1;
}

QPair<int, int> Recedence::findTerminal(QString terminal)
{
    for(int row = 0; row < _tokens.length(); row++)
    {
        for(int word = 0; word < _tokens[row].length(); word++)
        {
            if(_tokens[row][word] == terminal)
                return {row, word};
        }
    }
    return {-1, -1};
}
