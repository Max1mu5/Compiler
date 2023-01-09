#include "codegenerating.h"
#include "nasmformatedcommands.h"


#include <QFile>
#include <QTextStream>

void CodeGenerating::startCodeGenerating()
{
    _NASMCode.append(_formatedCommands.NASMLanguageStructure[LIB]);
    _NASMCode.append(generateBSSSection());
    _NASMCode.append(_formatedCommands.NASMLanguageStructure[MAIN]);

    visitor(_root);

    _NASMCode.append(_formatedCommands.NASMLanguageStructure[HLT]);

    QFile data("CodeGeneration.asm");
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&data);
        out << _NASMCode;
    }
}

QString CodeGenerating::generateBSSSection()
{
    if(_declaredVariables.size() == 0) return "";

    QString bssSection = "";
    bssSection.append(_formatedCommands.NASMLanguageStructure[BSS]);

    QString declaredVarCode = "";
    for(auto itDeclaredVariables : _declaredVariables)
    {
        Var *varDeclared = dynamic_cast<Var*>(itDeclaredVariables);
        VarName *varNameDeclared = dynamic_cast<VarName*>(varDeclared->varName);
        VarType *varTypeDeclared = dynamic_cast<VarType*>(varDeclared->type);

        declaredVarCode = _formatedCommands.formatedCommands[DECL];
        declaredVarCode = declaredVarCode.arg(varNameDeclared->name,
                                              _formatedCommands.typeMapping[varTypeDeclared->type]);
        bssSection.append(declaredVarCode);
        declaredVarCode = "";
    }
    return bssSection + "\n";
}

QString CodeGenerating::generateMathExp(AstNode *currentNode)
{
    QString mathCode;
    MathExp *mathExp = dynamic_cast<MathExp *>(currentNode);

    mathCode.append(_formatedCommands.formatedCommands[MOV]);
    mathCode = mathCode.arg("eax");
    switch (mathExp->leftExp->nodeId) // Заменяем %2
    {
    case VAR_NAME_NODE:
    {
        VarName *varName = dynamic_cast<VarName *>(mathExp->leftExp);
        mathCode = mathCode.arg("[" + varName->name + "]");
        break;
    }
    case VAL_FLOAT_NODE:
    {
        ValFloat *valFloat = dynamic_cast<ValFloat *>(mathExp->leftExp);
        mathCode = mathCode.arg(valFloat->value);
        break;
    }
    case VAL_INT_NODE:
    {
        ValInt *valInt = dynamic_cast<ValInt *>(mathExp->leftExp);
        mathCode = mathCode.arg(valInt->value);
        break;
    }
    }

    mathCode.append(_formatedCommands.formatedCommands[MATH_OP]);
    mathCode = mathCode.arg(_formatedCommands.mathOpMapping[mathExp->op]); // заменяем %2
    mathCode = mathCode.arg("eax");

    switch (mathExp->rightExp->nodeId) // Заменяем %3
    {
    case VAR_NAME_NODE:
    {
        VarName *varName = dynamic_cast<VarName *>(mathExp->rightExp);
        mathCode = mathCode.arg("[" + varName->name + "]");
        break;
    }
    case VAL_FLOAT_NODE:
    {
        ValFloat *valFloat = dynamic_cast<ValFloat *>(mathExp->rightExp);
        mathCode = mathCode.arg(valFloat->value);
        break;
    }
    case VAL_INT_NODE:
    {
        ValInt *valInt = dynamic_cast<ValInt *>(mathExp->rightExp);
        mathCode = mathCode.arg(valInt->value);
        break;
    }
    case MATH_EXP_NODE:
    {
        mathCode = mathCode.arg("ebx");
        QString tempMov = _formatedCommands.formatedCommands[MOV].arg("ebx", "eax");
        mathCode = generateMathExp(mathExp->rightExp).append(tempMov).append(mathCode);
        break;
    }
    }
    return mathCode;
}

void CodeGenerating::visitor(AstNode *currentNode)
{
    switch (currentNode->nodeId)
    {
    case COMMAND_CHAIN_NODE:
    {
        CommandChain *chain = dynamic_cast<CommandChain*>(currentNode);
        visitor(chain->leftNode);
        visitor(chain->rightNode);
        break;
    }
    case MATH_EXP_NODE:
    {
        _NASMCode.append(generateMathExp(currentNode));
        break;
    }
    case VAL_INT_NODE:
    {
        ValInt *valInt = dynamic_cast<ValInt*>(currentNode);
        QString movNumberEax = _formatedCommands.formatedCommands[MOV];
        movNumberEax = movNumberEax.arg("eax", QString::number(valInt->value));
        _NASMCode.append(movNumberEax);
        break;
    }
    case VAL_FLOAT_NODE:
    {
        ValFloat *valFloat = dynamic_cast<ValFloat*>(currentNode);
        QString movNumberEax = _formatedCommands.formatedCommands[MOV];
        movNumberEax = movNumberEax.arg("eax", QString::number(valFloat->value));
        _NASMCode.append(movNumberEax);
        break;
    }
    case VAR_NAME_NODE:
    {
        VarName *varName = dynamic_cast<VarName*>(currentNode);
        QString movNumberEax = _formatedCommands.formatedCommands[MOV];
        movNumberEax = movNumberEax.arg("eax", "[" + varName->name + "]");
        _NASMCode.append(movNumberEax);
        break;
    }
    case VAR_ASMT_NODE:
    {
        VarAsmt *varAsmt = dynamic_cast<VarAsmt *>(currentNode);
        visitor(varAsmt->exp);
        VarName *varName = dynamic_cast<VarName *>(varAsmt->var);
        QString varAsmtCode = _formatedCommands.formatedCommands[MOV];
        varAsmtCode = varAsmtCode.arg("[" + varName->name + "]", "eax");
        _NASMCode.append(varAsmtCode);
        break;
    }
    case WRITE_OP_NODE:
    {
        _NASMCode.append(generationOutputOp(currentNode));
        break;
    }
    case FOR_OP_NODE:
    {
        generationForOp(currentNode);
        break;
    }
    case IF_OP_NODE:
    {
        generationIfOp(currentNode);
        break;
    }
    case IF_ELSE_OP_NODE:
    {
        generationIfElseOp(currentNode);
        break;
    }
    case WHILE_OP_NODE:
    {
        generationWhileOp(currentNode);
        break;
    }
    }
}



QString CodeGenerating::generationOutputOp(AstNode *currentNode)
{
    QString print = _formatedCommands.formatedCommands[WRITE];
    WriteOp *writeOp = dynamic_cast<WriteOp *>(currentNode);
    switch (writeOp->exp->nodeId)
    {
    case VAR_NAME_NODE:
    {
        VarName *varName = dynamic_cast<VarName*>(writeOp->exp);
        print = print.arg(QString::number(4), varName->name);
        break;
    }
    case MATH_EXP_NODE:
    {
        visitor(writeOp->exp);
        print = print.arg(QString::number(4), "eax");
        break;
    }
    case VAL_FLOAT_NODE:
    {
        ValFloat *valFloat = dynamic_cast<ValFloat *>(writeOp->exp);
        print = print.arg(QString::number(4), QString::number(valFloat->value));
        break;
    }
    case VAL_INT_NODE:
    {
        ValInt *valInt = dynamic_cast<ValInt *>(writeOp->exp);
        print = print.arg(QString::number(4), QString::number(valInt->value));
        break;
    }
    }
    return print;
}

QString CodeGenerating::generationForOp(AstNode *currentNode)
{
    _context.forCounter++;
    ForOp *forOp = dynamic_cast<ForOp*>(currentNode);
    VarAsmt *varAsmt;

    switch (forOp->cond->nodeId)
    {
    case FOR_EXP_COND_NODE:
    {
        ForExpCond *forExpCond = dynamic_cast<ForExpCond*>(forOp->cond);
        visitor(forExpCond->leftExp);
        visitor(forExpCond->rightExp);
        varAsmt = dynamic_cast<VarAsmt*>(forExpCond->leftExp);
        break;
    }
    case FOR_STEP_EXP_COND_NODE:
    {
        ForStepExpCond *forStepExpCond = dynamic_cast<ForStepExpCond*>(forOp->cond);
        visitor(forStepExpCond->leftExp);
        visitor(forStepExpCond->rightExp);
        varAsmt = dynamic_cast<VarAsmt*>(forStepExpCond->leftExp);
        break;
    }
    }

    VarName* varName = dynamic_cast<VarName*>(varAsmt->var);

    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("ecx", "eax"));

    QString marker = "\tfor%1";
    marker = marker.arg(_context.forCounter);

    _NASMCode.append(marker + ":\n");

    visitor(forOp->body);

    switch (forOp->cond->nodeId)
    {
    case FOR_STEP_EXP_COND_NODE:
    {
        ForStepExpCond *forStepExpCond = dynamic_cast<ForStepExpCond*>(forOp->cond);
        visitor(forStepExpCond->step);
        break;
    }
    case FOR_EXP_COND_NODE:
    {
         _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("eax", "1"));
         break;
    }
    }

    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("ebx", "eax"));
    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("eax", "[" + varName->name + "]"));
    _NASMCode.append(_formatedCommands.formatedCommands[MATH_OP]
                     .arg(_formatedCommands.mathOpMapping["+"], "eax", "ebx"));
    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("[" + varName->name + "]", "eax"));
    _NASMCode.append(_formatedCommands.formatedCommands[CMP].arg("ecx", "[" + varName->name + "]"));
    _NASMCode.append(_formatedCommands.formatedCommands[JNZ].arg(marker));
    return "";
}

QString CodeGenerating::generationIfOp(AstNode *currentNode)
{
    _context.ifCounter++;
    IfOp *ifOp = dynamic_cast<IfOp*>(currentNode);
    CondExp *condExp = dynamic_cast<CondExp*>(ifOp->cond);

    visitor(condExp->rightExp);
    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("ebx", "eax"));
    visitor(condExp->leftExp);

    _NASMCode.append(_formatedCommands.formatedCommands[CMP].arg("eax", "ebx"));


    QString markerIfEnd = "\tifEnd%1";
    markerIfEnd = markerIfEnd.arg(_context.ifCounter);



    _NASMCode.append(_formatedCommands.formatedCommands[COND]
                     .arg(_formatedCommands.condOpMapping[condExp->op],
                          markerIfEnd));

    visitor(ifOp->body);

    _NASMCode.append(markerIfEnd + ":\n");

    return "";
}

QString CodeGenerating::generationIfElseOp(AstNode *currentNode)
{
    _context.ifCounter++;
    IfElseOp* ifElse = dynamic_cast<IfElseOp*>(currentNode);
    CondExp *condExp = dynamic_cast<CondExp*>(ifElse->cond);

    visitor(condExp->rightExp);
    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("ebx", "eax"));
    visitor(condExp->leftExp);

    _NASMCode.append(_formatedCommands.formatedCommands[CMP].arg("eax", "ebx"));

    QString markerIfEnd = "\tifEnd%1";
    QString markerElseBody = "\telse%1";
    markerIfEnd = markerIfEnd.arg(_context.ifCounter);
    markerElseBody = markerElseBody.arg(_context.ifCounter);

    _NASMCode.append(_formatedCommands.formatedCommands[COND]
                     .arg(_formatedCommands.condInverseOpMapping[condExp->op],
                          markerElseBody));
    visitor(ifElse->bodyTrue);
    _NASMCode.append(_formatedCommands.formatedCommands[JMP].arg(markerIfEnd));
    _NASMCode.append(markerElseBody + ":\n");
    visitor(ifElse->bodyFalse);
    _NASMCode.append(markerIfEnd + ":\n");
    return "";
}

QString CodeGenerating::generationWhileOp(AstNode *currentNode)
{
    _context.whileCounter++;
    WhileOp *whileOp = dynamic_cast<WhileOp*>(currentNode);

    CondExp *condExp = dynamic_cast<CondExp*>(whileOp->cond);

    QString markerWhileStart = "\twhileStart%1";
    QString markerWhileEnd = "\twhileEnd%1";
    markerWhileStart = markerWhileStart.arg(_context.whileCounter);
    markerWhileEnd = markerWhileEnd.arg(_context.whileCounter);

    _NASMCode.append(markerWhileStart + ":\n");

    visitor(condExp->rightExp);
    _NASMCode.append(_formatedCommands.formatedCommands[MOV].arg("ebx", "eax"));
    visitor(condExp->leftExp);

    _NASMCode.append(_formatedCommands.formatedCommands[CMP].arg("eax", "ebx"));

    _NASMCode.append(_formatedCommands.formatedCommands[COND]
                     .arg(_formatedCommands.condInverseOpMapping[condExp->op],
                          markerWhileEnd));

    visitor(whileOp->body);
    _NASMCode.append(_formatedCommands.formatedCommands[JMP].arg(markerWhileStart));
    _NASMCode.append(markerWhileEnd + ":\n");
    return "";
}
