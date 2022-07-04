#include "dlg_truthtablecreate.h"
#include "ui_dlg_truthtablecreate.h"

DLG_TruthTableCreate::DLG_TruthTableCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_TruthTableCreate)
{
    ui->setupUi(this);
}

DLG_TruthTableCreate::~DLG_TruthTableCreate()
{
    delete ui;
}


////////////////////////////////////////////////////////
/// \brief BinaryLabel::BinaryLabel
/// \param parent
///
BinaryLabel::BinaryLabel(QWidget* parent, const bool& value) : QLabel(parent)
{
    setText(value ? "1" : "0");
}

bool BinaryLabel::value()
{
    return text() == "1";
}

void BinaryLabel::mousePressEvent(QMouseEvent* event)
{
    setText(value() ? "0" : "1");
    QLabel::mousePressEvent(event);
}
