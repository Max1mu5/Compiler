#ifndef SYNTACTICWINDOW_H
#define SYNTACTICWINDOW_H

#include <QWidget>

#include "recedence.h"
#include "syntanal.h"

#include "errorhandler.h"

namespace Ui { class SyntacticWindow; }


class SyntacticWindow : public QWidget
{
    Q_OBJECT

public:
    SyntacticWindow(QWidget *parent = nullptr);
    ~SyntacticWindow();
    void startSyntacticAnalysis(QString code,
                                QList<QPair<int, int>> numTokens,
                                QList<QStringList> tokens);

    SyntAnal *syntAnal;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SyntacticWindow *ui;
    Recedence *recedenceMat;

};
#endif // SYNTACTICWINDOW_H
