#include "truthtable.h"

ExpressionCalculatorResult BooleanExpressionCalculator::truthTableToBooleanExpressions(TruthTable& truthTable, std::vector<BooleanExpression>& expressions)
{
    if(truthTable.inValues.size() == 0 || truthTable.outValues.size() == 0)
    {
        return INVALID_TABLE;
    }
}
