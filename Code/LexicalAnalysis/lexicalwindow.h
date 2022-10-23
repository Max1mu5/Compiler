#ifndef LEXICALWINDOW_H
#define LEXICALWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class LexicalWindow;
}

class LexicalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LexicalWindow(QWidget *parent = nullptr);
    ~LexicalWindow();
    void recieveData(QString codeText);
    QStringList getTableValues(QTableWidget *tw);
    QList<QPair<int, int>> getNumTokens();
    QStringList getTerminals();
    QStringList getSeparators();
    QStringList getIdentifiers();
    QStringList getConstants();




private slots:
    void on_startLexicalAnalyze_clicked();

signals:
    void requestData();

private:
    Ui::LexicalWindow *ui;
    QString _codeText;
    QList<QPair<int, int>> _numTokens;

    QHash<QString, int> _terminals;
    QHash<QString, int> _separators;

    QString tokensToText();
    void lexicalAnalyze();
    void clearComments();
    QString getCodeText();

    bool isTerminal(QString str);
    bool isSeparator(QString str);
    bool isNum(QString str);
    QString itemName(QHash<QString, int> *hash, int pos);
    void insertItem(QTableWidget *tw, QString str);

    void setCodeText(QString code);

};

#endif // LEXICALWINDOW_H
