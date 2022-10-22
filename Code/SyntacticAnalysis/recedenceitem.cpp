#include "recedenceitem.h"

RecedenceItem::RecedenceItem()
{

}

void RecedenceItem::appendLeft(QString str)
{
    for(int i = 0; i < _left.length(); i++)
        if(_left[i] == str) return;

    _left.append(str);
}

void RecedenceItem::appendRight(QString str)
{
    for(int i = 0; i < _right.length(); i++)
        if(_right[i] == str) return;

    _right.append(str);
}

void RecedenceItem::setName(QString name)
{
    _nameTerm = name;
}

QString RecedenceItem::getName()
{
    return _nameTerm;
}

QStringList& RecedenceItem::getLeft()
{
    return _left;
}

QStringList& RecedenceItem::getRight()
{
    return _right;
}

QString RecedenceItem::getLeftToStr()
{
    QString temp = "";
    for(int i = 0; i < _left.length(); i++)
    {
        temp += _left[i] + " ";
    }
    return temp;
}

QString RecedenceItem::getRightToStr()
{
    QString temp = "";
    for(int i = 0; i < _right.length(); i++)
    {
        temp += _right[i] + " ";
    }
    return temp;
}

