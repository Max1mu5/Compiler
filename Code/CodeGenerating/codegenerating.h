#ifndef CODEGENERATING_H
#define CODEGENERATING_H

#include "./SyntacticAnalysis/ast.h"
#include "nasmformatedcommands.h"
#include "context.h"

class CodeGenerating
{
public:
    CodeGenerating(AstNode *root, QList<AstNode *> declaredVariables)
                    : _root(root),
                      _declaredVariables(declaredVariables),
                      _NASMCode("") {};
    void startCodeGenerating();
private:
    Context _context;
    AstNode *_root;
    QList<AstNode *> _declaredVariables;
    QString _NASMCode;
    NASMFormatedCommands _formatedCommands;
    QString generateBSSSection();
    QString generateMathExp(AstNode *currentNode);
    QString generateCondExp(AstNode *currentNode);
    void visitor(AstNode *currentNode);
    QString generationOutputOp(AstNode *currentNode);
    QString generationInputOp(AstNode *currentNode);
    QString generationForOp(AstNode *currentNode);
    QString generationIfOp(AstNode *currentNode);
    QString generationIfElseOp(AstNode *currentNode);
    QString generationWhileOp(AstNode *currentNode);

};

#endif // CODEGENERATING_H
