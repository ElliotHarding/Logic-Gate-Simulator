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

    BooleanExpression expression;
    expression.resultLetter = 'Z';
    expression.letters = {'A', 'B'};
    expressions.push_back(expression);

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
/*
void Tests::test_circuit()
{
    //Circuits gates
    GateToggle toggle1;
    GateToggle toggle2;
    GateToggle toggle3;
    GateNand nand;
    GateNor nor;
    GateTriAnd triAnd;

    //Get nodes
    std::vector<Node*> nandInputs;
    std::vector<Node*> nandOutputs;
    std::vector<Node*> norInputs;
    std::vector<Node*> norOutputs;
    std::vector<Node*> triAndInputs;
    std::vector<Node*> triAndOutputs;
    std::vector<Node*> toggle1Node;
    std::vector<Node*> toggle2Node;
    std::vector<Node*> toggle3Node;
    dynamic_cast<Gate*>(&nand)->getInputNodes(nandInputs);
    dynamic_cast<Gate*>(&nand)->getOutputNodes(nandOutputs);
    dynamic_cast<Gate*>(&nor)->getInputNodes(norInputs);
    dynamic_cast<Gate*>(&nor)->getOutputNodes(norOutputs);
    dynamic_cast<Gate*>(&triAnd)->getInputNodes(triAndInputs);
    dynamic_cast<Gate*>(&triAnd)->getOutputNodes(triAndOutputs);
    dynamic_cast<Gate*>(&toggle1)->getOutputNodes(toggle1Node);
    dynamic_cast<Gate*>(&toggle2)->getOutputNodes(toggle2Node);
    dynamic_cast<Gate*>(&toggle3)->getOutputNodes(toggle3Node);


    //Link circuit
    toggle1Node[0]->LinkNode(nandInputs[0]);
    toggle1Node[0]->LinkNode(norInputs[0]);
    toggle2Node[0]->LinkNode(nandInputs[1]);
    toggle2Node[0]->LinkNode(norInputs[1]);

    nandOutputs[0]->LinkNode(triAndInputs[0]);
    toggle3Node[0]->LinkNode(triAndInputs[1]);
    norOutputs[0]->LinkNode(triAndInputs[2]);


    //Test results - (0,0,0 --> 0)
    toggle1.SetPowerState(0);
    toggle2.SetPowerState(0);
    toggle3.SetPowerState(0);

    nand.updateOutput();
    nor.updateOutput();
    triAnd.updateOutput();

    QCOMPARE(triAndOutputs[0]->value(), false);

    //Test results - (1,1,1 --> 0)
    toggle1.SetPowerState(1);
    toggle2.SetPowerState(1);
    toggle3.SetPowerState(1);

    nand.updateOutput();
    nor.updateOutput();
    triAnd.updateOutput();

    QCOMPARE(triAndOutputs[0]->value(), false);

    //Test results - (0,0,0 --> 0)
    toggle1.SetPowerState(0);
    toggle2.SetPowerState(1);
    toggle3.SetPowerState(1);

    nand.updateOutput();
    nor.updateOutput();
    triAnd.updateOutput();

    QCOMPARE(triAndOutputs[0]->value(), false);

    //Test results - (0,0,1 --> 1)
    toggle1.SetPowerState(0);
    toggle2.SetPowerState(0);
    toggle3.SetPowerState(1);

    nand.updateOutput();
    nor.updateOutput();
    triAnd.updateOutput();

    QCOMPARE(triAndOutputs[0]->value(), true);
}

#include "gatereader.h"
void Tests::test_save_load()
{
    //Circuits gates
    GateToggle toggle1;
    GateToggle toggle2;
    GateToggle toggle3;
    GateNand nand;
    GateNor nor;
    GateTriAnd triAnd;

    //Get nodes
    std::vector<Node*> nandInputs;
    std::vector<Node*> nandOutputs;
    std::vector<Node*> norInputs;
    std::vector<Node*> norOutputs;
    std::vector<Node*> triAndInputs;
    std::vector<Node*> triAndOutputs;
    std::vector<Node*> toggle1Node;
    std::vector<Node*> toggle2Node;
    std::vector<Node*> toggle3Node;
    dynamic_cast<Gate*>(&nand)->getInputNodes(nandInputs);
    dynamic_cast<Gate*>(&nand)->getOutputNodes(nandOutputs);
    dynamic_cast<Gate*>(&nor)->getInputNodes(norInputs);
    dynamic_cast<Gate*>(&nor)->getOutputNodes(norOutputs);
    dynamic_cast<Gate*>(&triAnd)->getInputNodes(triAndInputs);
    dynamic_cast<Gate*>(&triAnd)->getOutputNodes(triAndOutputs);
    dynamic_cast<Gate*>(&toggle1)->getOutputNodes(toggle1Node);
    dynamic_cast<Gate*>(&toggle2)->getOutputNodes(toggle2Node);
    dynamic_cast<Gate*>(&toggle3)->getOutputNodes(toggle3Node);

    //Link circuit
    toggle1Node[0]->LinkNode(nandInputs[0]);
    toggle1Node[0]->LinkNode(norInputs[0]);
    toggle2Node[0]->LinkNode(nandInputs[1]);
    toggle2Node[0]->LinkNode(norInputs[1]);

    nandOutputs[0]->LinkNode(triAndInputs[0]);
    toggle3Node[0]->LinkNode(triAndInputs[1]);
    norOutputs[0]->LinkNode(triAndInputs[2]);

    std::vector<Gate*> gates;
    gates.push_back(&toggle1);
    gates.push_back(&toggle2);
    gates.push_back(&toggle3);
    gates.push_back(&nand);
    gates.push_back(&nor);
    gates.push_back(&triAnd);

    if(!QDir("Saves").exists())
        QDir().mkdir("Saves");

    //Save
    std::ofstream newGateCollection("Saves/test.CustomGate");
    if(newGateCollection.is_open())
    {
        GateCollection::SaveData(newGateCollection, gates);
        newGateCollection.close();

        //Load
        std::ifstream customGateFile("Saves/test.CustomGate");
        if(customGateFile.is_open())
        {
            GateCollection* cg;
            static GateReader gReader;
            QCOMPARE(gReader.ReadGateCollection(customGateFile, cg), true);

            std::vector<Gate*> loadedGates = dynamic_cast<Test_GateCollection*>(cg)->GetGates();

            //Test results - (0,0,1 --> 1)
            dynamic_cast<GateToggle*>(loadedGates[0])->SetPowerState(0);
            dynamic_cast<GateToggle*>(loadedGates[1])->SetPowerState(0);
            dynamic_cast<GateToggle*>(loadedGates[2])->SetPowerState(1);

            loadedGates[3]->UpdateOutput();
            loadedGates[4]->UpdateOutput();
            loadedGates[5]->UpdateOutput();

            std::vector<Node*> output;
            loadedGates[5]->getOutputNodes(output);

            QCOMPARE(output[0]->value(), true);
        }
    }
}*/

QTEST_APPLESS_MAIN(Tests)
