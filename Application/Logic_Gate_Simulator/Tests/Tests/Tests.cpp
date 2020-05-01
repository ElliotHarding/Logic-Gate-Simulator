#include "Tests.h"
#include "allgates.h"

Tests::Tests()
{

}

Tests::~Tests()
{

}

void Tests::test_case1()
{
    GateAnd andGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[0]->SetValue(true);
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(true);
    inputNodes[0]->SetValue(true);
    QCOMPARE(outputNodes[0]->GetValue(), true);

}

QTEST_APPLESS_MAIN(Tests)
