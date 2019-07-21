#ifndef GATESELECTION_H
#define GATESELECTION_H

#include "gate.h"

class GateSelection
{
public:
    GateSelection(GateField* pParent, std::vector<Gate**>& gates);
    ~GateSelection();

    void Draw(QPainter* painter);

    bool UpdateDrag(int x, int y);

    void UpdateContaningArea();

    std::vector<Gate*> GetSelectedGates();

private:
    GateField* m_pParent;

    std::vector<Gate**> m_ppGates;

    //Number of pixels from border before gates are seen
    const int c_borderBoxMargin = 20;

    //Dragging
    DragMode m_dragMode = DragAll;
    void DisplaceGates(Vector2D displacement);

    //Buttons
    QRect m_saveButton;
    QRect m_deleteButton;
    QRect m_deleteAllButton;
    void DrawButtons(QPainter* painter);

    //Contaning area
    QRect m_contaningArea;

    //Call UpdateContaningArea() before calling any of these
    int Left();
    int Right();
    int Top();
    int Bottom();

    bool m_bDeleteGates = false;
};


#endif // GATESELECTION_H
