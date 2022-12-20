#include "nasmformatedcommands.h"

NASMFormatedCommands::NASMFormatedCommands()
{


    typeMapping.insert("INT", "4");
    typeMapping.insert("FLOAT", "4");
    typeMapping.insert("BOOL", "1");

    mathOpMapping.insert("+", "add");
    mathOpMapping.insert("-", "sub");
    mathOpMapping.insert("*", "mul");
    mathOpMapping.insert("/", "div");

    NASMLanguageStructure.insert(LIB,
                                 "%include \"io64.inc\"\n\n");

    NASMLanguageStructure.insert(BSS,
                                 "section .bss\n");

    NASMLanguageStructure.insert(MAIN,
                                 "section .text\n" \
                                 "global CMAIN\n" \
                                 "CMAIN:\n");

    NASMLanguageStructure.insert(HLT,
                                 "\n\txor rax, rax\n" \
                                 "\tret\n");

    formatedCommands.insert(DECL, // %1 - имя переменной, %2 - размер
                            "\t%1: resb %2\n");

    formatedCommands.insert(MOV,
                            "\tmov %1, %2\n");

    formatedCommands.insert(MATH_OP, // %1 - первый операнд, %2 - операция, %3 - второй операнд
                            "\t%1 %2, %3\n");

    formatedCommands.insert(WRITE,
                            "\tPRINT_DEC %1, %2\n" \
                            "\tPRINT_CHAR `\\n`\n");
    formatedCommands.insert(JNZ,
                            "\tjnz %1\n");
    formatedCommands.insert(CMP,
                            "\tcmp %1, %2\n");
}
