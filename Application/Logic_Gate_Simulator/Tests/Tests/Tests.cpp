#include "Tests.h"
#include "../../converter.h"

#include <QFont>

void Tests::test_andGate()
{
    GateAnd andGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&andGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&andGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

}

void Tests::test_orGate()
{
    GateOr orGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&orGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&orGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);
}

void Tests::test_notGate()
{
    GateNot notGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&notGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&notGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    notGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    notGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);
}

void Tests::test_eorGate()
{
    GateEor eorGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&eorGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&eorGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);
}

void Tests::test_xorGate()
{
    GateXor xorGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&xorGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&xorGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    xorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    xorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    xorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);
}

void Tests::test_norGate()
{
    GateNor norGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&norGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&norGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    norGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    norGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    norGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);
}

void Tests::test_nandGate()
{
    GateNand nandGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&nandGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&nandGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    nandGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    nandGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);
}

void Tests::test_triAndGate()
{
    GateTriAnd andGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&andGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&andGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(true);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(true);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(false);
    inputNodes[2]->setValue(true);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(false);
    andGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);
}

void Tests::test_triOrGate()
{
    GateTriOr orGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&orGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&orGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(true);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(true);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    inputNodes[2]->setValue(true);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(false);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    inputNodes[2]->setValue(false);
    orGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);
}

void Tests::test_triEorGate()
{
    GateTriEor eorGate;

    std::vector<Node*> inputNodes = dynamic_cast<Gate*>(&eorGate)->getInputNodes();
    std::vector<Node*> outputNodes = dynamic_cast<Gate*>(&eorGate)->getOutputNodes();

    inputNodes[0]->setValue(true);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(true);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(true);
    inputNodes[2]->setValue(false);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), true);

    inputNodes[0]->setValue(false);
    inputNodes[1]->setValue(false);
    inputNodes[2]->setValue(false);
    eorGate.updateOutput();
    QCOMPARE(outputNodes[0]->value(), false);
}

void Tests::test_outputGates()
{
    GateToggle toggleGate;

    Node* pOutNode = toggleGate.getOutputNodes()[0];

    toggleGate.setPowerState(true);
    QCOMPARE(pOutNode->value(), true);
    QCOMPARE(toggleGate.getPowerState(), true);

    toggleGate.setPowerState(false);
    QCOMPARE(pOutNode->value(), false);
    QCOMPARE(toggleGate.getPowerState(), false);

    GateConstantActive activeGate;
    QCOMPARE(activeGate.getOutputNodes()[0]->value(), true);

    GateConstantInactive inactiveGate;
    QCOMPARE(inactiveGate.getOutputNodes()[0]->value(), false);

    //Timer gate has its own test
}

void Tests::test_fpga()
{
    //Init ui stuff for test
    int a0 = 0;
    char** cl;
    QApplication a(a0, cl);

    GateFPGA fpga;
    fpga.setInputs(3);
    fpga.setOutputs(3);

    QCOMPARE(fpga.getOutputNodes().size(), 3);
    QCOMPARE(fpga.getInputNodes().size(), 3);

    fpga.setScript("var output1 = true, output2 = false, output3 = true, output4 = true, output5 = true;");
    fpga.updateOutput();
    QCOMPARE(fpga.getOutputNodes()[0]->value(), true);
    QCOMPARE(fpga.getOutputNodes()[1]->value(), false);
    QCOMPARE(fpga.getOutputNodes()[2]->value(), true);


    fpga.setScript("var output1 = input1 & input2; var output2 = input1 | input2; var output3 = input1 & input3;");
    fpga.getInputNodes()[0]->setValue(true);
    fpga.getInputNodes()[1]->setValue(false);
    fpga.getInputNodes()[2]->setValue(true);
    fpga.updateOutput();
    QCOMPARE(fpga.getOutputNodes()[0]->value(), false);
    QCOMPARE(fpga.getOutputNodes()[1]->value(), true);
    QCOMPARE(fpga.getOutputNodes()[2]->value(), true);

    fpga.setScript("");
    fpga.getInputNodes()[0]->setValue(true);
    fpga.getInputNodes()[1]->setValue(false);
    fpga.getInputNodes()[2]->setValue(true);
    fpga.updateOutput();
    QCOMPARE(fpga.getOutputNodes()[0]->value(), false);
    QCOMPARE(fpga.getOutputNodes()[0]->value(), false);
    QCOMPARE(fpga.getOutputNodes()[0]->value(), false);

    //Todo : extend test

}


void Tests::test_nodeLink()
{
    GateReciever reciever;
    Node* pRecieverNode = reciever.getInputNodes()[0];

    GateToggle toggle;
    Node* pSenderNode = toggle.getOutputNodes()[0];

    QCOMPARE(pRecieverNode->linkNode(pSenderNode), true);
    QCOMPARE(pSenderNode->linkNode(pRecieverNode), true);

    toggle.setPowerState(1);
    toggle.updateOutput();
    QCOMPARE(pRecieverNode->value(), true);

    toggle.setPowerState(0);
    toggle.updateOutput();
    QCOMPARE(pRecieverNode->value(), false);
}

void Tests::test_booleanExpressionsToCircuit()
{
    //Init ui stuff for test
    int a0 = 0;
    char** cl;
    QApplication a(a0, cl);

    std::vector<BooleanExpression> expressions;
    CircuitOptions circuitOptions(false, false, false, 200, 20, 20, ConversionAlgorithm::QuineMcCluskey);
    GateCollection* pNewCircuit;

    //Expression to convert to circuit
    BooleanExpression expression;
    expression.resultLetter = 'Z';
    expression.letters = {'A', 'B'};
    expressions.push_back(expression);

    //Do conversion
    QCOMPARE(Converter::booleanExpressionsToCircuit(expressions, circuitOptions, pNewCircuit), ConverterResult::SUCCESS);

    if(pNewCircuit == nullptr)
    {
        QCOMPARE(true, false);
        return;
    }

    TruthTable tt;
    QCOMPARE(Converter::circuitToTruthTable(pNewCircuit->getGates(), tt), SUCCESS);

    std::vector<std::vector<bool>> outValues = {{false}, {false}, {false}, {true}};
    QCOMPARE(tt.outValues, outValues);


    delete pNewCircuit;
    pNewCircuit = nullptr;


    BooleanExpression expression2;
    expression2.resultLetter = 'Y';
    expression2.letters = {'C', '+', 'D'};
    expressions.push_back(expression2);

    expressions.push_back(expression);

    QCOMPARE(Converter::booleanExpressionsToCircuit(expressions, circuitOptions, pNewCircuit), ConverterResult::SUCCESS);

    if(pNewCircuit == nullptr)
    {
        QCOMPARE(true, false);
        return;
    }

    TruthTable tt2;
    QCOMPARE(Converter::circuitToTruthTable(pNewCircuit->getGates(), tt2), SUCCESS);

    std::vector<std::vector<bool>> outValues2 = {{false, false},
                                                 {false, false},
                                                 {false, false},
                                                 {false, true},
                                                 {true, false},
                                                 {true, false},
                                                 {true, false},
                                                 {true, true},
                                                 {true, false},
                                                 {true, false},
                                                 {true, false},
                                                 {true, true},
                                                 {true, false},
                                                 {true, false},
                                                 {true, false},
                                                 {true, true}};
    QCOMPARE(tt2.outValues, outValues2);
}

void Tests::test_truthTableToBooleanExpression()
{
    TruthTable truthTable;
    truthTable.size = 16;
    for(uint i = 0; i < 16; i++)
    {
        truthTable.inValues.push_back(truthTable.genInputs(i, 4));
    }
    truthTable.outValues = {{false, false},
                            {false, false},
                            {false, false},
                            {false, true},
                            {true, false},
                            {true, false},
                            {true, false},
                            {true, true},
                            {true, false},
                            {true, false},
                            {true, false},
                            {true, true},
                            {true, false},
                            {true, false},
                            {true, false},
                            {true, true}};
    truthTable.inLetters = {'A', 'B', 'C', 'D'};
    truthTable.outLetters = {'Z', 'Y'};

    std::vector<BooleanExpression> expressions;
    QCOMPARE(Converter::truthTableToBooleanExpressions(truthTable, ConversionAlgorithm::QuineMcCluskey, expressions), SUCCESS);

    if(expressions.size() != 2)
    {
        QCOMPARE(false, true);
        return;
    }

    std::vector<char> resultLetters1 = {'A','B'};
    std::vector<char> resultLetters2 = {'D', '+', 'C'};

    QCOMPARE(expressions[0].resultLetter, 'Z');
    QCOMPARE(expressions[1].resultLetter, 'Y');
    QCOMPARE(expressions[0].letters, resultLetters2);
    QCOMPARE(expressions[1].letters, resultLetters1);
}

void Tests::test_circuitToOther()
{
    //todo
}
#include "../../gatefield.h"
void Tests::test_save_load()
{
    //Create circuit
    GateToggle toggleGate(200, 200);
    GateToggle toggleGate2(200, 300);
    GateAnd andGate(300, 200);
    GateReciever receiverGate(400, 200);
    toggleGate.setPowerState(true);
    toggleGate.setPowerState(true);
    andGate.getInputNodes()[0]->linkNode(toggleGate.getOutputNodes()[0]);
    toggleGate.getOutputNodes()[0]->linkNode(andGate.getInputNodes()[0]);
    andGate.getInputNodes()[1]->linkNode(toggleGate2.getOutputNodes()[0]);
    toggleGate2.getOutputNodes()[0]->linkNode(andGate.getInputNodes()[1]);
    andGate.getOutputNodes()[0]->linkNode(receiverGate.getInputNodes()[0]);
    receiverGate.getInputNodes()[0]->linkNode(andGate.getOutputNodes()[0]);

    GateField gf(nullptr, 1, "Test", 300);
    gf.addGate(&toggleGate, false);
    gf.addGate(&toggleGate2, false);
    gf.addGate(&andGate, false);
    gf.addGate(&receiverGate, false);



}

QTEST_APPLESS_MAIN(Tests)
