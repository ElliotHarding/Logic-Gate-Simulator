#ifndef GATEFIELDSCONTAINER_H
#define GATEFIELDSCONTAINER_H

#include "gatefield.h"
#include <QMutex>

class DLG_Home;
class GateFieldsContainer
{
public:
    GateFieldsContainer(DLG_Home* pParent);

    void Add(GateField* gf);
    void DeleteGate(Gate *g);

private:
    GateField* m_currentGateField;
    std::vector<GateField*> m_allGateFields;
    QMutex m_lockGateFields;
    DLG_Home* m_pParent;
};

#endif // GATEFIELDSCONTAINER_H
