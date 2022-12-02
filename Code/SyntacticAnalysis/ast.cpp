#include "ast.h"

Ast::Ast()
{

}

void Ast::parse(int Op, QString token)
{
    switch (Op)
    {
    case COMMAND:
    {
        //Возможно нуждна свертка и очистка текущего контекста, запушить в стек ветку, хз пока
    };
    case VAR_DECL:
    {
        QStringList operands = token.split(":");
        VarDecl *var = new VarDecl(operands[0], operands[1]);
        _context.push_back(var);
        break;
    }
    case VAR_ASSIGNMENT:
    {
        AstNode *exp = _context.takeLast();
        AstNode *var = _context.takeLast();
        VarAsmt *varAsmt = new VarAsmt(var, exp);
        _context.push_back(varAsmt);
        break;
    }
    case MATH_EXP_ADD:
    {
        QString op = "+";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        MathExp *mathExp = new MathExp(op, leftExp, rightExp);
        _context.push_back(mathExp);
        break;
    }
    case MATH_EXP_SUB:
    {
        QString op = "+";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        MathExp *mathExp = new MathExp(op, leftExp, rightExp);
        _context.push_back(mathExp);
        break;
    }
    case MATH_EXP_MUL:
    {
        QString op = "+";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        MathExp *mathExp = new MathExp(op, leftExp, rightExp);
        _context.push_back(mathExp);
        break;
    }
    case MATH_EXP_DIV:
    {
        QString op = "+";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        MathExp *mathExp = new MathExp(op, leftExp, rightExp);
        _context.push_back(mathExp);
        break;
    }
    case COND_EXP_MORE:
    {
        QString op = ">";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        CondExp *condExp = new CondExp(op, leftExp, rightExp);
        _context.push_back(condExp);
        break;
    }
    case COND_EXP_LESS:
    {
        QString op = "<";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        CondExp *condExp = new CondExp(op, leftExp, rightExp);
        _context.push_back(condExp);
        break;
    }
    case COND_EXP_EQ:
    {
        QString op = "=";
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        CondExp *condExp = new CondExp(op, leftExp, rightExp);
        _context.push_back(condExp);
        break;
    }
    case IF_ELSE_ELSEIF_OP:
    {
        AstNode *bodyFalse = _context.takeLast();
        AstNode *secondBodyTrue = _context.takeLast();
        AstNode *secondCond = _context.takeLast();
        AstNode *firstBodyTrue = _context.takeLast();
        AstNode *firstCond = _context.takeLast();

        IfElseifElse *longIf = new IfElseifElse(firstCond, firstBodyTrue,
                                               secondCond, secondBodyTrue,
                                               bodyFalse);
        _context.push_back(longIf);
        break;
    }
    case IF_ELSE_OP:
    {
        AstNode *bodyFalse = _context.takeLast();
        AstNode *bodyTrue = _context.takeLast();
        AstNode *cond = _context.takeLast();

        IfElseOp *ifElseOp = new IfElseOp(cond, bodyTrue, bodyFalse);
        _context.push_back(ifElseOp);
        break;
    }
    case IF_OP:
    {
        AstNode *body = _context.takeLast();
        AstNode *cond = _context.takeLast();

        IfOp *ifOp = new IfOp(cond, body);
        _context.push_back(ifOp);
        break;
    }
    case FOR_OP:
    {
        AstNode *body = _context.takeLast();
        AstNode *cond = _context.takeLast();

        ForOp *forOp = new ForOp(cond, body);
        _context.push_back(forOp);
        break;
    }
    case FOR_STEP_COND:
    {
        AstNode *step = _context.takeLast();
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();

        ForStepExpCond *forStepExpCond = new ForStepExpCond(step, leftExp, rightExp);
        _context.push_back(forStepExpCond);
        break;
    }
    case FOR_COND:
    {
        AstNode *rightExp = _context.takeLast();
        AstNode *leftExp = _context.takeLast();
        ForExpCond *forCondExp = new ForExpCond(leftExp, rightExp);
        _context.push_back(forCondExp);
        break;
    }
    case WHILE_OP:
    {
        AstNode *body = _context.takeLast();
        AstNode *cond = _context.takeLast();

        WhileOp *whileOp = new WhileOp(cond, body);
        _context.push_back(whileOp);
        break;
    }
    case READ_OP:
    {
        AstNode *body = _context.takeLast();

        ReadOp *readOp = new ReadOp(body);
        _context.push_back(readOp);
        break;
    }
    case WRITE_OP:
    {
        AstNode *body = _context.takeLast();

        WriteOp *writeOp = new WriteOp(body);
        _context.push_back(writeOp);
        break;
    }


    }
}
