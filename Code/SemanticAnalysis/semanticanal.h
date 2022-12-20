#ifndef SEMANTICANAL_H
#define SEMANTICANAL_H

#include "./SyntacticAnalysis/ast.h"


class SemanticAnal
{
public:
    SemanticAnal(AstNode *root) : _root(root) {}
    void startSemantic();

 private:
    AstNode *_root;
    AstNode* visit(AstNode *currentNode);
    QList<AstNode*> _declaredVariables;

    void visitor(AstNode *currentNode);
    void expVisitor(AstNode *currentNode, QList<AstNode*> &types);
    bool isTypeMatching(AstNode *varAsmnNode);
    bool isDeclared(AstNode *varNameNode);
    VarType* getVarType(VarName *varName);
};

#endif // SEMANTICANAL_H
