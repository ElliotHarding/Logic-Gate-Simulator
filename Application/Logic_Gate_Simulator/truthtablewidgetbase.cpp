#include "truthtablewidgetbase.h"

TruthTableWidgetBase::TruthTableWidgetBase(QWidget *parent) :
    QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
}
