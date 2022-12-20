#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./LexicalAnalysis/lexicalwindow.h"
#include "./SyntacticAnalysis/syntacticwindow.h"
#include "./SemanticAnalysis/semanticanal.h"
#include "errorhandler.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();
    void sendCodeText();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    LexicalWindow *lexicalwindow;
    SyntacticWindow *syntacticwindow;
    ErrorHandler *_errorHandler;

    QTime *time;

    void buildOutput(QString text);

};
#endif // MAINWINDOW_H
