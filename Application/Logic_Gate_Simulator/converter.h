#ifndef CONVERTER_H
#define CONVERTER_H

#include "truthtable.h"

class GateCollection;

enum ConverterResult
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
    CircuitOptions(const bool& useAdvancedNotGates, const bool& nandOnly, const bool& tripleGates, const ConversionAlgorithm& conversionAlgorithm = NoAlgorithm);;

    bool m_bUseAdvancedNotGates; //Use gates like NAND or NOR
    bool m_bNandOnly; //Only NAND gates
    bool m_bTripleGates; //Triple input gates
    ConversionAlgorithm m_algorithm;
};

class Converter
{
public:
    static ConverterResult truthTableToBooleanExpressions(TruthTable& truthTable, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
    static ConverterResult expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable);
    static ConverterResult booleanExpressionsToCircuit(std::vector<BooleanExpression> expressions, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult truthTableToCircuit(TruthTable& truthTable, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult scriptToCircuit(const QString& script, const uint& numInputs, const uint& numOutputs, CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult scriptToTruthTable(const QString& script, const uint& numInputs, const uint& numOutputs, TruthTable& truthTable);
    static ConverterResult scriptToBooleanExpressions(const QString& script, const uint& numInputs, const uint& numOutputs, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
};

#endif // CONVERTER_H
