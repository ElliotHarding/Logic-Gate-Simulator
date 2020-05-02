#ifndef TESTS_H
#define TESTS_H

#include <QtTest>
#include "dlg_home.h"
#include "allgates.h"

class Tests : public QObject
{
    Q_OBJECT

public:

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

