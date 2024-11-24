#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <QObject>

#include "QtTest/QTest"
#include "test.h"

class testUnit:public QObject{
    Q_OBJECT
 private:
    test test_;
 private slots:
    void checkPassOnlyDigits(){
        QCOMPARE(test_.checkPassword("283884848"),false);
    }

    void checkPassOnlyLetters(){
        QCOMPARE(test_.checkPassword("Hotbichto"),false);
    }

    void checkPassOnlyCapitalLetters(){
        QCOMPARE(test_.checkPassword("HKJSLEUFJA"),false);
    }

    void checkPassOnlyLowerLetters(){
        QCOMPARE(test_.checkPassword("hjhfxzslos"),false);
    }

    void checkPassCorrectOne(){
        QCOMPARE(test_.checkPassword("Kdhsjalu5"),true);
    }

    void checkPassOutOfSize(){
        QCOMPARE(test_.checkPassword("dkjhfjsdhjfjsdhhhjhjkjF4"),false);
    }
 public:
    testUnit(){};
};

#endif // TESTUNIT_H
