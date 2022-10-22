#ifndef RECEDENCEITEM_H
#define RECEDENCEITEM_H

#include <QString>
#include <QStringList>

class RecedenceItem
{
public:
    RecedenceItem();

    void appendLeft(QString str);
    void appendRight(QString str);
    void setName(QString name);
    QString getName();
    QStringList& getLeft();
    QStringList& getRight();
    QString getLeftToStr();
    QString getRightToStr();



private:
    QString _nameTerm;
    QStringList _left;
    QStringList _right;




};

#endif // RECEDENCEITEM_H
