#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>
#include <QString>

class GateCollection;

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size = 0;

    std::vector<bool> genInputs(const unsigned int& iTableRun, const unsigned int& numInputs)
    {
        std::vector<bool> inputs;
        int mask = 1;
        for(unsigned int i = 0; i < numInputs; i++)
        {
            if((mask&iTableRun) >= 1)
                inputs.push_back(true);
            else
                inputs.push_back(false);
            mask<<=1;
        }
        return inputs;
    }
};

struct BooleanExpression
{
    std::vector<char> letters;
    std::vector<bool> inverted;
    char resultLetter;

    void addTerm(const char& letter, const bool& bInverted = false)
    {
        letters.push_back(letter);
        inverted.push_back(bInverted);
    }

    QString lettersAsString()
    {
        QString result = "";

        for(uint i = 0; i < letters.size(); i++)
        {
            result += letters[i];
        }

        return result;
    }
};

enum ExpressionCalculatorResult
{
    SUCCESS,
    INVALID_TABLE,
    INVALID_INPUT_EXPRESSIONS
};

enum ConversionAlgorithm
{
    QuineMcCluskey,
    NoOptimization,
    NoAlgorithm
};

struct CircuitOptions //Circuit generation options
{
    CircuitOptions(const bool& useAdvancedNotGates, const bool& nandOnly, const bool& tripleGates, const ConversionAlgorithm& conversionAlgorithm = NoAlgorithm) :
        m_bUseAdvancedNotGates(useAdvancedNotGates),
        m_bNandOnly(nandOnly),
        m_bTripleGates(tripleGates),
        m_algorithm(conversionAlgorithm)
    {};

    bool m_bUseAdvancedNotGates; //Use gates like NAND or NOR
    bool m_bNandOnly; //Only NAND gates
    bool m_bTripleGates; //Triple input gates
    ConversionAlgorithm m_algorithm;
};

class BooleanExpressionCalculator
{
public:
    static ExpressionCalculatorResult truthTableToBooleanExpressions(TruthTable& truthTable, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
    static ExpressionCalculatorResult expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable);
    static ExpressionCalculatorResult booleanExpressionsToCircuit(std::vector<BooleanExpression> expressions, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ExpressionCalculatorResult truthTableToCircuit(TruthTable& truthTable, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ExpressionCalculatorResult scriptToCircuit(const QString& script, const uint& numInputs, const uint& numOutputs, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ExpressionCalculatorResult scriptToTruthTable(const QString& script, const uint& numInputs, const uint& numOutputs, TruthTable& truthTable);
    static ExpressionCalculatorResult scriptToBooleanExpressions(const QString& script, const uint& numInputs, const uint& numOutputs, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
};

#endif // TRUTHTABLE_H
