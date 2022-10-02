#include <QtTest>
#include <QCoreApplication>

#define private public
#include "../Code/mainwindow.h"
#include "../Code/lexicalwindow.h"
#define private private

class performance : public QObject
{
    Q_OBJECT

public:
    performance();
    ~performance();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_clearComments_case1();
    void test_clearComments_case2();
    void test_lexicalAnalyze_case1();
    void test_lexicalAnalyze_case2();
    void test_lexicalAnalyze_case3();

};

performance::performance()
{
}

performance::~performance()
{

}

void performance::initTestCase()
{

}

void performance::cleanupTestCase()
{

}

void performance::test_clearComments_case1()
{
    LexicalWindow *obj = new LexicalWindow();
    obj->setCodeText("VR1 : %\nVR2 : !\n/*\nVR3, VR4 : $; */\nVR5 : !; VR6 : !;");
    obj->clearComments();
    QCOMPARE(obj->getCodeText(), "VR1 : %\nVR2 : !\n\nVR5 : !; VR6 : !;");
}

void performance::test_clearComments_case2()
{
    LexicalWindow *obj = new LexicalWindow();
    obj->setCodeText("VR1 : %\nVR2 : !\n/*\nVR3, VR4 : $; */\nVR5 : !/*; VR6 : !*/;");
    obj->clearComments();
    QCOMPARE(obj->getCodeText(), QString("VR1 : %\nVR2 : !\n\nVR5 : !;"));
}

void performance::test_lexicalAnalyze_case1()
{
    LexicalWindow *obj = new LexicalWindow();
    obj->setCodeText("VR1 : %\n VR2 : ! VR3, VR4 : $;\nVR5 : !; VR6 : !;\nend\n");
    obj->lexicalAnalyze();

    QCOMPARE(obj->tokensToText(), "(2, 0) (1, 0) (0, 0) (1, 1) (2, 1) (1, 0) (0, 1)"
                                  " (2, 2) (1, 2) (2, 3) (1, 0) (0, 2) (1, 3) (1, 1)"
                                  " (2, 4) (1, 0) (0, 1) (1, 3) (2, 5) (1, 0) (0, 1)"
                                  " (1, 3) (1, 1) (0, 3) (1, 1) ");
}

void performance::test_lexicalAnalyze_case2()
{
    LexicalWindow * obj = new LexicalWindow();
    obj->recieveData("VR1 := 1 + 5 + 6\n\
                      VR2 := VR3\nend\n");
    QCOMPARE(obj->tokensToText(), "(2, 0) (1, 0) (3, 0) (1, 1) (3, 1) (1, 1) (3, 2) (1, 2) (2, 1) (1, 0) (2, 2) (1, 2) (0, 0) (1, 2) ");
}

void performance::test_lexicalAnalyze_case3()
{
    LexicalWindow *obj = new LexicalWindow();
    obj->recieveData("for VR1 := 1 to 10 step 1 VR4 := 11 next ");
    QCOMPARE(obj->tokensToText(), "(0, 0) (2, 0) (1, 0) (3, 0) (0, 1) (3, 1) (0, 2) (3, 0) (2, 1) (1, 0) (3, 2) (0, 3) ");
}



QTEST_MAIN(performance)

#include "tst_performance.moc"
