#include "Tests.h"
#include "allgates.h"

Tests::Tests()
{

}

Tests::~Tests()
{

}

void Tests::test_andGate()
{
    GateAnd andGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

}

void Tests::test_orGate()
{
    GateOr orGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&orGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&orGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
}

void Tests::test_notGate()
{
    GateNot notGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&notGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&notGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    notGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    notGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);
}

void Tests::test_xorGate()
{
    GateXor xorGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&xorGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&xorGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    xorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    xorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    xorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
}

void Tests::test_norGate()
{

}

void Tests::test_nodeLink()
{

}

QTEST_APPLESS_MAIN(Tests)
