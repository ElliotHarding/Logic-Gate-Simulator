#ifndef TESTS_H
#define TESTS_H

#include <QtTest>
//#include <QtXml/QDomDocument>
#include "dlg_home.h"
#include "allgates.h"

class Tests : public QObject
{
    Q_OBJECT

public:

    /*
    class Test_GateCollection : public GateCollection
    {
    public:
        Test_GateCollection(std::vector<Gate*> gates) : GateCollection(gates) {}
        std::vector<Gate*> GetGates()
        {
            return m_gates;
        }
    };*/

private slots:
    //Gate tests
    void test_andGate();
    /*void test_orGate();
    void test_notGate();
    void test_eorGate();
    void test_xorGate();
    void test_norGate();
    void test_nandGate();
    void test_triAndGate();
    void test_triOrGate();
    void test_triEorGate();

    //Link tests
    void test_nodeLink();
    void test_circuit();

    //Saving/loading
    void test_save_load();*/
};

#endif // TESTS_H

