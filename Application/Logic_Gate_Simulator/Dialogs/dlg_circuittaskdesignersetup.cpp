#include "dlg_circuittaskdesignersetup.h"
#include "ui_dlg_circuittaskdesignersetup.h"
#include "dlg_message.h"
#include "dlg_circuittaskdesigner.h"

DLG_CircuitTaskDesignerSetup::DLG_CircuitTaskDesignerSetup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_CircuitTaskDesignerSetup)
{
    ui->setupUi(this);
}

DLG_CircuitTaskDesignerSetup::~DLG_CircuitTaskDesignerSetup()
{
    delete ui;
}

void DLG_CircuitTaskDesignerSetup::on_btn_ok_clicked()
{
    DLG_Message* messageDisplay = new DLG_Message(this);
    try
    {
        int inputs = ui->txt_inputs->toPlainText().toInt();
        int outputs = ui->txt_outputs->toPlainText().toInt();

        if(inputs == 0 || outputs == 0 || inputs > 4 || outputs > 4)
        {
            messageDisplay->ShowMessage("Values must be between 1 and 3");
            return;
        }

        DLG_CircuitTaskDesigner* dlgCircuitDesigner = new DLG_CircuitTaskDesigner(inputs, outputs);
        dlgCircuitDesigner->show();
        delete this;
    }
    catch (...)
    {
        messageDisplay->ShowMessage("Make sure values are correct");
    }
}
