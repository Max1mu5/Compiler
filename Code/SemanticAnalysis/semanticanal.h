#ifndef SEMANTICANAL_H
#define SEMANTICANAL_H

#include "./SyntacticAnalysis/ast.h"


class SemanticAnal
{
public:
    SemanticAnal(Ast *root) : _root(root) {}
    void startSemantic();

 private:
    Ast *_root;
    QList<AstNode*> _declaredVariables;
};

#endif // SEMANTICANAL_H
