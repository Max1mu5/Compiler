QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LexicalAnalysis/lexicalwindow.cpp \
    SemanticAnalysis/semanticanal.cpp \
    SyntacticAnalysis/ast.cpp \
    SyntacticAnalysis/recedence.cpp \
    SyntacticAnalysis/recedenceitem.cpp \
    SyntacticAnalysis/syntacticwindow.cpp \
    SyntacticAnalysis/syntanal.cpp \
    errorhandler.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    LexicalAnalysis/lexicalwindow.h \
    SemanticAnalysis/semanticanal.h \
    SyntacticAnalysis/ast.h \
    SyntacticAnalysis/recedence.h \
    SyntacticAnalysis/recedenceitem.h \
    SyntacticAnalysis/syntacticwindow.h \
    SyntacticAnalysis/syntanal.h \
    errorhandler.h \
    mainwindow.h

FORMS += \
    LexicalAnalysis/lexicalwindow.ui \
    SyntacticAnalysis/syntacticwindow.ui \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SemanticAnalysis/temp.txt \
    SyntacticAnalysis/enumExpressions.inc \
    SyntacticAnalysis/formalLang.txt
