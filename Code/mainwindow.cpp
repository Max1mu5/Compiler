#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lexicalwindow = new LexicalWindow();
    syntacticwindow = new SyntacticWindow();
    time = new QTime();
    _errorHandler = new ErrorHandler(ui->tabWidget->widget(0)->findChild<QTextEdit*>("textEdit_buildOutput"));


    connect(lexicalwindow, &LexicalWindow::requestData,
            this, &MainWindow::sendCodeText);

    //connect(syntacticwindow->syntAnal, &SyntAnal::emitError,
          //  _errorHandler, &ErrorHandler::printError);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    lexicalwindow->show();
}


void MainWindow::sendCodeText()
{
    lexicalwindow->recieveData(ui->codeEdit->toPlainText());
}


void MainWindow::on_action_2_triggered()
{
    syntacticwindow->show();
}


void MainWindow::on_action_3_triggered()
{
    buildOutput("Начало компиляции");

    buildOutput("Запускается лексический анализ");
    lexicalwindow->recieveData(ui->codeEdit->toPlainText());

    buildOutput("Запускается синтаксический анализ");
    syntacticwindow->startSyntacticAnalysis(ui->codeEdit->toPlainText(),
                                            lexicalwindow->getNumTokens(),
                                            QList<QStringList>{lexicalwindow->getTerminals(),
                                                               lexicalwindow->getSeparators(),
                                                               lexicalwindow->getIdentifiers(),
                                                               lexicalwindow->getConstants()});


    buildOutput("Завершение компиляции");
}

void MainWindow::buildOutput(QString text)
{
    QTextEdit *buildOutput = ui->tabWidget->widget(0)->findChild<QTextEdit*>("textEdit_buildOutput");
    buildOutput->append("[" + time->currentTime().toString("hh:mm:ss") + "]: " + text);
}

