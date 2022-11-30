#include "lexicalwindow.h"
#include "ui_lexicalwindow.h"

LexicalWindow::LexicalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LexicalWindow)
{
    ui->setupUi(this);

    ui->terminals->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->separators->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->identifiers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->constants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    _codeText = "";

    _terminals["if"] = -1;
    _terminals["elseif"] = -1;
    _terminals["else"] = -1;
    _terminals["endif"] = -1;
    _terminals["for"] = -1;
    _terminals["step"] = -1;
    _terminals["next"] = -1;
    _terminals["while"] = -1;
    _terminals["loop"] = -1;
    _terminals["readln"] = -1;
    _terminals["writeln"] = -1;
    _terminals["end"] = -1;
    _terminals["!"] = -1;
    _terminals["%"] = -1;
    _terminals["$"] = -1;
    _terminals["to"] = -1;
    _terminals["loop"] = -1;

    _separators[":"] = -1;
    _separators[";"] = -1;
    _separators["+"] = -1;
    _separators["-"] = -1;
    _separators["*"] = -1;
    _separators["/"] = -1;
    _separators[">"] = -1;
    _separators["<"] = -1;
    _separators["="] = -1;
    _separators[","] = -1;
    _separators["("] = -1;
    _separators[")"] = -1;
    _separators[" "] = -1;
    _separators["\n"] = -1;
    _separators[":="] = -1;

}

LexicalWindow::~LexicalWindow()
{
    delete ui;
}

void LexicalWindow::recieveData(QString codeText)
{
    _numTokens = QList<QPair<int, int>>();
//    ui->terminals->clear();
//    ui->constants->clear();
//    ui->identifiers->clear();
//    ui->identifiers->clear();
    ui->terminals->setRowCount(0);
    ui->constants->setRowCount(0);
    ui->identifiers->setRowCount(0);
    ui->separators->setRowCount(0);

    QHashIterator<QString, int> i(_terminals);
    while (i.hasNext())
    {
        i.next();
        _terminals[i.key()] = -1;
    }
    QHashIterator<QString, int> j(_separators);
    while (j.hasNext())
    {
        j.next();
        _separators[j.key()] = -1;
    }
    this->_codeText = codeText;

    _codeText += " ";
    lexicalAnalyze();
    ui->textEdit->setText(tokensToText());
}

QList<QPair<int, int> > LexicalWindow::getNumTokens()
{
    return _numTokens;
}

QStringList LexicalWindow::getTableValues(QTableWidget *tw)
{
    QStringList temp;
    for(int i = 0; i < tw->rowCount(); i++)
    {
        temp.append(tw->item(i, 0)->text());
    }
    return temp;
}

void LexicalWindow::on_startLexicalAnalyze_clicked()
{
    emit requestData();
}

QStringList LexicalWindow::getTerminals()
{
    return getTableValues(ui->terminals);
}

QStringList LexicalWindow::getSeparators()
{
    return getTableValues(ui->separators);
}

QStringList LexicalWindow::getIdentifiers()
{
    return getTableValues(ui->identifiers);
}

QStringList LexicalWindow::getConstants()
{
    return getTableValues(ui->constants);
}

QString LexicalWindow::tokensToText()
{
    QString temp = "";
    for (int i = 0; i < _numTokens.count(); i++)
    {
        temp += "(" + QString::number(_numTokens[i].first) +
                ", " + QString::number(_numTokens[i].second) + ") ";
    }
    return temp;
}

void LexicalWindow::lexicalAnalyze()
{
    clearComments();

    QString buffer = "";
    int pos = 0;
    int unicalSep = 0, unicalTerm = 0;

    while (_codeText.length() != 0)
    {
        if(isSeparator(_codeText[pos]) || isSeparator(QString(_codeText[pos]) + _codeText[pos+1]))
        {
            if(isTerminal(buffer))
            {
                if(_terminals[buffer] == -1)
                {
                    _terminals[buffer] = unicalTerm++;
                    _numTokens.append({0, _terminals[buffer]});
                    insertItem(ui->terminals, buffer);
                }
                else
                    _numTokens.append({0, _terminals[buffer]});
            }
            else if(isNum(buffer))
            {
                if(ui->constants->findItems(buffer, Qt::MatchExactly).count() == 0)
                {
                    _numTokens.append({3, ui->constants->rowCount()});
                    insertItem(ui->constants, buffer);
                }
                else
                {
                    _numTokens.append({3, ui->constants->findItems(buffer, Qt::MatchExactly)[0]->row()});
                }
            }
            else if(ui->identifiers->findItems(buffer, Qt::MatchExactly).count() == 0 && buffer != "")
                {
                    _numTokens.append({2, ui->identifiers->rowCount()});
                    insertItem(ui->identifiers, buffer);
                }
                else if (buffer != "")
                {
                    _numTokens.append({2, ui->identifiers->findItems(buffer, Qt::MatchExactly)[0]->row()});
                }

            if(_codeText.length() - pos > 1 && QString(_codeText[pos]) + _codeText[pos+1] == ":=")
                if(_separators[":="] == -1)
                {
                    _separators[":="] = unicalSep++;
                    _numTokens.append({1, _separators[":="]});
                    insertItem(ui->separators, ":=");
                    pos++;
                }
                else
                {
                    _numTokens.append({1, _separators[":="]});
                    pos++;
                }
            else
                if(_separators[_codeText[pos]] == -1 && _codeText[pos] != ' ')
                {
                    _separators[_codeText[pos]] = unicalSep++;
                    _numTokens.append({1, _separators[_codeText[pos]]});
                    insertItem(ui->separators, _codeText[pos]);
                }
                else if(_codeText[pos] != ' ')
                    _numTokens.append({1, _separators[_codeText[pos]]});

            if(buffer == "end") return;

            buffer = "";
            _codeText = _codeText.mid(pos + 1);
            pos = 0;
        }
        else
            buffer += _codeText[pos++];
    }



}

void LexicalWindow::clearComments()
{
    int pos = _codeText.indexOf("/*");
    while(pos != -1)
    {
        _codeText.remove(pos, _codeText.indexOf("*/") - pos + 2);
        pos = _codeText.indexOf("/*");
    }
}

QString LexicalWindow::getCodeText()
{
    return _codeText;
}

bool LexicalWindow::isTerminal(QString str)
{
    for(int i = 0; i < _terminals.count(); i++)
        if(str == itemName(&_terminals, i))
            return true;

    return false;
}

bool LexicalWindow::isSeparator(QString str)
{
    for(int i = 0; i < _separators.count(); i++)
        if(str == itemName(&_separators, i))
            return true;

    return false;
}

bool LexicalWindow::isNum(QString str)
{
    bool ok;
    str.toDouble(&ok);
    return ok;
}

QString LexicalWindow::itemName(QHash<QString, int> *hash, int pos)
{
    QHash<QString, int>::iterator it = hash->begin();
    for (int i = 0; i < pos; ++i)
        it++;
    return it.key();
}

void LexicalWindow::insertItem(QTableWidget *tw, QString str)
{
    tw->setRowCount(tw->rowCount() + 1);
    tw->setItem(tw->rowCount() - 1, 0, new QTableWidgetItem(str));
}

void LexicalWindow::setCodeText(QString code)
{
    _codeText = code;
}

