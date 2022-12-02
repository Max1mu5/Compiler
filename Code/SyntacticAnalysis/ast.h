#ifndef AST_H
#define AST_H

#include <QList>

enum nodeTypes
{
    PROGRAMM_END,
    COMMAND = 1,
    VAR_DECL = 6,
    VAR_ENUMERATION = 10,
    VAR_ASSIGNMENT = 19,
    MATH_EXP_ADD = 21,
    MATH_EXP_SUB,
    MATH_EXP_MUL,
    MATH_EXP_DIV,
    COND_EXP_MORE,
    COND_EXP_LESS,
    COND_EXP_EQ,
    VAR_NAME,
    IF_ELSE_ELSEIF_OP,
    IF_ELSE_OP,
    IF_OP,
    FOR_OP,
    FOR_STEP_COND,
    FOR_COND,
    WHILE_OP,
    READ_OP,
    WRITE_OP
};

class AstNode;

class Ast
{
public:
    Ast();
    void parse(int Op, QString token);

private:
    QList<AstNode*> _nodeStack;
    QList<AstNode*> _context;
};

class AstNode
{

};

class VarDecl : public AstNode
{
public:
    QString varName;
    QString type;

    VarDecl(QString varName, QString type) : varName(varName), type(type) {}
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
    QList<VarDecl> l;

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
