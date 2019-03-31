#include "gateor.h"

GateOr::GateOr()
{

}

void GateOr::update(int clickX, int clickY)
{
    Gate::Update(clickX,clickY);

    if(output != nullptr)
    {
        *output = inputA | inputB;
    }
}
