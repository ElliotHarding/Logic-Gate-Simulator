#include "truthtable.h"
#include "circuit.h"
#include "allgates.h"

#include <cmath>

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;
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

ExpressionCalculatorResult BooleanExpressionCalculator::truthTableToBooleanExpressions(TruthTable& truthTable, std::vector<BooleanExpression>& expressions)
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

bool expressionToResult(const std::vector<bool>& inValues, const BooleanExpression& expression)
{
    for(uint i = 0; i < inValues.size(); i++)
    {
        const char letter = Settings::IntStartAlphabet + i;
        for(uint j = 0; j < expression.letters.size(); j++)
        {
            if(expression.letters[j] == letter)
            {
                if(expression.inverted[j] == inValues[i])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

ExpressionCalculatorResult BooleanExpressionCalculator::expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable)
{
    if(truthTable.inValues.size() != 0 || truthTable.outValues.size() != 0 || truthTable.size != 0)
    {
        return INVALID_INPUT_EXPRESSIONS;
    }

    std::vector<char> inputs;
    std::vector<char> outputs;
    for(BooleanExpression expression : expressions)
    {
        for(uint i = 0; i < expression.letters.size(); i++)
        {
            const char letter = expression.letters[i];
            if(uint(letter) >= Settings::IntStartAlphabet && uint(letter) <= Settings::IntEndAlphabet && !inVector(inputs, letter))
            {
                inputs.push_back(letter);
            }
        }

        outputs.push_back(expression.resultLetter);
    }

    truthTable.size = pow(2, inputs.size());
    for(uint i = 0; i < truthTable.size; i++)
    {
        truthTable.inValues.push_back(truthTable.genInputs(i, inputs.size()));
    }

    for(uint i = 0; i < truthTable.inValues.size(); i++)
    {
        truthTable.outValues.push_back(std::vector<bool>());
        for(uint iOutput = 0; iOutput < outputs.size(); iOutput++)
        {
            truthTable.outValues[i].push_back(expressionToResult(truthTable.inValues[i], expressions[iOutput]));
        }
    }

    return SUCCESS;
}

bool isLetter(const char& letter)
{
    if(letter >= (int)Settings::IntStartAlphabet && letter <= (int)Settings::IntEndAlphabet)
    {
        return true;
    }
    return false;
}

bool isLetterOrInt(const char& letter)
{
    if((letter >= (int)Settings::IntStartAlphabet && letter <= (int)Settings::IntEndAlphabet) || (letter >= 48 && letter <= 57))
    {
        return true;
    }
    return false;
}

ExpressionCalculatorResult BooleanExpressionCalculator::booleanExpressionsToCircuit(std::vector<BooleanExpression>& expressions, GateCollection*& pNewCircuit)
{
    //Todo ~ simplification - Either properly or by converting to truth table putting it through truthTableToBooleanExpressions


    //Get list of individual input letters to count
    QList<char> letters;
    for(BooleanExpression& expression : expressions)
    {
        for(char& letter : expression.letters)
        {
            if(isLetter(letter))
            {
                if(!letters.contains(letter))
                {
                    letters.push_back(letter);
                }
            }
        }
    }

    const uint numOutputs = expressions.size();
    const uint numInputs = letters.size();

    Circuit circuit(numInputs, numOutputs);
    std::map<char, Gate*> circuitGates;
    std::map<char, Gate*> invertLetterGates;
    int sumGateCounter = 0;
    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        bool changed = true;
        while(changed)
        {
            changed = false;

            //Look for AND jobs
            for(uint iLetter = 0; iLetter < expressions[iExpression].letters.size()-1; iLetter++)
            {
                if(isLetterOrInt(expressions[iExpression].letters[iLetter]) && isLetterOrInt(expressions[iExpression].letters[iLetter+1]))
                {
                    Gate* input1Gate;
                    if(expressions[iExpression].inverted[iLetter])
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(expressions[iExpression].letters[iLetter]) != invertLetterGates.end())
                        {
                            input1Gate = invertLetterGates[expressions[iExpression].letters[iLetter]];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input1Gate = new GateNot();
                            circuit.inputs[expressions[iExpression].letters[iLetter] - Settings::IntStartAlphabet]->getOutputNodes()[0]->LinkNode(input1Gate->getInputNodes()[0]);
                            invertLetterGates[expressions[iExpression].letters[iLetter]] = input1Gate;
                            circuit.mainGates.push_back(input1Gate);
                        }
                    }
                    else if(isLetter(expressions[iExpression].letters[iLetter]))
                    {
                        input1Gate = circuit.inputs[expressions[iExpression].letters[iLetter] - Settings::IntStartAlphabet];
                    }
                    else
                    {
                        input1Gate = circuitGates[expressions[iExpression].letters[iLetter]];
                    }

                    Gate* input2Gate;
                    if(expressions[iExpression].inverted[iLetter+1])
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(expressions[iExpression].letters[iLetter+1]) != invertLetterGates.end())
                        {
                            input2Gate = invertLetterGates[expressions[iExpression].letters[iLetter+1]];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input2Gate = new GateNot();
                            circuit.inputs[expressions[iExpression].letters[iLetter+1] - Settings::IntStartAlphabet]->getOutputNodes()[0]->LinkNode(input2Gate->getInputNodes()[0]);
                            invertLetterGates[expressions[iExpression].letters[iLetter+1]] = input2Gate;
                            circuit.mainGates.push_back(input2Gate);
                        }
                    }
                    else if(isLetter(expressions[iExpression].letters[iLetter+1]))
                    {
                        input2Gate = circuit.inputs[expressions[iExpression].letters[iLetter+1] - Settings::IntStartAlphabet];
                    }
                    else
                    {
                        input2Gate = circuitGates[expressions[iExpression].letters[iLetter+1]];
                    }

                    Gate* andGate = new GateAnd();
                    andGate->getInputNodes()[0]->LinkNode(input1Gate->getOutputNodes()[0]);
                    input1Gate->getOutputNodes()[0]->LinkNode(andGate->getInputNodes()[0]);
                    andGate->getInputNodes()[1]->LinkNode(input2Gate->getOutputNodes()[0]);
                    input2Gate->getOutputNodes()[0]->LinkNode(andGate->getInputNodes()[1]);
                    circuit.mainGates.push_back(andGate);
                    circuitGates[48 + sumGateCounter] = andGate;

                    //Replace A.B with 1
                    expressions[iExpression].letters[iLetter] = 48 + sumGateCounter;
                    expressions[iExpression].letters.erase(expressions[iExpression].letters.begin() + iLetter + 1);
                    expressions[iExpression].inverted[iLetter] = false;
                    expressions[iExpression].inverted.erase(expressions[iExpression].inverted.begin() + iLetter + 1);

                    sumGateCounter++;
                    changed = true;

                    if(expressions[iExpression].letters.size() == 1)
                    {
                        circuit.outputs[iExpression]->getInputNodes()[0]->LinkNode(andGate->getOutputNodes()[0]);
                        andGate->getOutputNodes()[0]->LinkNode(circuit.outputs[iExpression]->getInputNodes()[0]);
                    }

                    break;
                }
            }

            if(changed)
            {
                continue;
            }

            //Look for OR jobs
            for(uint iLetter = 0; iLetter < expressions[iExpression].letters.size()-1; iLetter++)
            {
                if(expressions[iExpression].letters[iLetter] == '+' && iLetter > 0 && iLetter < expressions[iExpression].letters.size()-1)
                {
                    //Todo ~ notted sums

                    Gate* input1Gate;
                    if(expressions[iExpression].inverted[iLetter-1])
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(expressions[iExpression].letters[iLetter-1]) != invertLetterGates.end())
                        {
                            input1Gate = invertLetterGates[expressions[iExpression].letters[iLetter-1]];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input1Gate = new GateNot();
                            circuit.inputs[expressions[iExpression].letters[iLetter-1] - Settings::IntStartAlphabet]->getOutputNodes()[0]->LinkNode(input1Gate->getInputNodes()[0]);
                            invertLetterGates[expressions[iExpression].letters[iLetter-1]] = input1Gate;
                            circuit.mainGates.push_back(input1Gate);
                        }
                    }
                    else if(isLetter(expressions[iExpression].letters[iLetter-1]))
                    {
                        input1Gate = circuit.inputs[expressions[iExpression].letters[iLetter-1] - Settings::IntStartAlphabet];
                    }
                    else
                    {
                        input1Gate = circuitGates[expressions[iExpression].letters[iLetter-1]];
                    }

                    Gate* input2Gate;
                    if(expressions[iExpression].inverted[iLetter+1])
                    {
                        //Check if already have a notted gate of current letter
                        if(invertLetterGates.find(expressions[iExpression].letters[iLetter+1]) != invertLetterGates.end())
                        {
                            input2Gate = invertLetterGates[expressions[iExpression].letters[iLetter+1]];
                        }

                        //Todo ~ check if sum gate is notted.

                        //Otherwise create new notted gate of current letter
                        else
                        {
                            input2Gate = new GateNot();
                            circuit.inputs[expressions[iExpression].letters[iLetter+1] - Settings::IntStartAlphabet]->getOutputNodes()[0]->LinkNode(input2Gate->getInputNodes()[0]);
                            invertLetterGates[expressions[iExpression].letters[iLetter+1]] = input2Gate;
                            circuit.mainGates.push_back(input2Gate);
                        }
                    }
                    else if(isLetter(expressions[iExpression].letters[iLetter+1]))
                    {
                        input2Gate = circuit.inputs[expressions[iExpression].letters[iLetter+1] - Settings::IntStartAlphabet];
                    }
                    else
                    {
                        input2Gate = circuitGates[expressions[iExpression].letters[iLetter+1]];
                    }

                    Gate* orGate = new GateOr();
                    orGate->getInputNodes()[0]->LinkNode(input1Gate->getOutputNodes()[0]);
                    input1Gate->getOutputNodes()[0]->LinkNode(orGate->getInputNodes()[0]);
                    orGate->getInputNodes()[1]->LinkNode(input2Gate->getOutputNodes()[0]);
                    input2Gate->getOutputNodes()[0]->LinkNode(orGate->getInputNodes()[1]);
                    circuit.mainGates.push_back(orGate);
                    circuitGates[48 + sumGateCounter] = orGate;

                    //Replace A+B with 1
                    expressions[iExpression].letters[iLetter-1] = 48 + sumGateCounter;
                    expressions[iExpression].letters.erase(expressions[iExpression].letters.begin() + iLetter);
                    expressions[iExpression].letters.erase(expressions[iExpression].letters.begin() + iLetter);
                    expressions[iExpression].inverted[iLetter-1] = false;
                    expressions[iExpression].inverted.erase(expressions[iExpression].inverted.begin() + iLetter);
                    expressions[iExpression].inverted.erase(expressions[iExpression].inverted.begin() + iLetter);

                    sumGateCounter++;
                    changed = true;

                    if(expressions[iExpression].letters.size() == 1)
                    {
                        circuit.outputs[iExpression]->getInputNodes()[0]->LinkNode(orGate->getOutputNodes()[0]);
                        orGate->getOutputNodes()[0]->LinkNode(circuit.outputs[iExpression]->getInputNodes()[0]);
                        changed = false;//Mark finished
                    }

                    break;
                }
            }
        }
    }

    pNewCircuit = circuit.createGateCollection();
    return ExpressionCalculatorResult::SUCCESS;
}
