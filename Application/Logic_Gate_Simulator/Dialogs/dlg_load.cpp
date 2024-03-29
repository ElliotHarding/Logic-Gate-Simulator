#include "dlg_load.h"
#include "ui_dlg_load.h"
#include "dlg_home.h"
#include "logger.h"
#include "customsettings.h"

DLG_Load::DLG_Load(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DLG_Load)
{
    ui->setupUi(this);

    //Inital ui values
    ui->progressBar->setValue(0);
    ui->lbl_progressStep->setText("Initalizing");

    connect(this, SIGNAL(startLoad()), this, SLOT(onStartLoad()), Qt::ConnectionType::QueuedConnection);
}

DLG_Load::~DLG_Load()
{
    delete ui;
}

//Todo : find a work around.
// - starting load on a paint event because then the widget is definatly displayed
bool DLG_Load::event(QEvent *event)
{
    bool returnValue = QWidget::event(event);

    if (event->type() == QEvent::Paint && !m_bStartedLoad)
    {
        m_bStartedLoad = true;
        emit startLoad();
    }

    return returnValue;
}

void DLG_Load::onStartLoad()
{
    Logger::init();
    CustomSettings::init();

    ui->lbl_progressStep->setText("Constructing window");
    ui->progressBar->setValue(10);

    DLG_Home* home = new DLG_Home(ui->progressBar, ui->lbl_progressStep);
    home->show();

    //Forget home
    home = nullptr;

    close();
}
