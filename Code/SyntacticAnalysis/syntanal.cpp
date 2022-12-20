#include "syntanal.h"

#include <QDebug>

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

#include <QFile>

AstNode* SyntAnal::getAst()
{
    return _ast->root;
}


void SyntAnal::startSyntAnal()
{
    _ast = new Ast(_tokens);
    parseCode();
    parseFormalLang();


    _terminals.append("@entryEndPoint@");
    //_terminals.append("@endPoint@");
    _tokens[0].append("@entryEndPoint@");
    _numTokens.append({0, _tokens[0].length() - 1});
    _stack.append("@entryEndPoint@");
    QList<QPair<int, int>>::Iterator itNumTokens = _numTokens.begin();


    while (itNumTokens != _numTokens.end())
    {
        int firstTerminalPos = getTerminalIndex(_stack[findFirstTerm(0)]); // Ищем первый терминал в стеке
        int nextToken = getTerminalIndex(_tokens[itNumTokens->first][itNumTokens->second]);

        if(firstTerminalPos == _terminals.length() - 1 &&
                nextToken == _terminals.length() - 1)
        {
            qDebug() << "No syntactical error";
            //qDebug() <<_ast->printedNodes();
            QFile data("output.txt");
            if (data.open(QFile::WriteOnly | QFile::Truncate)) {
                QTextStream out(&data);
                out << _ast->printedNodes();
                // writes "Result: 3.14      2.7       "
            }
            return;
        }

        QString recedenceStatus = _recedenceMat[firstTerminalPos][nextToken];

        if(recedenceStatus.isEmpty())
        {
            qDebug() << ("Syntactical error between: " +
                      _terminals[firstTerminalPos] + " и " + _terminals[nextToken]);
            return;
        }

        if(recedenceStatus == "=." || recedenceStatus == "<.")
        {
            _stack.append(_tokens[itNumTokens->first][itNumTokens->second]);
            itNumTokens++;
            continue;
        }

        if(recedenceStatus == ">.")
        {
            QString chain = "";
            //int tempTerm = 0;
            int leftTermStackIndex = findFirstTerm(0);
            int rightTermStackIndex = findFirstTerm(_stack.length() - leftTermStackIndex);
            while(leftTermStackIndex != -1 && rightTermStackIndex != -1
                  && _recedenceMat[getTerminalIndex(_stack[rightTermStackIndex])][getTerminalIndex(_stack[leftTermStackIndex])] == "=.")
            {
                addNeighbours(&chain, leftTermStackIndex);

                //addNeighbours(&chain, rightTermStackIndex);

                leftTermStackIndex = findFirstTerm(0);
                rightTermStackIndex = findFirstTerm(_stack.length() - leftTermStackIndex);
            }

            int firstTerminal = findFirstTerm(0);
            addNeighbours(&chain, firstTerminal);

            chain.chop(1);

            if(ruleNumber(chain) >= 0)
            {
                _stack.append("T");
                itNumTokens--;
                //qDebug() << chain;
                _ast->parse(ruleNumber(chain), {itNumTokens->first, itNumTokens->second});
                itNumTokens++;
            }

            else
            {
                qDebug() << ("Syntactical error between: " + _terminals[firstTerminalPos] + " и " + _terminals[nextToken]);
                return;
            }

        }
    }
}

int SyntAnal::ruleNumber(QString chain)
{
    int ruleCounter = 0;
    for(int i = 0; i < _formalLangRules.length(); i++)
    {
        for(int j = 0; j < _formalLangRules[i].length(); j++)
        {
            if(chain == _formalLangRules[i][j])
                return ruleCounter;
            ruleCounter++;
        }
    }
    return -1;
}

void SyntAnal::addNeighbours(QString *chain, int pos)
{
    if(pos + 1 < _stack.length() && getTerminalIndex(_stack[pos + 1]) == -1)
    {
        chain->push_front(_stack[pos + 1] + " " );
        _stack.remove(pos + 1);
    }
    chain->push_front(_stack[pos] + " ");
    _stack.remove(pos);
    if(pos - 1 < _stack.length() && pos - 1 >= 0
            && getTerminalIndex(_stack[pos - 1]) == -1)
    {
        chain->push_front(_stack[pos - 1] + " ");
        _stack.remove(pos - 1);
    }
}

int SyntAnal::findFirstTerm(int startPos)
{
    for(int i = _stack.length() - 1 - startPos; i >= 0; i--)
    {
        if(getTerminalIndex(_stack[i]) >= 0)
            return i;
    }
    return -1;
}

int SyntAnal::getTerminalIndex(QString term)
{
    for(int i = 0; i < _terminals.length(); i++)
    {
        if(_terminals[i] == term)
            return i;
    }
    return -1;
}

void SyntAnal::parseCode()
{
    for(int i = 0; i < _tokens[2].length(); i++)
    {
        _tokens[2][i] = "ind";
    }
    for(int i = 0; i < _tokens[3].length(); i++)
    {
        _tokens[3][i] = "const";
    }
    for(int i = 0; i < _tokens[1].length(); i++)
    {
        if(_tokens[1][i] == "\n")
            _tokens[1][i] = "newLine";
    }
    for(int i = 0; i < _terminals.length(); i++)
    {
        if(_terminals[i] == "\\n")
            _terminals[i] = "newLine";
    }

    for(int i = 0; i < _numTokens.length() - 1; i++)
    {
        if(_numTokens[i] == _numTokens[i+1]
                && ( _tokens[_numTokens[i].first][_numTokens[i].second] == "newLine"
                || _tokens[_numTokens[i].first][_numTokens[i].second] == ";"))
                _numTokens.remove(i);
    }

}

void SyntAnal::parseFormalLang()
{
    _formalLang.replace("\\n", "newLine");
    QStringList tempFormalLang = _formalLang.split("\n");
    QList<QStringList> tempFormalLangTokens;
    for(int i = tempFormalLang.length() - 1; i >= 0; i--)
    {
        tempFormalLangTokens.append(tempFormalLang[i].split(" "));

        _formalLang.replace(tempFormalLangTokens[tempFormalLang.length() - 1 - i][0], "T");
    }

    tempFormalLang = _formalLang.split("\n");
    for(int i = 0; i < tempFormalLang.length(); i++)
    {
        //_formalLangRules
        tempFormalLang[i].remove(0, 4);
        _formalLangRules.append(tempFormalLang[i].split("|"));
        for(int j = 0 ; j < _formalLangRules[i].length(); j++)
        {
            _formalLangRules[i][j] = _formalLangRules[i][j].trimmed();
        }
    }


}


