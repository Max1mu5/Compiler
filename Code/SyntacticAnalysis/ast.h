#ifndef AST_H
#define AST_H

#include <QList>

enum convolutionRule
{
    PROGRAMM_END,
    #include "enumExpressions.inc"
};

enum nodeType
{
    COMMAND_CHAIN_NODE = 1,
    VAR_DECL_NODE = 8,
    VAR_NAME_NODE = 30,
    VAR_TYPE_NODE = 7,
    VAL_BOOL_NODE = 11,
    VAL_FLOAT_NODE = 9,
    VAL_INT_NODE = 10,
    VAR_ENUMERATION_NODE = 12,
    MATH_EXP_NODE = 23,
    COND_EXP_NODE = 27,
    FOR_EXP_COND_NODE = 38,
    FOR_STEP_EXP_COND_NODE = 37,
    FOR_OP_NODE = 35,
    WHILE_OP_NODE = 39,
    IF_OP_NODE = 34,
    IF_ELSE_OP_NODE = 33,
    IF_ELSEIF_ELSE_NODE = 32,
    VAR_ASMT_NODE = 21,
    READ_OP_NODE = 40,
    WRITE_OP_NODE = 41
};

class AstNode;

class Ast
{
public:
    Ast() {};
    Ast(QList<QStringList> tokens);
    void parse(int Op, QPair<int, int> token);
    QString printedNodes();
    AstNode *root;

private:
    QList<AstNode*> _nodeStack;
    QList<AstNode*> _context;
    QList<QStringList> _numTokens;
};

class AstNode
{
public:
    int nodeId;
    AstNode(int id) : nodeId(id) {}
    virtual ~AstNode() = default;
    virtual QString printNode(int callLevel = 0)
    {
        return "ERROR HERE";
    };
protected:
    QString moveCursor(int count)
    {
        QString space = "";
        for(int i = 0; i < count; i++) space += "\t";
        return space;
    }
};

class CommandChain : public AstNode
{
public:
    AstNode *leftNode;
    AstNode *rightNode;

    CommandChain(AstNode *leftNode, AstNode *rightNode) : AstNode(1), leftNode(leftNode), rightNode(rightNode) {}
    QString printNode(int callLevel = 0)
    {
        int newPos = callLevel;
        if(callLevel >= 1) newPos -= 1;
        return  moveCursor(newPos) + "COMMAND_CHAIN\n"
                    + leftNode->printNode(newPos + 1)
                    + rightNode->printNode(newPos + 1);
    }
};

class Var : public AstNode
{
public:
    AstNode *varName;
    AstNode *type;

    Var(AstNode *varName, AstNode *type) : AstNode(8), varName(varName), type(type) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAR_DECLARATION\n"
                    + varName->printNode(callLevel + 1)
                    + type->printNode(callLevel + 1);
    }
};

class VarName : public AstNode
{
public:
    QString name;
    VarName(QString varName) : AstNode(30), name(varName) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAR_NAME\n"
                    + moveCursor(callLevel + 1) + name + "\n";
    }
};

class VarType : public AstNode
{
public:
    QString type;

    VarType(QString type) : AstNode(7), type(type) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAR_TYPE\n"
                    + moveCursor(callLevel + 1) + type + "\n";
    }
};

class ValBool : public AstNode
{
public:
    bool value;

    ValBool(bool value) : AstNode(11), value(value) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAL_BOOL\n"
                    + moveCursor(callLevel + 1) + QString::number(value) + "\n";
    }
};

class ValFloat : public AstNode
{
public:
    float value;

    ValFloat(float value) : AstNode(9), value(value) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAL_FLOAT\n"
                    + moveCursor(callLevel + 1) + QString::number(value) + "\n";
    }
};

class ValInt : public AstNode
{
public:
    int value;

    ValInt(int value) : AstNode(10), value(value) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAL_INT\n"
                    + moveCursor(callLevel + 1) + QString::number(value) + "\n";
    }
};

class VarEnumeration : public AstNode
{
public:
    AstNode *prev;
    AstNode *next;

    VarEnumeration(AstNode *prev, AstNode *next) : AstNode(12), prev(prev), next(next) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAR_ENUMERATION\n"
                    + prev->printNode(callLevel + 1)
                    + next->printNode(callLevel + 1);
    }
};

class MathExp : public AstNode
{
public:
    QString op;
    AstNode *leftExp;
    AstNode *rightExp;

    MathExp(QString op, AstNode *leftExp, AstNode *rightExp) : AstNode(23), op(op), leftExp(leftExp), rightExp(rightExp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "MATH_EXP " + op + "\n"
                    + leftExp->printNode(callLevel + 1)
                    + rightExp->printNode(callLevel + 1);
    }
};

class CondExp : public AstNode
{
public:
    QString op;
    AstNode *leftExp;
    AstNode *rightExp;

    CondExp(QString op, AstNode *leftExp, AstNode *rightExp) : AstNode(27), op(op), leftExp(leftExp), rightExp(rightExp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "COND_EXP " + op + "\n"
                    + leftExp->printNode(callLevel + 1)
                    + rightExp->printNode(callLevel + 1);
    }
};

class ForExpCond : public AstNode
{
public:
    AstNode *leftExp;
    AstNode *rightExp;

    ForExpCond(AstNode *leftExp, AstNode *rightExp) : AstNode(38), leftExp(leftExp), rightExp(rightExp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "FOR_COND_EXP\n"
                    + leftExp->printNode(callLevel + 1)
                    + rightExp->printNode(callLevel + 1);
    }
};

class ForStepExpCond : public AstNode
{
public:
    AstNode *step;
    AstNode *leftExp;
    AstNode *rightExp;

    ForStepExpCond(AstNode *step, AstNode *leftExp, AstNode *rightExp) : AstNode(37), step(step), leftExp(leftExp), rightExp(rightExp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "FOR_STEP_COND_EXP\n"
                    + step->printNode(callLevel + 1)
                    + leftExp->printNode(callLevel + 1)
                    + rightExp->printNode(callLevel + 1);
    }
};

class ForOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    ForOp(AstNode *cond, AstNode *body) : AstNode(35), cond(cond), body(body) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "FOR_OPERATOR\n"
                    + cond->printNode(callLevel + 1)
                    + body->printNode(callLevel + 1);
    }
};

class WhileOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    WhileOp(AstNode *cond, AstNode *body) : AstNode(39), cond(cond), body(body) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "WHILE_OPERATOR\n"
                    + cond->printNode(callLevel + 1)
                    + body->printNode(callLevel + 1);
    }
};

class IfOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    IfOp(AstNode *cond, AstNode *body) : AstNode(34), cond(cond), body(body) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "IF_OPERATOR\n"
                    + cond->printNode(callLevel + 1)
                    + moveCursor(callLevel + 1) + "TRUE_STATEMENT\n"
                    + body->printNode(callLevel + 2);
    }
};

class IfElseOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *bodyTrue;
    AstNode *bodyFalse;

    IfElseOp(AstNode *cond, AstNode *bodyTrue, AstNode *bodyFalse) :  AstNode(33), cond(cond), bodyTrue(bodyTrue), bodyFalse(bodyFalse) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "IF_ELSE_OPERATOR\n"
                    + cond->printNode(callLevel + 1)
                    + moveCursor(callLevel + 1) + "TRUE_STATEMENT\n"
                    + bodyTrue->printNode(callLevel + 2)
                    + moveCursor(callLevel + 1) + "FALSE_STATEMENT\n"
                    + bodyFalse->printNode(callLevel + 2);
    }
};

class IfElseifElse : public AstNode
{
public:
    AstNode *firstCond;
    AstNode *firstBodyTrue;

    AstNode *secondCond;
    AstNode *secondBodyTrue;

    AstNode *bodyFalse;

    IfElseifElse(AstNode *firstCond, AstNode *firstBodyTrue,
                 AstNode *secondCond, AstNode *secondBodyTrue,
                 AstNode *bodyFalse) :  AstNode(32), firstCond(firstCond), firstBodyTrue(firstBodyTrue),
                                       secondCond(secondCond), secondBodyTrue(secondBodyTrue),
                                       bodyFalse(bodyFalse) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "IF_ESLEIF_ELSE_OPERATOR\n"
                    + moveCursor(callLevel + 1) + "FIRST_COND\n"
                    + firstCond->printNode(callLevel + 2)

                    + moveCursor(callLevel + 1) + "FISRT_TRUE_STATEMENT\n"
                    + firstBodyTrue->printNode(callLevel + 2)

                    + moveCursor(callLevel + 1) + "SECOND_COND\n"
                    + secondCond->printNode(callLevel + 2)

                    + moveCursor(callLevel + 1) + "SECOND_TRUE_STATEMENT\n"
                    + secondBodyTrue->printNode(callLevel + 2)

                    + moveCursor(callLevel + 1) + "FALSE_STATEMENT\n"
                    + bodyFalse->printNode(callLevel + 2);
    }
};

class VarAsmt : public AstNode
{
public:
    AstNode *var;
    AstNode *exp;

    VarAsmt(AstNode *var, AstNode *exp) :  AstNode(21), var(var), exp(exp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "VAR_ASSIGMENT\n"
                    + var->printNode(callLevel + 1)
                    + exp->printNode(callLevel + 1);
    }
};

class ReadOp : public AstNode
{
public:
    AstNode *exp;

    ReadOp(AstNode *exp) :  AstNode(40), exp(exp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "READ_OPERATOR\n"
                    + exp->printNode(callLevel + 1);
    }
};

class WriteOp : public AstNode
{
public:
    AstNode *exp;

    WriteOp(AstNode *exp) :  AstNode(41), exp(exp) {}
    QString printNode(int callLevel = 0)
    {
        return  moveCursor(callLevel) + "WRITE_OPERATOR\n"
                    + exp->printNode(callLevel + 1);
    }
};


#endif // AST_H
