#include "dlg_load.h"
#include "ui_dlg_load.h"
#include "dlg_home.h"

DLG_Load::DLG_Load(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_Load)
{
    ui->setupUi(this);

    //Inital ui values
    ui->progressBar->setValue(0);
    ui->lbl_progressStep->setText("Initalizing");
}

DLG_Load::~DLG_Load()
{
    delete ui;
}

bool DLG_Load::event(QEvent *event)
{
    int returnValue = QWidget::event(event);

    if (event->type() == QEvent::Paint && !m_bStartedLoad)
    {
        Load();
        return true;
    }

    return returnValue;
}

void DLG_Load::Load()
{
    m_bStartedLoad = true;

    repaint();

    ui->lbl_progressStep->setText("Constructing window");
    ui->progressBar->setValue(10);

    repaint();

    DLG_Home* home = new DLG_Home(ui->progressBar, ui->lbl_progressStep);
    home->show();

    //Forget home
    home = nullptr;

    close();
}
