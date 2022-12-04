#ifndef AST_H
#define AST_H

#include <QList>

enum nodeTypes
{
    PROGRAMM_END,
    #include "enumExpressions.inc"
};

class AstNode;

class Ast
{
public:
    Ast();
    Ast(QList<QStringList> tokens);
    void parse(int Op, QPair<int, int> token);

private:
    QList<AstNode*> _nodeStack;
    QList<AstNode*> _context;
    QList<QStringList> _numTokens;
};

class AstNode
{
public:
    //int nodeId;
    //AstNode(int id) : nodeId(id) {}
    virtual ~AstNode() = default;
};

class Var : public AstNode
{
public:
    AstNode *varName;
    AstNode *type;

    Var(AstNode *varName, AstNode *type) : varName(varName), type(type) {}
};

class VarName : public AstNode
{
public:
    QString name;
    VarName(QString varName) : name(varName) {}
};

class VarType : public AstNode
{
public:
    QString type;

    VarType(QString type) : type(type) {}
};

class ValBool : public AstNode
{
public:
    bool value;

    ValBool(bool value) : value(value) {}
};

class ValFloat : public AstNode
{
public:
    float value;

    ValFloat(float value) : value(value) {}
};

class ValInt : public AstNode
{
public:
    int value;

    ValInt(int value) : value(value) {}
};

class VarEnumeration : public AstNode
{
public:
    AstNode *prev;
    AstNode *next;

    VarEnumeration(AstNode *prev, AstNode *next) : prev(prev), next(next) {}

};

class MathExp : public AstNode
{
public:
    QString op;
    AstNode *leftExp;
    AstNode *rightExp;

    MathExp(QString op, AstNode *leftExp, AstNode *rightExp) : op(op), leftExp(leftExp), rightExp(rightExp) {}
};

class CondExp : public AstNode
{
public:
    QString op;
    AstNode *leftExp;
    AstNode *rightExp;

    CondExp(QString op, AstNode *leftExp, AstNode *rightExp) : op(op), leftExp(leftExp), rightExp(rightExp) {}
};

class ForExpCond : public AstNode
{
public:
    AstNode *leftExp;
    AstNode *rightExp;

    ForExpCond(AstNode *leftExp, AstNode *rightExp) : leftExp(leftExp), rightExp(rightExp) {}
};

class ForStepExpCond : public AstNode
{
public:
    AstNode *step;
    AstNode *leftExp;
    AstNode *rightExp;

    ForStepExpCond(AstNode *step, AstNode *leftExp, AstNode *rightExp) : step(step), leftExp(leftExp), rightExp(rightExp) {}
};

class ForOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    ForOp(AstNode *cond, AstNode *body) : cond(cond), body(body) {}
};

class WhileOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    WhileOp(AstNode *cond, AstNode *body) : cond(cond), body(body) {}
};

class IfOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *body;

    IfOp(AstNode *cond, AstNode *body) : cond(cond), body(body) {}
};

class IfElseOp : public AstNode
{
public:
    AstNode *cond;
    AstNode *bodyTrue;
    AstNode *bodyFalse;

    IfElseOp(AstNode *cond, AstNode *bodyTrue, AstNode *bodyFalse) : cond(cond), bodyTrue(bodyTrue), bodyFalse(bodyFalse) {}
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
                 AstNode *bodyFalse) : firstCond(firstCond), firstBodyTrue(firstBodyTrue),
                                       secondCond(secondCond), secondBodyTrue(secondBodyTrue),
                                       bodyFalse(bodyFalse) {}
};

class VarAsmt : public AstNode
{
public:
    AstNode *var;
    AstNode *exp;

    VarAsmt(AstNode *var, AstNode *exp) : var(var), exp(exp) {}
};

class ReadOp : public AstNode
{
public:
    AstNode *exp;

    ReadOp(AstNode *exp) : exp(exp) {}
};

class WriteOp : public AstNode
{
public:
    AstNode *exp;

    WriteOp(AstNode *exp) : exp(exp) {}
};


#endif // AST_H
