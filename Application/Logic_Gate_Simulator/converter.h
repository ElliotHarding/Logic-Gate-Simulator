#ifndef CONVERTER_H
#define CONVERTER_H

#include "gatecollection.h"
#include "booleanexpression.h"

enum ConverterResult
{
    SUCCESS,
    INVALID_TABLE,
    INVALID_INPUT_EXPRESSIONS,
    INVALID_SCRIPT,
    INVALID_CIRCUIT
};

enum ConversionAlgorithm
{
    QuineMcCluskey,
    Random,
    NoOptimization,
    NoAlgorithm
    //When editing, also update dlg_conversionconfig.cpp
};

struct CircuitOptions //Circuit generation options
{
    CircuitOptions(const bool& useInverseGates, const bool& nandOnly, const bool& largeInputGates, const int& maxSeconds, const ConversionAlgorithm& conversionAlgorithm = NoAlgorithm);
    CircuitOptions();

    bool m_bUseInverseGates; //Use gates like NAND or NOR
    bool m_bNandOnly; //Only NAND gates
    bool m_bLargeInputGates; //Use gates with more than 2 inputs (tri-and)
    ConversionAlgorithm m_algorithm;
    int m_maxSeconds;
};

class Converter
{
public:
    static ConverterResult truthTableToBooleanExpressions(TruthTable& truthTable, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
    static ConverterResult expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable);
    static ConverterResult simplifyBooleanExpressions(std::vector<BooleanExpression>& expressions, const ConversionAlgorithm& conversionOptions);
    static ConverterResult booleanExpressionsToCircuit(std::vector<BooleanExpression> expressions, const CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult booleanExpressionsToCircuit2(std::vector<BooleanExpression> expressions, const CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult truthTableToCircuit(TruthTable& truthTable, const CircuitOptions& circuitOptions, GateCollection*& pNewCircuit);
    static ConverterResult scriptToCircuit(const QString& script, const uint& numInputs, const uint& numOutputs, const CircuitOptions& circuitOptions, GateCollection*& pNewCircuit, int& failedLineNumber);
    static ConverterResult scriptToTruthTable(const QString& script, const uint& numInputs, const uint& numOutputs, TruthTable& truthTable, int& failedLineNumber);
    static ConverterResult scriptToBooleanExpressions(const QString& script, const uint& numInputs, const uint& numOutputs, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions, int& failedLineNumber);
    static ConverterResult circuitToTruthTable(std::vector<Gate*> gates, TruthTable& truthTable);
    static ConverterResult circuitToBooleanExpressions(std::vector<Gate*> gates, const ConversionAlgorithm& conversionOptions, std::vector<BooleanExpression>& expressions);
};

#endif // CONVERTER_H
