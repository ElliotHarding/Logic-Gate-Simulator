#ifndef TESTS_H
#define TESTS_H

#include <QtTest>
#include "allgates.h"

class Tests : public QObject
{
    Q_OBJECT

public:

private slots:
    //Gate tests
    void test_andGate();
    void test_orGate();
    void test_notGate();
    void test_eorGate();
    void test_xorGate();
    void test_norGate();
    void test_nandGate();
    void test_triAndGate();
    void test_triOrGate();
    void test_triEorGate();
    void test_outputGates();
    void test_fpga();

    void test_nodeLink();

    void test_booleanExpressionsToCircuit();
    void test_truthTableToBooleanExpression();
    void test_circuitToOther();

    void test_save_load();
};

#endif // TESTS_H

