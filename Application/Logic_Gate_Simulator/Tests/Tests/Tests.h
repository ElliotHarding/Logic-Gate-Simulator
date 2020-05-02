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
    void test_andGate();
    void test_orGate();
    void test_notGate();
    void test_eorGate();
    void test_xorGate();
    void test_norGate();
    void test_nodeLink();

};

#endif // TESTS_H

