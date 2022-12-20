#ifndef NASMFORMATEDCOMMANDS_H
#define NASMFORMATEDCOMMANDS_H

#include <QHash>
#include "./SyntacticAnalysis/ast.h"

enum NASMStructure
{
    LIB = 0,
    BSS = 1,
    MAIN = 2,
    HLT = 3
};

enum NASMCommands
{
    DECL = 0,
    MOV = 1,
    MATH_OP = 2,
    WRITE = 3,
    JNZ = 4,
    CMP = 5
};

class NASMFormatedCommands
{
public:
    NASMFormatedCommands();
    QHash<NASMCommands, QString> formatedCommands;
    QHash<QString, QString> typeMapping;
    QHash<NASMStructure, QString> NASMLanguageStructure;
    QHash<QString, QString> signMapping;
    QHash<QString, QString> mathOpMapping;
};

#endif // NASMFORMATEDCOMMANDS_H
