#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lexicalwindow = new LexicalWindow();
    connect(lexicalwindow, SIGNAL(requestData()),
            this, SLOT(sendCodeText()));

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

