#include "converter.h"
#include "circuit.h"
#include "allgates.h"

#include <cmath>
#include <QScriptEngine>

CircuitOptions::CircuitOptions(const bool& useInverseGates, const bool& nandOnly, const bool& largeInputGates, const int& maxSeconds, const ConversionAlgorithm& conversionAlgorithm) :
    m_bUseInverseGates(useInverseGates),
    m_bNandOnly(nandOnly),
    m_bLargeInputGates(largeInputGates),
    m_algorithm(conversionAlgorithm),
    m_maxSeconds(maxSeconds)
{
}

CircuitOptions::CircuitOptions() : CircuitOptions(false, false, false, 0)
{
}

bool isLetter(const char& letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {
        return true;
    }
    return false;
}

bool isLowercaseLetter(const char& letter)
{
    if(letter >= 'a' && letter <= 'z')
    {
        return true;
    }
    return false;
}

bool onlyDiffer1bit(QString& termA, QString& termB)
{
    int iDiffer = 0;

    for(int i = 0; i < termA.length(); i++)
    {
        if(termA[i] != termB[i])
        {
            iDiffer++;
            if(iDiffer > 1)
            {
                return false;
            }
        }
    }

    return iDiffer == 1;
}

// 0010 and 0110 becomes 0-10
QString mergeTerms(const QString& termA, const QString& termB)
{
    QString result = "";

    for(int i = 0; i < termA.length(); i++)
    {
        if(termA[i] != termB[i])
        {
            result+="-";
        }
        else
        {
            result+=termA[i];
        }
    }

    return result;
}

bool inVector(const std::vector<QString>& vec, const QString& str)
{
    for(uint i = 0; i < vec.size(); i++)
    {
        if(str == vec[i])
        {
            return true;
        }
    }
    return false;
}

std::vector<QString> reduceMinTerms(std::vector<QString> minTerms)
{
    std::vector<QString> newMinTerms;

    const uint minTermsSize = minTerms.size();

    std::vector<bool> checked = std::vector<bool>(minTermsSize, false);

    for(uint i = 0; i < minTermsSize; i++)
    {
        for(uint j = 0; j < minTermsSize; j++)
        {
            if(onlyDiffer1bit(minTerms[i], minTerms[j]))
            {
                checked[i] = true;
                checked[j] = true;

                const QString mergedTerms = mergeTerms(minTerms[i], minTerms[j]);
                if(!inVector(newMinTerms, mergedTerms))
                {
                    newMinTerms.push_back(mergedTerms);
                }
            }
        }
    }

    for(uint i = 0; i < minTermsSize; i++)
    {
        if(!checked[i] && !inVector(newMinTerms, minTerms[i]))
        {
            newMinTerms.push_back(minTerms[i]);
        }
    }

    return newMinTerms;
}

void addTranslatedMinTerm(QString& minTerm, BooleanExpression& expression, std::vector<char>& vars, const QString& dontCareMask)
{
    if(minTerm == dontCareMask)
    {
        expression.addTerm('1');
        return;
    }

    const uint minTermSize = minTerm.length() - 1;

    for(uint i = 0; i < minTermSize; i++)
    {
        if(minTerm[i] != "-")
        {
            if(minTerm[i] == '0')
            {
                expression.addTerm(vars[i], true);
            }
            else if(minTerm[i] == '1')
            {
                expression.addTerm(vars[i]);
            }
        }
    }

    if(minTerm[minTermSize] == '0')
    {
        expression.addTerm(vars[minTermSize], true);
    }
    else if(minTerm[minTermSize] == '1')
    {
        expression.addTerm(vars[minTermSize]);
    }
}

ConverterResult Converter::truthTableToBooleanExpressions(TruthTable& truthTable, const ConversionAlgorithm& /*conversionOptions*/, std::vector<BooleanExpression>& expressions)
{
    if(!truthTable.isValid())
    {
        Logger::log(LL_Error, "Converter::truthTableToBooleanExpressions - Invalid truth table provided");
        return INVALID_TABLE;
    }

    if(expressions.size() != 0)
    {
        expressions.clear();
        Logger::log(LL_Warn, "Converter::truthTableToBooleanExpressions - Cleared provided expressions");
    }

    //Todo ~ simplify

    // - Basic rule simplification
    // - Karnaugh maps simplification
    // - Quine-McCluskey algorithm

    //Todo use conversionOptions


    const uint numOutputs = truthTable.outValues[0].size();
    const uint numRuns = truthTable.inValues.size();
    const uint numInputs = truthTable.inValues[0].size();

    QString dontCaresMask = "";
    for(uint i = 0; i < numInputs; i++)
    {
        dontCaresMask += "-";
    }

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        BooleanExpression expression;
        expression.resultLetter = truthTable.outLetters[iOutput];

        //Get min terms
        std::vector<QString> minTerms;
        for(uint iTableRun = 0; iTableRun < numRuns; iTableRun++)
        {
            if(truthTable.outValues[iTableRun][iOutput])
            {
                QString minTerm = "";
                for(const bool input : truthTable.inValues[iTableRun])
                {
                    minTerm += (input ? "1" : "0");
                }
                minTerms.push_back(minTerm);
            }
        }

        //Reduce min terms
        std::sort(minTerms.begin(), minTerms.end());
        std::vector<QString> oldMinTerms;
        while(true)
        {
            oldMinTerms = minTerms;
            minTerms = reduceMinTerms(minTerms);

            std::sort(minTerms.begin(), minTerms.end());

            if(oldMinTerms == minTerms)
            {
                break;
            }
        }


        const int minTermsSize = minTerms.size() - 1;
        if(minTermsSize < 0)
        {
            return INVALID_INPUT_EXPRESSIONS;
        }

        //Translate reduced min terms into boolean expression
        for(int iMinTerm = 0; iMinTerm < minTermsSize; iMinTerm++)
        {
            addTranslatedMinTerm(minTerms[iMinTerm], expression, truthTable.inLetters, dontCaresMask);
            expression.addTerm('+');
        }
        addTranslatedMinTerm(minTerms[minTermsSize], expression, truthTable.inLetters, dontCaresMask);

        //Finish
        expressions.push_back(expression);
    }

    return SUCCESS;
}

//If input values match up with expression letters being inverted or not
bool expressionToResult(const std::vector<bool>& inValues, std::vector<char>& inputLetters, const BooleanExpression& expression)
{
    //New algorithm
    QString expressionToInts;
    for(uint i = 0; i < expression.letters.size(); i++)
    {
        const char currentExpressionLetter = expression.letters[i];

        if(currentExpressionLetter == '+')
        {
            expressionToInts.push_back('|');
            continue;
        }

        if(currentExpressionLetter == '!' || currentExpressionLetter == '(' || currentExpressionLetter == ')' || currentExpressionLetter == '&' || currentExpressionLetter == '^')
        {
            expressionToInts.push_back(currentExpressionLetter);
            continue;
        }

        if(currentExpressionLetter == '.')
        {
            expressionToInts.push_back('&');
            continue;
        }

        for(uint j = 0; j < inputLetters.size(); j++)
        {
            if(inputLetters[j] == currentExpressionLetter)
            {
                expressionToInts.push_back(QString::number(inValues[j]));
                break;
            }
        }
    }

    QString expressionAsBooleanOperation;
    for(uint i = 0; i < expressionToInts.size(); i++)
    {
        expressionAsBooleanOperation.push_back(expressionToInts[i]);
        if(i < expressionToInts.size() - 1 && (expressionToInts[i] == "0" || expressionToInts[i] == "1") && ((expressionToInts[i+1] == "0" || expressionToInts[i+1] == "1") || expressionToInts[i+1] == "(" || expressionToInts[i+1] == "!"))
        {
            expressionAsBooleanOperation += "&";
        }
    }

    QScriptEngine engine;
    QScriptContext* pContext = engine.pushContext();//I think this gets deleted by engine destructor

    const QString script = "outputVar = " + expressionAsBooleanOperation + ";";

    pContext->activationObject().setProperty("outputVar", false);

    //Run script
    engine.evaluate(script);

    return pContext->activationObject().property("outputVar").toBool();
}

ConverterResult Converter::expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable)
{
    if(!truthTable.isEmptyTable())
    {
        Logger::log(LL_Error, "Converter::expressionsToTruthTable - Invalid input truth table");
        return INVALID_TABLE;
    }

    //Get inputs and outputs
    for(BooleanExpression expression : expressions)
    {
        for(uint i = 0; i < expression.letters.size(); i++)
        {
            const char letter = expression.letters[i];
            if(isLetter(letter) && !truthTable.inInputs(letter))
            {
                truthTable.inLetters.push_back(letter);
            }
        }

        if(!truthTable.inOutputs(expression.resultLetter))
        {
            truthTable.outLetters.push_back(expression.resultLetter);
        }
    }

    //Generate input values
    truthTable.genInputs(truthTable.inLetters.size());

    //Generate output values
    for(uint i = 0; i < truthTable.inValues.size(); i++)
    {
        truthTable.outValues.push_back(std::vector<bool>());
        for(uint iOutput = 0; iOutput < truthTable.outLetters.size(); iOutput++)
        {
            truthTable.outValues[i].push_back(expressionToResult(truthTable.inValues[i], truthTable.inLetters, expressions[iOutput]));
        }
    }

    return SUCCESS;
}

ConverterResult Converter::simplifyBooleanExpressions(std::vector<BooleanExpression>& expressions, const ConversionAlgorithm& conversionOptions)
{
    //This is just simplification option 1. Using Quine-McCluskey algorithm

    TruthTable truthTable;
    ConverterResult result = expressionsToTruthTable(expressions, truthTable);
    if(result != ConverterResult::SUCCESS)
    {
        return result;
    }

    expressions.clear();
    return truthTableToBooleanExpressions(truthTable, conversionOptions, expressions);
}

bool isLetterOrInt(const char& letter)
{
    if(isLetter(letter) || (letter >= 48 && letter <= 57))
    {
        return true;
    }
    return false;
}

bool linkNodes(Node*& pNodeA, Node*& pNodeB)
{
    bool linked = pNodeA->linkNode(pNodeB);
    linked &= pNodeB->linkNode(pNodeA);
    return linked;
}

bool inCharVec(const std::vector<char>& vec, const char& chr)
{
    for(uint i = 0; i < vec.size(); i++)
    {
        if(chr == vec[i])
        {
            return true;
        }
    }
    return false;
}

void findAndMakeLinks(Gate* pGate, Gate* pNewGate, NodeIds& linkInfoInput1, NodeIds& linkInfoInput2, NodeIds& linkInfoOutput)
{
    for(int id : linkInfoInput1.linkedIds)
    {
        Node* pNode;
        if(pGate->findNodeWithId(id, pNode))
        {
            linkNodes(pNewGate->getInputNodes()[0], pNode);
        }
    }

    for(int id : linkInfoInput2.linkedIds)
    {
        Node* pNode;
        if(pGate->findNodeWithId(id, pNode))
        {
            linkNodes(pNewGate->getInputNodes()[1], pNode);
        }
    }

    for(int id : linkInfoOutput.linkedIds)
    {
        Node* pNode;
        if(pGate->findNodeWithId(id, pNode))
        {
            linkNodes(pNewGate->getOutputNodes()[0], pNode);
        }
    }
}

void linkReplacementFromCircuit(Gate* pOldGate, Gate* pNewGate, Circuit& circuit)
{
    NodeIds linkInfoInput1 = pOldGate->getInputNodes()[0]->linkInfo();
    NodeIds linkInfoInput2 = pOldGate->getInputNodes()[1]->linkInfo();
    NodeIds linkInfoOutput = pOldGate->getOutputNodes()[0]->linkInfo();

    for(Gate* pGate : circuit.mainGates)
    {
        findAndMakeLinks(pGate, pNewGate, linkInfoInput1, linkInfoInput2, linkInfoOutput);
    }

    for(std::pair<char, Gate*> inputGateAndLetter : circuit.inputs)
    {
        Gate* pGate = inputGateAndLetter.second;
        findAndMakeLinks(pGate, pNewGate, linkInfoInput1, linkInfoInput2, linkInfoOutput);
    }
}

void replaceDoubleInputGate(Gate* pNewGate, Circuit& circuit, std::map<char, Gate*>& circuitGates, const char& circuitGate)
{
    Gate* pOldGate = circuitGates[circuitGate];
    linkReplacementFromCircuit(pOldGate, pNewGate, circuit);

    for(uint i = 0; i < circuit.mainGates.size(); i++)
    {
        if(circuit.mainGates[i] == pOldGate)
        {
            circuit.mainGates.erase(circuit.mainGates.begin() + i);
            break;
        }
    }
    delete pOldGate;

    circuit.mainGates.push_back(pNewGate);
    circuitGates[circuitGate] = pNewGate;

}
//TODO ~ GOT TO WORK IN XOR OPERATOR
Node* getNode(BooleanExpression& expression, uint& i, Circuit& circuit, std::map<char, Gate*>& circuitGates, std::map<char, Gate*>& invertLetterGates)
{
    if(expression.letters[i] == '!')
    {
        i++;
        if(invertLetterGates.find(expression.letters[i]) != invertLetterGates.end())
        {
            return invertLetterGates[expression.letters[i]]->getOutputNodes()[0];
        }
        else if(isLowercaseLetter(expression.letters[i]))
        {
            if(circuitGates[expression.letters[i]]->getType() == GateType::GATE_AND)
            {
                GateNand* pNand = new GateNand();
                replaceDoubleInputGate(pNand, circuit, circuitGates, expression.letters[i]);
                return circuitGates[expression.letters[i]]->getOutputNodes()[0];
            }
            else if(circuitGates[expression.letters[i]]->getType() == GateType::GATE_OR)
            {
                GateNor* pNor = new GateNor();
                replaceDoubleInputGate(pNor, circuit, circuitGates, expression.letters[i]);
                return circuitGates[expression.letters[i]]->getOutputNodes()[0];
            }

            //TODO ~ ADD XNOR

            GateNot* pNot = new GateNot();
            linkNodes(circuitGates[expression.letters[i]]->getOutputNodes()[0], pNot->getInputNodes()[0]);
            circuit.mainGates.push_back(pNot);
            return pNot->getOutputNodes()[0];
        }
        else
        {
            GateNot* pNot = new GateNot();
            linkNodes(circuit.inputs[expression.letters[i]]->getOutputNodes()[0], pNot->getInputNodes()[0]);
            invertLetterGates[expression.letters[i]] = pNot;
            circuit.mainGates.push_back(pNot);
            return pNot->getOutputNodes()[0];
        }
    }
    else if(isLetter(expression.letters[i]))
    {
        return circuit.inputs[expression.letters[i]]->getOutputNodes()[0];
    }
    else if(isLowercaseLetter(expression.letters[i]))
    {
        return circuitGates[expression.letters[i]]->getOutputNodes()[0];
    }
    else
    {
        //Issue
        return nullptr;
    }
}

void turnSectionIntoCircuit(BooleanExpression& expression, uint iStart, uint iEnd, Circuit& circuit, std::map<char, Gate*>& circuitGates, std::map<char, Gate*>& invertLetterGates, char& gatesCounter)
{
    for(uint i = iStart; i < iEnd; i++)
    {
        uint iNext = i;
        Node* pFirstNode = getNode(expression, iNext, circuit, circuitGates, invertLetterGates);
        if(pFirstNode == nullptr)
        {
            return;
        }

        iNext++;
        if(iNext > iEnd)
        {
            return;
        }

        Node* pSecondNode = nullptr;
        if(expression.letters[iNext] == '+' || expression.letters[iNext] == '|')
        {
            iNext++;
            pSecondNode = getNode(expression, iNext, circuit, circuitGates, invertLetterGates);
            if(pSecondNode == nullptr)
            {
                return;
            }

            GateOr* pOr = new GateOr();
            linkNodes(pOr->getInputNodes()[0], pFirstNode);
            linkNodes(pOr->getInputNodes()[1], pSecondNode);

            circuit.mainGates.push_back(pOr);
            circuitGates[++gatesCounter] = pOr;
        }
        else if(expression.letters[iNext] == '^')
        {
            iNext++;
            pSecondNode = getNode(expression, iNext, circuit, circuitGates, invertLetterGates);
            if(pSecondNode == nullptr)
            {
                return;
            }

            GateXor* pXor = new GateXor();
            linkNodes(pXor->getInputNodes()[0], pFirstNode);
            linkNodes(pXor->getInputNodes()[1], pSecondNode);

            circuit.mainGates.push_back(pXor);
            circuitGates[++gatesCounter] = pXor;
        }
        else
        {
            if(expression.letters[iNext] == '&' || expression.letters[iNext] == '.')
            {
                iNext++;
            }

            pSecondNode = getNode(expression, iNext, circuit, circuitGates, invertLetterGates);
            if(pSecondNode == nullptr)
            {
                return;
            }

            GateAnd* pAnd = new GateAnd();
            linkNodes(pAnd->getInputNodes()[0], pFirstNode);
            linkNodes(pAnd->getInputNodes()[1], pSecondNode);

            circuit.mainGates.push_back(pAnd);
            circuitGates[++gatesCounter] = pAnd;
        }

        expression.letters[i] = gatesCounter;
        for(uint iRemove = i+1; iRemove <= iNext; iRemove++)
        {
            expression.letters.erase(expression.letters.begin() + i + 1);
            iEnd--;
        }
    }
}

void dealWithBrackets(BooleanExpression& expression, uint iBracket, Circuit& circuit, std::map<char, Gate*>& circuitGates, std::map<char, Gate*>& invertLetterGates, char& gatesCounter)
{
    for(uint i = iBracket+1; i < expression.letters.size(); i++)
    {
        if(expression.letters[i] == ')')
        {
            expression.letters.erase(expression.letters.begin() + iBracket); //Remove (
            expression.letters.erase(expression.letters.begin() + i - 1); //Remove )
            turnSectionIntoCircuit(expression, iBracket, i-2, circuit, circuitGates, invertLetterGates, gatesCounter);
            return;
        }
        else if(expression.letters[i] == '(')
        {
            dealWithBrackets(expression, i, circuit, circuitGates, invertLetterGates, gatesCounter);
        }
    }
}

ConverterResult Converter::booleanExpressionsToCircuit(std::vector<BooleanExpression> expressions, const CircuitOptions &circuitOptions, GateCollection *&pNewCircuit)
{
    //Todo ~ simplification - Either properly or by converting to truth table putting it through truthTableToBooleanExpressions

    std::vector<char> inputLetters;
    std::vector<char> outputLetters;
    for(BooleanExpression& expression : expressions)
    {
        for(char& letter : expression.letters)
        {
            if(isLetter(letter))
            {
                if(!inCharVec(inputLetters, letter))
                {
                    inputLetters.push_back(letter);
                }
            }
        }

        if(!inCharVec(outputLetters, expression.resultLetter))
        {
            outputLetters.push_back(expression.resultLetter);
        }
    }

    const uint numOutputs = outputLetters.size();
    const uint numInputs = inputLetters.size();
    if(numOutputs == 0 || numInputs == 0)
    {
        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Inputs or outputs count equals 0");
        return INVALID_INPUT_EXPRESSIONS;
    }

    Circuit circuit(inputLetters, outputLetters);
    std::map<char, Gate*> circuitGates;
    std::map<char, Gate*> invertLetterGates;
    char gatesCounter = 'a';

    for(BooleanExpression& expression : expressions)
    {

        //Get rid of brackets
        for(uint i = 0; i < expression.letters.size(); i++)
        {
            if(expression.letters[i] == '(')
            {
                dealWithBrackets(expression, i, circuit, circuitGates, invertLetterGates, gatesCounter);
            }
        }

        //Convert rest
        turnSectionIntoCircuit(expression, 0, expression.letters.size()-1, circuit, circuitGates, invertLetterGates, gatesCounter);

        if(expression.letters.size() == 1)
        {
            if(isLetter(expression.letters[0]))
            {
                linkNodes(circuit.inputs[expression.letters[0]]->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
            }
            else if(isLowercaseLetter(expression.letters[0]))
            {
                linkNodes(circuitGates[expression.letters[0]]->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
            }
            else
            {
                //Issue
                return INVALID_INPUT_EXPRESSIONS;
            }
        }
        else if(expression.letters.size() == 2)
        {
            if(expression.letters[0] == '!')
            {
                if(isLowercaseLetter(expression.letters[1]))
                {
                    if(circuitGates[expression.letters[1]]->getType() == GateType::GATE_AND)
                    {
                        GateNand* pNand = new GateNand();
                        replaceDoubleInputGate(pNand, circuit, circuitGates, expression.letters[1]);
                        linkNodes(circuitGates[expression.letters[1]]->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
                    }
                    else if(circuitGates[expression.letters[1]]->getType() == GateType::GATE_OR)
                    {
                        GateNor* pNor = new GateNor();
                        replaceDoubleInputGate(pNor, circuit, circuitGates, expression.letters[1]);
                        linkNodes(circuitGates[expression.letters[1]]->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
                    }
                    else
                    {
                        GateNot* pNot = new GateNot();
                        linkNodes(circuitGates[expression.letters[1]]->getOutputNodes()[0], pNot->getInputNodes()[0]);
                        circuit.mainGates.push_back(pNot);
                        linkNodes(pNot->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
                    }
                }
                else if(isLetter(expression.letters[1]))
                {
                    if(invertLetterGates.find(expression.letters[1]) != invertLetterGates.end())
                    {
                        linkNodes(invertLetterGates[expression.letters[1]]->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
                    }
                    else
                    {
                        GateNot* pNot = new GateNot();
                        linkNodes(circuit.inputs[expression.letters[1]]->getOutputNodes()[0], pNot->getInputNodes()[0]);
                        invertLetterGates[expression.letters[1]] = pNot;
                        circuit.mainGates.push_back(pNot);
                        linkNodes(pNot->getOutputNodes()[0], circuit.outputs[expression.resultLetter]->getInputNodes()[0]);
                    }
                }
                else
                {
                    return INVALID_INPUT_EXPRESSIONS;
                }
            }
        }
        else
        {
            return INVALID_INPUT_EXPRESSIONS;
        }
    }

    pNewCircuit = circuit.createGateCollection();
    return SUCCESS;
}

ConverterResult Converter::truthTableToCircuit(TruthTable& truthTable, const CircuitOptions& circuitOptions, GateCollection*& pNewCircuit)
{
    std::vector<BooleanExpression> expressions;
    ConverterResult res = truthTableToBooleanExpressions(truthTable, circuitOptions.m_algorithm, expressions);

    if(res != ConverterResult::SUCCESS)
    {
        return res;
    }

    return booleanExpressionsToCircuit(expressions, circuitOptions, pNewCircuit);
}

ConverterResult Converter::scriptToCircuit(const QString &script, const uint &numInputs, const uint &numOutputs, const CircuitOptions& circuitOptions, GateCollection *&pNewCircuit, int& failedLineNumber)
{
    TruthTable tt;
    ConverterResult res = scriptToTruthTable(script, numInputs, numOutputs, tt, failedLineNumber);

    if(res != ConverterResult::SUCCESS)
    {
        return res;
    }

    return truthTableToCircuit(tt, circuitOptions, pNewCircuit);
}

ConverterResult Converter::scriptToTruthTable(const QString &script, const uint &numInputs, const uint &numOutputs, TruthTable &truthTable, int& failedLineNumber)
{
    if(!truthTable.isEmptyTable())
    {
        Logger::log(LL_Error, "Converter::scriptToTruthTable - Invalid input truth table");
        return INVALID_TABLE;
    }

    QScriptEngine engine;
    QScriptContext* pContext = engine.pushContext();//I think this gets deleted by engine destructor

    std::vector<QString> inputVariables;
    for(uint i = 1; i <= numInputs; i++)
    {
        inputVariables.push_back("input" + QString::number(i));
        truthTable.inLetters.push_back('A'-1+i);
    }

    std::vector<QString> outputVariables;
    for(uint i = 1; i <= numOutputs; i++)
    {
        outputVariables.push_back("output" + QString::number(i));
        pContext->activationObject().setProperty("output" + QString::number(i), false);
        truthTable.outLetters.push_back('Z'+1-i);
    }

    truthTable.genInputs(numInputs);
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        //Set input values for script
        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            pContext->activationObject().setProperty(inputVariables[iInput], (bool)truthTable.inValues[iTableRun][iInput]);
        }

        //Run script
        engine.evaluate(script);

        if(engine.hasUncaughtException())
        {
            failedLineNumber = engine.uncaughtExceptionLineNumber();
            return INVALID_SCRIPT;
        }

        //Collect output values from script
        std::vector<bool> genOutputValues;
        for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
        {
            genOutputValues.push_back(pContext->activationObject().property(outputVariables[iOutput]).toBool());
        }
        truthTable.outValues.push_back(genOutputValues);
    }

    return ConverterResult::SUCCESS;
}

ConverterResult Converter::scriptToBooleanExpressions(const QString& script, const uint& numInputs, const uint& numOutputs, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions, int& failedLineNumber)
{
    TruthTable tt;
    ConverterResult res = scriptToTruthTable(script, numInputs, numOutputs, tt, failedLineNumber);

    if(res != ConverterResult::SUCCESS)
    {
        return res;
    }

    return truthTableToBooleanExpressions(tt, conversionOptions, expressions);
}

ConverterResult Converter::circuitToTruthTable(std::vector<Gate*> gates, TruthTable &truthTable)
{
    if(!truthTable.isEmptyTable())
    {
        Logger::log(LL_Error, "Converter::circuitToTruthTable - Invalid input truth table");
        return INVALID_TABLE;
    }

    //Check for external connections
    for (Gate* gate : gates)
    {
        std::vector<NodeIds> linkInfo;
        gate->collectLinkInfo(linkInfo);

        for(NodeIds nodeIds : linkInfo)
        {
            for(int linkId : nodeIds.linkedIds)
            {
                Node* pNode;
                bool found = false;
                for (Gate* gate : gates)
                {
                    if(gate->findNodeWithId(linkId, pNode))
                    {
                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    Logger::log(LL_Error, "Converter::circuitToTruthTable : Failed. Circuit includes external connections!");
                    return INVALID_CIRCUIT;
                }
            }
        }
    }

    //Collect circuit
    std::vector<GateToggle*> inputGates;
    std::vector<Gate*> mainGates;
    std::vector<GateReciever*> resultGates;
    for (Gate* g : gates)
    {
        if(g->getType() == GateType::GATE_EMMITTER)
        {
            if(dynamic_cast<GateToggle*>(g))
            {
                inputGates.push_back(dynamic_cast<GateToggle*>(g));
            }
            else
            {
                Logger::log(LL_Error, "Converter::circuitToTruthTable - Failed to cast GateToggle");
                return INVALID_CIRCUIT;
            }
        }

        else if(g->getType() == GateType::GATE_RECIEVER)
        {
            if(dynamic_cast<GateReciever*>(g))
            {
                resultGates.push_back(dynamic_cast<GateReciever*>(g));
            }
            else
            {
                Logger::log(LL_Error, "Converter::circuitToTruthTable - Failed to cast GateReciever");
                return INVALID_CIRCUIT;
            }
        }

        else if(g->getType() == GateType::GATE_TIMER || g->getType() == GateType::GATE_NULL || g->getType() == GateType::GATE_COLLECTION)
        {
            Logger::log(LL_Error, "Converter::circuitToTruthTable : Failed. Unsupported gate type for truth table. No nested gate collections. No timer gates.");
            return INVALID_CIRCUIT;
        }

        else
        {
            mainGates.push_back(g);
        }
    }

    if(inputGates.empty())
    {
        Logger::log(LL_Error, "Converter::circuitToTruthTable : Failed to generate. No input(emmiter) gates.");
        return INVALID_CIRCUIT;
    }

    if(resultGates.empty())
    {
        Logger::log(LL_Error, "Converter::circuitToTruthTable : Failed to generate. No result(reciever) gates.");
        return INVALID_CIRCUIT;
    }

    const uint numInputs = inputGates.size();
    const uint numOutputs = resultGates.size();
    const uint numMainGates = mainGates.size();

    truthTable.addInputLetters(numInputs);
    truthTable.addOutputLetters(numOutputs);

    truthTable.genInputs(numInputs);
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            inputGates[iInput]->setPowerState(truthTable.inValues[iTableRun][iInput]);
        }

        //Must be a better way of doing this...
        for(uint i = 0; i < numMainGates; i++)
        {
            for(Gate* g : mainGates)
            {
                g->updateOutput();
            }
        }

        //Generate output values
        std::vector<bool> outputValues;
        for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
        {
            outputValues.push_back(resultGates[iOutput]->getValue());
        }
        truthTable.outValues.push_back(outputValues);
    }

    return SUCCESS;
}

ConverterResult Converter::circuitToBooleanExpressions(std::vector<Gate*> gates, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions)
{
    TruthTable truthTable;
    ConverterResult result = circuitToTruthTable(gates, truthTable);
    if(result != ConverterResult::SUCCESS)
    {
        return result;
    }

    return truthTableToBooleanExpressions(truthTable, conversionOptions, expressions);
}

ConverterResult Converter::kmapToBooleanExpressions(const KarnaughMap& kmap, std::vector<BooleanExpression> &expressions)
{
    const int width = kmap.values.size();
    if(width == 0)
    {
        return INVALID_TABLE;
    }

    const int height = kmap.values[0].size();
    if(height == 0)
    {
        return INVALID_TABLE;
    }

    BooleanExpression expression;
    expression.resultLetter = kmap.outputLetter;

    SpillProofValues kmapValues;
    kmapValues.values = kmap.values;
    kmapValues.width = width;
    kmapValues.height = height;

    std::vector<std::vector<QPoint>> groupedValues;

    std::vector<QPoint> directions = {QPoint(0, 1), QPoint(1, 0), QPoint(0, -1), QPoint(-1, 0)};

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            for(int direction = 0; direction < 4; direction++)
            {
                if(kmapValues.getValue(x, y))
                {
                    //Two together
                    if(kmapValues.getValue(x + directions[direction].x(), y + directions[direction].y()))
                    {

                    }
                }
            }
        }
    }
}
