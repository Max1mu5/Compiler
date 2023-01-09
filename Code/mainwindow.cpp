#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QProcess>


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

    QTextCursor cursor = ui->codeEdit->textCursor();
    ui->codeEdit->selectAll();
    ui->codeEdit->setFontPointSize(12);
    ui->codeEdit->setTextCursor( cursor );

    cursor = ui->ABSTree->textCursor();
    ui->ABSTree->selectAll();
    ui->ABSTree->setFontPointSize(12);
    ui->ABSTree->setTextCursor( cursor );

    cursor = ui->NASMCode->textCursor();
    ui->NASMCode->selectAll();
    ui->NASMCode->setFontPointSize(12);
    ui->NASMCode->setTextCursor( cursor );


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

    buildOutput("Запускается семантический анализ");
    SemanticAnal semanticAnal(syntacticwindow->syntAnal->getAst());
    semanticAnal.startSemantic();

    buildOutput("Запускается генерация кода");
    CodeGenerating codeGenerating(syntacticwindow->syntAnal->getAst(), semanticAnal._declaredVariables);
    codeGenerating.startCodeGenerating();

    on_action_5_triggered();
    on_action_4_triggered();

    buildOutput("Завершение компиляции");

    QTextEdit *buildOutput = ui->tabWidget->widget(1)->findChild<QTextEdit*>("textEdit_programOutput");

    buildOutput->append("[" + time->currentTime().toString("hh:mm:ss") + "]: " + "Запуск программы ...\n");

    QProcess process;
    process.start(".\\bin\\NASM\\nasm", QStringList() << "-f" << "win64" << ".\\CodeGeneration.asm" << "-o" << "CodeGeneration.obj");
    process.waitForFinished();
    QString res = process.readAll();
    buildOutput->append(res);

    process.start(".\\bin\\MinGW64\\bin\\gcc.exe", QStringList() << ".\\CodeGeneration.obj" << ".\\bin\\NASM\\macro64.o" << "-g" << "-o" << "YAY" << "-m64");
    process.waitForFinished();
    res = process.readAll();
    buildOutput->append(res);

    process.start(".\\YAY.exe");
    process.waitForFinished();
    res = process.readAll();
    buildOutput->append(res);
}

void MainWindow::buildOutput(QString text)
{
    QTextEdit *buildOutput = ui->tabWidget->widget(0)->findChild<QTextEdit*>("textEdit_buildOutput");
    buildOutput->append("[" + time->currentTime().toString("hh:mm:ss") + "]: " + text);
}

#include <QFile>
void MainWindow::on_action_5_triggered()
{
    QFile file("output.txt");
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
        return;
    data = file.readAll();

    ui->ABSTree->setText(QString(data));


}


void MainWindow::on_action_4_triggered()
{
    QFile file("CodeGeneration.asm");
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
        return;
    data = file.readAll();

    ui->NASMCode->setText(QString(data));
}


void MainWindow::on_action_6_triggered()
{
    QTextCursor cursor = ui->codeEdit->textCursor();
    ui->codeEdit->selectAll();
    ui->codeEdit->setFontPointSize(12);
    ui->codeEdit->setTextCursor( cursor );

    cursor = ui->ABSTree->textCursor();
    ui->ABSTree->selectAll();
    ui->ABSTree->setFontPointSize(12);
    ui->ABSTree->setTextCursor( cursor );

    cursor = ui->NASMCode->textCursor();
    ui->NASMCode->selectAll();
    ui->NASMCode->setFontPointSize(12);
    ui->NASMCode->setTextCursor( cursor );

    QTextEdit *buildOutput = ui->tabWidget->widget(1)->findChild<QTextEdit*>("textEdit_programOutput");
    cursor = buildOutput->textCursor();
    buildOutput->selectAll();
    buildOutput->setFontPointSize(12);
    buildOutput->setTextCursor( cursor );
}

