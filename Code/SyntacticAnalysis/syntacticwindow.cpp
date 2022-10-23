#include "syntacticwindow.h"
#include "ui_syntacticwindow.h"

SyntacticWindow::SyntacticWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SyntacticWindow)
{
    ui->setupUi(this);
    ui->tableNonTerm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableTerm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableRecedence->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableNonTerm->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableTerm->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->tableRecedence->verticalHeader()->setVisible(false);
    ui->tableRecedence->horizontalHeader()->setVisible(false);

}

SyntacticWindow::~SyntacticWindow()
{
    delete ui;
}

void SyntacticWindow::startSyntacticAnalysis(QString code,
                                             QList<QPair<int, int>> numTokens,
                                             QList<QStringList> tokens)
{
    on_pushButton_clicked();
    syntAnal = new SyntAnal(code, recedenceMat->getTerminals(),
                            recedenceMat->getRecedenceMat(), numTokens,
                            tokens, recedenceMat->getFormalLang());
    syntAnal->startSyntAnal();
}


void SyntacticWindow::on_pushButton_clicked()
{
    recedenceMat = new Recedence();
    ui->tableNonTerm->setRowCount(0);
    ui->tableRecedence->setRowCount(0);
    ui->tableTerm->setRowCount(0);

    recedenceMat->constructRecedenceTable(ui->textEdit->toPlainText());

    QList<RecedenceItem> nonTerm = recedenceMat->getNonTerm();
    for(int i = 0; i < nonTerm.length(); i++)
    {
        ui->tableNonTerm->setRowCount(ui->tableNonTerm->rowCount() + 1);
        ui->tableNonTerm->setItem(ui->tableNonTerm->rowCount()-1,
                                 0,
                                 new QTableWidgetItem(nonTerm[i].getName()));
        ui->tableNonTerm->setItem(ui->tableNonTerm->rowCount()-1,
                                 1,
                                 new QTableWidgetItem(nonTerm[i].getLeftToStr()));
        ui->tableNonTerm->setItem(ui->tableNonTerm->rowCount()-1,
                                 2,
                                 new QTableWidgetItem(nonTerm[i].getRightToStr()));
    }

    QList<RecedenceItem> term = recedenceMat->getTerm();
    for(int i = 0; i < term.length(); i++)
    {
        ui->tableTerm->setRowCount(ui->tableTerm->rowCount() + 1);
        ui->tableTerm->setItem(ui->tableTerm->rowCount()-1,
                               0,
                               new QTableWidgetItem(term[i].getName()));
        ui->tableTerm->setItem(ui->tableTerm->rowCount()-1,
                               1,
                               new QTableWidgetItem(term[i].getLeftToStr()));
        ui->tableTerm->setItem(ui->tableTerm->rowCount()-1,
                               2,
                               new QTableWidgetItem(term[i].getRightToStr()));
    }

    QStringList list = recedenceMat->getTerminals();
    ui->tableRecedence->setRowCount(list.length() + 2);
    ui->tableRecedence->setColumnCount(list.length() + 2);
    ui->tableRecedence->setItem(0, 0, new QTableWidgetItem("Символы"));
    for(int i = 1; i < list.length()+1; i++)
    {
        ui->tableRecedence->setItem(0, i, new QTableWidgetItem(list[i-1]));
        ui->tableRecedence->setItem(i, 0, new QTableWidgetItem(list[i-1]));
    }

    ui->tableRecedence->setItem(ui->tableRecedence->rowCount()-1,
                                0,
                                new QTableWidgetItem("BEGIN"));
    ui->tableRecedence->setItem(0,
                                ui->tableRecedence->rowCount()-1,
                                new QTableWidgetItem("END"));

    QList<QList<QString>> matrix = recedenceMat->getRecedenceMat();
    for(int row = 0; row < matrix.length(); row++)
    {
        for(int column = 0; column < matrix[row].length(); column++)
        {
            ui->tableRecedence->setItem(row + 1,
                                        column + 1,
                                        new QTableWidgetItem(matrix[row][column]));
        }
    }

}

