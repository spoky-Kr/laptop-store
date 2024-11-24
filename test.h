#ifndef TEST_H
#define TEST_H

#include "QRegularExpression"

class test
{
private:
    QRegularExpression regExPass=QRegularExpression("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16}");
public:
    test(){};
    bool checkPassword(QString pass);
};

#endif // TEST_H
