#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"

DLG_TruthTable::DLG_TruthTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_TruthTable)
{
    ui->setupUi(this);
}

DLG_TruthTable::~DLG_TruthTable()
{
    delete ui;
}

void DLG_TruthTable::open(const TruthTable& truthTable)
{
    QDialog::open();
}

void DLG_TruthTable::open()
{
    QDialog::open();
}

////////////////////////////////////////////////////////
/// \brief BinaryLabel::BinaryLabel
/// \param parent
///
BinaryLabel::BinaryLabel(QWidget* parent, const bool& value, const bool& editDisabled) : QLabel(parent),
    m_bEditDisabled(editDisabled)
{
    setText(value ? "1" : "0");
}

bool BinaryLabel::value()
{
    return text() == "1";
}

void BinaryLabel::mousePressEvent(QMouseEvent* event)
{
    if(!m_bEditDisabled)
    {
        setText(value() ? "0" : "1");
    }
    QLabel::mousePressEvent(event);
}
