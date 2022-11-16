#include "converter.h"
#include "circuit.h"
#include "allgates.h"

#include <cmath>
#include <QScriptEngine>

CircuitOptions::CircuitOptions(const bool& useInverseGates, const bool& nandOnly, const bool& largeInputGates, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates, const ConversionAlgorithm& conversionAlgorithm) :
    m_bUseInverseGates(useInverseGates),
    m_bNandOnly(nandOnly),
    m_bLargeInputGates(largeInputGates),
    m_algorithm(conversionAlgorithm),
    m_maxSeconds(maxSeconds),
    m_percentageRandomGate(percentageRandomGate),
    m_maxGates(maxGates)
{
}

CircuitOptions::CircuitOptions() : CircuitOptions(false, false, false, 0, 0, 0)
{
}

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;
}

bool isLetter(const char& letter)
{
    if(letter >= (int)Settings::IntStartAlphabet && letter <= (int)Settings::IntEndAlphabet)
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
    if(truthTable.inValues.size() == 0 || truthTable.outValues.size() == 0)
    {
        return INVALID_TABLE;
    }

    if(expressions.size() != 0)
    {
        return INVALID_INPUT_EXPRESSIONS;
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

    std::vector<char> vars;
    for(uint i = 0; i < numInputs; i++)
    {
        vars.push_back(char(Settings::IntStartAlphabet + i));
    }

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        BooleanExpression expression;
        expression.resultLetter = Settings::IntEndAlphabet - iOutput;

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
            addTranslatedMinTerm(minTerms[iMinTerm], expression, vars, dontCaresMask);
            expression.addTerm('+');
        }
        addTranslatedMinTerm(minTerms[minTermsSize], expression, vars, dontCaresMask);

        //Finish
        expressions.push_back(expression);
    }

    return SUCCESS;
}

bool inVector(const std::vector<char>& vector, const char& value)
{
    for(const char& letter : vector)
    {
        if(letter == value)
        {
            return true;
        }
    }
    return false;
}

//If input values match up with expression letters being inverted or not
bool expressionToResult(const std::vector<bool>& inValues, std::vector<char>& inputLetters, const BooleanExpression& expression)
{
    for(uint i = 0; i < inValues.size(); i++)
    {
        const char letter = inputLetters[i];
        for(uint j = 0; j < expression.letters.size(); j++)
        {
            if(expression.letters[j] == letter)
            {
                if(expression.isInverted(j) == inValues[i])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

ConverterResult Converter::expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable)
{
    if(truthTable.inValues.size() != 0 || truthTable.outValues.size() != 0 || truthTable.size != 0 || truthTable.inLetters.size() != 0 || truthTable.outLetters.size() != 0)
    {
        return INVALID_TABLE;
    }

    //Get inputs and outputs
    for(BooleanExpression expression : expressions)
    {
        for(uint i = 0; i < expression.letters.size(); i++)
        {
            const char letter = expression.letters[i];
            if(isLetter(letter) && !inVector(truthTable.inLetters, letter))
            {
                truthTable.inLetters.push_back(letter);
            }
        }

        if(!inVector(truthTable.outLetters, expression.resultLetter))
        {
            truthTable.outLetters.push_back(expression.resultLetter);
        }
    }

    //Generate input values
    truthTable.size = pow(2, truthTable.inLetters.size());
    for(uint i = 0; i < truthTable.size; i++)
    {
        truthTable.inValues.push_back(truthTable.genInputs(i, truthTable.inLetters.size()));
    }

    //Generate output values
    for(uint i = 0; i < truthTable.inValues.size(); i++)
    {
        truthTable.outValues.push_back(std::vector<bool>());
        for(uint iOutput = 0; iOutput < truthTable.outValues.size(); iOutput++)
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
    if((letter >= (int)Settings::IntStartAlphabet && letter <= (int)Settings::IntEndAlphabet) || (letter >= 48 && letter <= 57))
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

ConverterResult Converter::booleanExpressionsToCircuit(std::vector<BooleanExpression> expressions, const CircuitOptions& /*circuitOptions*/, GateCollection*& pNewCircuit)
{
    //Todo ~ simplification - Either properly or by converting to truth table putting it through truthTableToBooleanExpressions
    //Todo ~ not gate options (like NAND and NOR)

    std::vector<char> inputLetters;
    std::vector<char> outputLetters;
    for(BooleanExpression& expression : expressions)
    {
        for(char& letter : expression.letters)
        {
            if(isLetter(letter))
            {
                if(!inVector(inputLetters, letter))
                {
                    inputLetters.push_back(letter);
                }
            }
        }
        outputLetters.push_back(expression.resultLetter);
    }

    const uint numOutputs = expressions.size();
    const uint numInputs = inputLetters.size();
    if(numOutputs == 0 || numInputs == 0)
    {
        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Inputs or outputs count equals 0");
        return INVALID_INPUT_EXPRESSIONS;
    }

    Circuit circuit(inputLetters, outputLetters);
    std::map<char, Gate*> circuitGates;
    std::map<char, Gate*> invertLetterGates;
    int sumGateCounter = 0;

    for(BooleanExpression& expression : expressions)
    {
        const char outputLetter = expression.resultLetter;
        bool changed = true;
        while(expression.letters.size() > 0)
        {
            changed = false;

            //Look for AND jobs
            for(uint iLetter = 0; iLetter < expression.letters.size()-1; iLetter++)
            {
                const bool firstItemInverted = iLetter > 0 && expression.letters[iLetter-1] == '!';
                const char firstItem = expression.letters[iLetter];
                const bool nextItemInverted = expression.letters[iLetter+1] == '!';
                const char nextItem = nextItemInverted ? expression.letters[iLetter+2] : expression.letters[iLetter+1];

                if(isLetterOrInt(firstItem) && isLetterOrInt(nextItem))
                {
                    Gate* input1Gate;
                    if(firstItemInverted)
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(firstItem) != invertLetterGates.end())
                        {
                            input1Gate = invertLetterGates[firstItem];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input1Gate = new GateNot();
                            if(!linkNodes(circuit.inputs[firstItem]->getOutputNodes()[0], input1Gate->getInputNodes()[0]))
                            {
                                Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                                return INVALID_INPUT_EXPRESSIONS;
                            }
                            invertLetterGates[firstItem] = input1Gate;
                            circuit.mainGates.push_back(input1Gate);
                        }
                    }
                    else if(isLetter(firstItem))
                    {
                        input1Gate = circuit.inputs[firstItem];
                    }
                    else
                    {
                        input1Gate = circuitGates[firstItem];
                    }

                    Gate* input2Gate;
                    if(nextItemInverted)
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(nextItem) != invertLetterGates.end())
                        {
                            input2Gate = invertLetterGates[nextItem];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input2Gate = new GateNot();
                            if(!linkNodes(circuit.inputs[nextItem]->getOutputNodes()[0], input2Gate->getInputNodes()[0]))
                            {
                                Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                                return INVALID_INPUT_EXPRESSIONS;
                            }
                            invertLetterGates[nextItem] = input2Gate;
                            circuit.mainGates.push_back(input2Gate);
                        }
                    }
                    else if(isLetter(nextItem))
                    {
                        input2Gate = circuit.inputs[nextItem];
                    }
                    else
                    {
                        input2Gate = circuitGates[nextItem];
                    }

                    Gate* andGate = new GateAnd();
                    if(!linkNodes(andGate->getInputNodes()[0], input1Gate->getOutputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    if(!linkNodes(andGate->getInputNodes()[1], input2Gate->getOutputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    circuit.mainGates.push_back(andGate);
                    circuitGates[48 + sumGateCounter] = andGate;

                    //Replace A.B with 1
                    expression.letters[iLetter - int(firstItemInverted)] = 48 + sumGateCounter;
                    for(int i = 0; i < 1 + int(firstItemInverted) + int(nextItemInverted); i++)
                    {
                        expression.letters.erase(expression.letters.begin() + iLetter + 1 - int(firstItemInverted));
                    }

                    sumGateCounter++;
                    changed = true;

                    if(expression.letters.size() == 1)
                    {
                        if(!linkNodes(circuit.outputs[outputLetter]->getInputNodes()[0], andGate->getOutputNodes()[0]))
                        {
                            Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                            return INVALID_INPUT_EXPRESSIONS;
                        }
                        expression.letters.clear();
                    }

                    break;
                }
            }

            if(changed)
            {
                continue;
            }

            //Look for OR jobs
            for(uint iLetter = 0; iLetter < expression.letters.size()-1; iLetter++)
            {
                if(expression.letters[iLetter] == '+' && iLetter > 0 && iLetter < expression.letters.size()-1)
                {
                    //Todo ~ notted sums

                    const bool firstItemInverted = iLetter > 1 && expression.letters[iLetter-2] == '!';
                    const char firstItem = expression.letters[iLetter-1];
                    const bool nextItemInverted = expression.letters[iLetter+1] == '!';
                    const char nextItem = nextItemInverted ? expression.letters[iLetter+2] : expression.letters[iLetter+1];

                    Gate* input1Gate;
                    if(firstItemInverted)
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(firstItem) != invertLetterGates.end())
                        {
                            input1Gate = invertLetterGates[firstItem];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input1Gate = new GateNot();
                            if(!linkNodes(input1Gate->getInputNodes()[0], circuit.inputs[firstItem]->getOutputNodes()[0]))
                            {
                                Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                                return INVALID_INPUT_EXPRESSIONS;
                            }
                            invertLetterGates[firstItem] = input1Gate;
                            circuit.mainGates.push_back(input1Gate);
                        }
                    }
                    else if(isLetter(firstItem))
                    {
                        input1Gate = circuit.inputs[firstItem];
                    }
                    else
                    {
                        input1Gate = circuitGates[firstItem];
                    }

                    Gate* input2Gate;
                    if(nextItemInverted)
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(nextItem) != invertLetterGates.end())
                        {
                            input2Gate = invertLetterGates[nextItem];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input2Gate = new GateNot();
                            if(!linkNodes(circuit.inputs[nextItem]->getOutputNodes()[0], input2Gate->getInputNodes()[0]))
                            {
                                Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                                return INVALID_INPUT_EXPRESSIONS;
                            }
                            invertLetterGates[nextItem] = input2Gate;
                            circuit.mainGates.push_back(input2Gate);
                        }
                    }
                    else if(isLetter(nextItem))
                    {
                        input2Gate = circuit.inputs[nextItem];
                    }
                    else
                    {
                        input2Gate = circuitGates[nextItem];
                    }

                    Gate* orGate = new GateOr();
                    if(!linkNodes(orGate->getInputNodes()[0], input1Gate->getOutputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    if(!linkNodes(orGate->getInputNodes()[1], input2Gate->getOutputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    circuit.mainGates.push_back(orGate);
                    circuitGates[48 + sumGateCounter] = orGate;

                    //Replace A+B with 1
                    expression.letters[firstItemInverted ? iLetter-2 : iLetter-1] = 48 + sumGateCounter;
                    for(int i = 0; i < 2 + int(firstItemInverted) + int(nextItemInverted); i++)
                    {
                        expression.letters.erase(expression.letters.begin() + iLetter - int(firstItemInverted));
                    }

                    sumGateCounter++;
                    changed = true;

                    if(expression.letters.size() == 1)
                    {
                        if(!linkNodes(circuit.outputs[outputLetter]->getInputNodes()[0], orGate->getOutputNodes()[0]))
                        {
                            Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                            return INVALID_INPUT_EXPRESSIONS;
                        }
                        expression.letters.clear();
                    }

                    break;
                }
            }

            if(changed)
            {
                continue;
            }

            if(expression.letters.size() > 0)
            {
                char letter;
                bool isInverted;
                if(expression.letters[0] == '!')
                {
                    if(expression.letters.size() > 1 && isLetter(expression.letters[1]))
                    {
                        letter = expression.letters[1];
                        isInverted = true;
                    }
                    else
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid expression design");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                }
                else if(isLetter(expression.letters[0]))
                {
                    letter = expression.letters[0];
                    isInverted = false;
                }
                else
                {
                    Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid expression design");
                    return INVALID_INPUT_EXPRESSIONS;
                }

                if(isInverted)
                {
                    Gate* notGate = new GateNot();
                    if(!linkNodes(circuit.inputs[letter]->getOutputNodes()[0], notGate->getInputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    if(!linkNodes(notGate->getOutputNodes()[0], circuit.outputs[outputLetter]->getInputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }

                    invertLetterGates[letter] = notGate;
                    circuit.mainGates.push_back(notGate);

                    expression.letters.clear();
                }
                else
                {
                    if(!linkNodes(circuit.outputs[outputLetter]->getInputNodes()[0], circuit.inputs[letter]->getOutputNodes()[0]))
                    {
                        Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid node link");
                        return INVALID_INPUT_EXPRESSIONS;
                    }
                    expression.letters.clear();
                }
            }
            else
            {
                Logger::log(LL_Error, "Converter::booleanExpressionsToCircuit - Invalid expression design");
                return INVALID_INPUT_EXPRESSIONS;
            }
        }
    }

    pNewCircuit = circuit.createGateCollection();
    return ConverterResult::SUCCESS;
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
    QScriptEngine engine;
    QScriptContext* pContext = engine.pushContext();//I think this gets deleted by engine destructor

    std::vector<QString> inputVariables;
    for(uint i = 1; i <= numInputs; i++)
    {
        inputVariables.push_back("input" + QString::number(i));
    }

    std::vector<QString> outputVariables;
    for(uint i = 1; i <= numOutputs; i++)
    {
        outputVariables.push_back("output" + QString::number(i));
        pContext->activationObject().setProperty("output" + QString::number(i), false);
    }

    std::vector<bool> genInputValues;

    truthTable.size = pow(2, numInputs);
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        //Generate input values
        genInputValues = truthTable.genInputs(iTableRun, numInputs);
        truthTable.inValues.push_back(genInputValues);

        //Set input values for script
        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            pContext->activationObject().setProperty(inputVariables[iInput], (bool)genInputValues[iInput]);
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

    truthTable.size = pow(2, numInputs);
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        //Generate input values
        std::vector<bool> inputValues = truthTable.genInputs(iTableRun, numInputs);
        truthTable.inValues.push_back(inputValues);

        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            inputGates[iInput]->setPowerState(inputValues[iInput]);
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
