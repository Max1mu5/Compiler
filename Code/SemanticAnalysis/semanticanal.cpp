#include "semanticanal.h"

#include <QDebug>


void SemanticAnal::startSemantic()
{
    visitor(_root);
}

void SemanticAnal::visitor(AstNode *currentNode)
{
    switch (currentNode->nodeId)
    {
    case COMMAND_CHAIN_NODE:
    {
        CommandChain *chain = dynamic_cast<CommandChain*>(currentNode);
        visitor(chain->leftNode);
        visitor(chain->rightNode);
    }
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
    case FOR_OP_NODE:
    {
        ForOp* forOp = dynamic_cast<ForOp*>(currentNode);
        visitor(forOp->body);
        break;
    }
    case IF_OP:
    {
        IfOp* ifOp = dynamic_cast<IfOp*>(currentNode);
        visitor(ifOp->body);
        break;
    }
    case IF_ELSE_OP:
    {
        IfElseOp* ifElseOp = dynamic_cast<IfElseOp*>(currentNode);
        visitor(ifElseOp->bodyTrue);
        visitor(ifElseOp->bodyFalse);
        break;
    }
    case IF_ELSEIF_ELSE_NODE:
    {
        IfElseifElse* ifElseifElseOp = dynamic_cast<IfElseifElse*>(currentNode);
        visitor(ifElseifElseOp->firstBodyTrue);
        visitor(ifElseifElseOp->secondBodyTrue);
        visitor(ifElseifElseOp->bodyFalse);
        break;
    }
    }
}

void SemanticAnal::expVisitor(AstNode *currentNode, QList<AstNode *> &types)
{
    switch (currentNode->nodeId)
    {
    case VAR_NAME_NODE:
    {
        if(!isDeclared(currentNode))
        {
            qDebug() << "Var doesn't declared";
            break;
        }

        types.append(getVarType(dynamic_cast<VarName*>(currentNode)));
        break;
    }
    case VAL_BOOL_NODE:
    {
        types.append(new VarType("BOOL"));
        break;
    }
    case VAL_FLOAT_NODE:
    {
        types.append(new VarType("FLOAT"));
        break;
    }
    case VAL_INT_NODE:
    {
        types.append(new VarType("INT"));
        break;
    }
    case MATH_EXP_NODE:
    {
        MathExp* mathExp = dynamic_cast<MathExp*>(currentNode);
        if(mathExp->op == "/")
            types.append(new VarType("FLOAT"));

        expVisitor(mathExp->leftExp, types);
        expVisitor(mathExp->rightExp, types);
    }
    }
}

bool SemanticAnal::isTypeMatching(AstNode *varAsmnNode)
{
    VarAsmt *varAsmt = dynamic_cast<VarAsmt*>(varAsmnNode);
    VarName *var = dynamic_cast<VarName*>(varAsmt->var);

    if(!isDeclared(var))
    {
        qDebug() << "Var doesn't declared";
    }

    VarType *varType = getVarType(var);

    QList<AstNode *>types;
    expVisitor(varAsmt->exp, types);
    QString resultType = "";
    for(auto itTypes : types)
    {
        VarType *itVarType = dynamic_cast<VarType*>(itTypes);
        if(itVarType->type == "FLOAT")
        {
            resultType = "FLOAT";
            break;
        }
        if(itVarType->type == "INT")
        {
            resultType = "INT";
        }
    }
    if(resultType == varType->type)
        return true;
    else
        return false;

}

bool SemanticAnal::isDeclared(AstNode *varNameNode)
{
    for(auto itDeclaredVariables : _declaredVariables)
    {
        Var *varDeclared = dynamic_cast<Var*>(itDeclaredVariables);
        VarName *varNameDeclared = dynamic_cast<VarName*>(varDeclared->varName);
        VarName *varName = dynamic_cast<VarName*>(varNameNode);
        if(varNameDeclared->name == varName->name)
        {
            return true;
        }
    }
    return false;
}

VarType *SemanticAnal::getVarType(VarName *varName)
{
    for(auto itDeclaredVariables : _declaredVariables)
    {
        Var *varDeclared = dynamic_cast<Var*>(itDeclaredVariables);
        VarName *varNameDeclared = dynamic_cast<VarName*>(varDeclared->varName);
        if(varNameDeclared->name == varName->name)
        {
            VarType *varType = dynamic_cast<VarType*>(varDeclared->type);
            return varType;
        }
    }
    return nullptr;
}

