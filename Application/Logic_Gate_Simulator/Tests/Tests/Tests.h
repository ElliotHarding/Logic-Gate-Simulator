#ifndef TESTS_H
#define TESTS_H

#include <QtTest>

class Tests : public QObject
{
    Q_OBJECT

public:
    Tests();
    ~Tests();

private slots:
    void test_case1();

};

#endif // TESTS_H

