#include "semanticanal.h"

#include <QDebug>


void SemanticAnal::startSemantic()
{

}

void SemanticAnal::visitor(AstNode *currentNode)
{
    switch (currentNode->nodeId)
    {
    case VAR_NODE:
    {
        _declaredVariables.push_back(currentNode);
        break;
    }
    case VAR_ASMT_NODE:
    {
        if(!isTypeMatching(currentNode))
        {
            qDebug() << "Type doesn't match";
            return;
        }
        break;
    }
    case VAR_NAME_NODE:
    {
        if(!isDeclared(currentNode))
        {
            qDebug() << "Var doesn't declared";
            return;
        }
        break;
    }
    }
}

bool SemanticAnal::isTypeMatching(AstNode *varAsmnNode)
{

}

bool SemanticAnal::isDeclared(AstNode *varNameNode)
{
    for(auto itDeclaredVariables : _declaredVariables)
    {
        if(itDeclaredVariables == varNameNode)
        {
            return true;
        }
    }
    return false;
}

