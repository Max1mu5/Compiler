#ifndef SYNTACTICWINDOW_H
#define SYNTACTICWINDOW_H

#include <QWidget>

#include "recedence.h"

namespace Ui { class SyntacticWindow; }


class SyntacticWindow : public QWidget
{
    Q_OBJECT

public:
    SyntacticWindow(QWidget *parent = nullptr);
    ~SyntacticWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SyntacticWindow *ui;
    Recedence *recedenceMat;

};
#endif // SYNTACTICWINDOW_H
