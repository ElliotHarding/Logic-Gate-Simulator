#include "Tests.h"

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

/*
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

void Tests::test_eorGate()
{
    GateEor eorGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&eorGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&eorGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
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
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    xorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    xorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);
}

void Tests::test_norGate()
{
    GateNor norGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&norGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&norGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    norGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    norGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    norGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);
}

void Tests::test_nandGate()
{
    GateNand nandGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&nandGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&nandGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    nandGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    nandGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);
}

void Tests::test_triAndGate()
{
    GateTriAnd andGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&andGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(true);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(true);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(false);
    inputNodes[2]->SetValue(true);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(false);
    andGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
}

void Tests::test_triOrGate()
{
    GateTriOr orGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&orGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&orGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(true);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(true);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    inputNodes[2]->SetValue(true);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(false);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    inputNodes[2]->SetValue(false);
    orGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
}

void Tests::test_triEorGate()
{
    GateTriEor eorGate;

    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    dynamic_cast<Gate*>(&eorGate)->GetDisconnectedInputNodes(inputNodes);
    dynamic_cast<Gate*>(&eorGate)->GetDisconnectedOutputNodes(outputNodes);

    inputNodes[0]->SetValue(true);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(true);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(true);
    inputNodes[2]->SetValue(false);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), true);

    inputNodes[0]->SetValue(false);
    inputNodes[1]->SetValue(false);
    inputNodes[2]->SetValue(false);
    eorGate.UpdateOutput();
    QCOMPARE(outputNodes[0]->GetValue(), false);
}

void Tests::test_nodeLink()
{
    GateReciever reciever;
    GateToggle toggle;

    std::vector<Node*> inputNode;
    std::vector<Node*> outputNode;
    dynamic_cast<Gate*>(&reciever)->GetDisconnectedInputNodes(inputNode);
    dynamic_cast<Gate*>(&toggle)->GetDisconnectedOutputNodes(outputNode);

    inputNode[0]->LinkNode(outputNode[0]);

    toggle.SetPowerState(1);
    toggle.UpdateOutput();
    QCOMPARE(outputNode[0]->GetValue(), true);

    toggle.SetPowerState(0);
    toggle.UpdateOutput();
    QCOMPARE(outputNode[0]->GetValue(), false);
}

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
    dynamic_cast<Gate*>(&nand)->GetDisconnectedInputNodes(nandInputs);
    dynamic_cast<Gate*>(&nand)->GetDisconnectedOutputNodes(nandOutputs);
    dynamic_cast<Gate*>(&nor)->GetDisconnectedInputNodes(norInputs);
    dynamic_cast<Gate*>(&nor)->GetDisconnectedOutputNodes(norOutputs);
    dynamic_cast<Gate*>(&triAnd)->GetDisconnectedInputNodes(triAndInputs);
    dynamic_cast<Gate*>(&triAnd)->GetDisconnectedOutputNodes(triAndOutputs);
    dynamic_cast<Gate*>(&toggle1)->GetDisconnectedOutputNodes(toggle1Node);
    dynamic_cast<Gate*>(&toggle2)->GetDisconnectedOutputNodes(toggle2Node);
    dynamic_cast<Gate*>(&toggle3)->GetDisconnectedOutputNodes(toggle3Node);


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

    nand.UpdateOutput();
    nor.UpdateOutput();
    triAnd.UpdateOutput();

    QCOMPARE(triAndOutputs[0]->GetValue(), false);

    //Test results - (1,1,1 --> 0)
    toggle1.SetPowerState(1);
    toggle2.SetPowerState(1);
    toggle3.SetPowerState(1);

    nand.UpdateOutput();
    nor.UpdateOutput();
    triAnd.UpdateOutput();

    QCOMPARE(triAndOutputs[0]->GetValue(), false);

    //Test results - (0,0,0 --> 0)
    toggle1.SetPowerState(0);
    toggle2.SetPowerState(1);
    toggle3.SetPowerState(1);

    nand.UpdateOutput();
    nor.UpdateOutput();
    triAnd.UpdateOutput();

    QCOMPARE(triAndOutputs[0]->GetValue(), false);

    //Test results - (0,0,1 --> 1)
    toggle1.SetPowerState(0);
    toggle2.SetPowerState(0);
    toggle3.SetPowerState(1);

    nand.UpdateOutput();
    nor.UpdateOutput();
    triAnd.UpdateOutput();

    QCOMPARE(triAndOutputs[0]->GetValue(), true);
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
    dynamic_cast<Gate*>(&nand)->GetDisconnectedInputNodes(nandInputs);
    dynamic_cast<Gate*>(&nand)->GetDisconnectedOutputNodes(nandOutputs);
    dynamic_cast<Gate*>(&nor)->GetDisconnectedInputNodes(norInputs);
    dynamic_cast<Gate*>(&nor)->GetDisconnectedOutputNodes(norOutputs);
    dynamic_cast<Gate*>(&triAnd)->GetDisconnectedInputNodes(triAndInputs);
    dynamic_cast<Gate*>(&triAnd)->GetDisconnectedOutputNodes(triAndOutputs);
    dynamic_cast<Gate*>(&toggle1)->GetDisconnectedOutputNodes(toggle1Node);
    dynamic_cast<Gate*>(&toggle2)->GetDisconnectedOutputNodes(toggle2Node);
    dynamic_cast<Gate*>(&toggle3)->GetDisconnectedOutputNodes(toggle3Node);

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
            loadedGates[5]->GetDisconnectedOutputNodes(output);

            QCOMPARE(output[0]->GetValue(), true);
        }
    }
}*/

QTEST_APPLESS_MAIN(Tests)
