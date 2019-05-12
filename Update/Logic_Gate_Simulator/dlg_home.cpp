#include "dlg_home.h"
#include "ui_dlg_home.h"
#include <QLayout>
#include <QFileDialog>
#include <QInputDialog>
#include "gatereader.h"

DLG_Home::DLG_Home(QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::DLG_Home),
    m_ZoomFactor(0.5),

    m_gateInfo(new DLG_GateInfo(this)),

    m_pWidgetAllGates(new Widget_AllGates(this)),
    m_pWidgetCustomGates(new Widget_CustomGates(this)),
    m_pWidgetAdvancedGates(new Widget_Advanced(this)),
    m_pWidgetStandardGates(new Widget_Standard(this)),
    m_pWidgetInputGates(new Widget_InputGates(this))
{
    ui->setupUi(this);
    setMouseTracking(true);
    ui->PlayField->clear();

    this->layout()->addWidget(m_pWidgetAllGates);
    this->layout()->addWidget(m_pWidgetCustomGates);
    this->layout()->addWidget(m_pWidgetAdvancedGates);
    this->layout()->addWidget(m_pWidgetStandardGates);
    this->layout()->addWidget(m_pWidgetInputGates);

    this->layout()->addWidget(m_gateInfo);
    m_gateInfo->move(c_GateInfoWidgetPos);
    m_gateInfo->raise();

    m_pWidgetCustomGates->move(c_GateWidgetPosHidden);
    m_pWidgetAdvancedGates->move(c_GateWidgetPosHidden);
    m_pWidgetStandardGates->move(c_GateWidgetPosHidden);
    m_pWidgetInputGates->move(c_GateWidgetPosHidden);

    m_pWidgetAllGates->move(c_GateWidgetPosShowing);
    m_pWidgetAllGates->raise();

    m_pCurrentShownGateWidget = m_pWidgetAllGates;

    addGateField("New 1");

    //Add zoom slider to dialog
    m_zoomSlider = new SimpleSlider(c_minZoom, c_maxZoom, c_zoomSliderPos, c_zoomSliderWidth, this);
    this->layout()->addWidget(m_zoomSlider);
}

DLG_Home::~DLG_Home()
{
    //m_updateThread->stopRunning();
    //m_updateThread->exit();
    //delete m_updateThread;

    //m_currentGateField = nullptr;

    //Delete gatefields
    for (GateField* gf : m_allGateFields)
    {
        delete gf;
    }

    delete ui;
}

void DLG_Home::SetZoomFactor(float zoomFactor)
{
    m_ZoomFactor = zoomFactor;
    m_currentGateField->setZoomLevel(m_ZoomFactor);
}

void DLG_Home::AddGate(Gate *g)
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(g);
        on_btn_Drag_clicked();
    }
}

void DLG_Home::GateSelected(Gate *g)
{
    m_gateInfo->setGate(g);
}

void DLG_Home::DeleteGate(Gate *g)
{
    for(GateField* gField : m_allGateFields)
    {
        if(gField == g->ParentField)
        {
            gField->DeleteGate(g);
        }
    }
}

void DLG_Home::addGateField(QString name)
{
    m_currentGateField = new GateField(m_ZoomFactor, name.toStdString(), this);
    m_allGateFields.push_back(m_currentGateField);
    ui->PlayField->addTab(m_currentGateField,tr(name.toUtf8()));
}


// -- BUTTON HANDLERS FOR CLICK MODES --

void DLG_Home::on_btn_Drag_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DRAG);
    }

    QApplication::setOverrideCursor(Qt::CursorShape::SizeAllCursor);
}
void DLG_Home::on_btn_Delete_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DELETE_GATE);
    }

    QApplication::setOverrideCursor(Qt::CursorShape::CrossCursor);
}
void DLG_Home::on_btn_link_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_LINK_NODES);
    }

    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
}
void DLG_Home::on_btn_DeleteLink_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DELETE_LINK_NODES);
    }

    QApplication::setOverrideCursor(Qt::CursorShape::DragLinkCursor);
}
void DLG_Home::on_btn_click_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_DEFAULT);
    }

    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}
void DLG_Home::SelectionToolClicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_SELECTION);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}
void DLG_Home::on_btn_Pan_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->setCurrentClickMode(CLICK_PAN);
    }
    QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}




// -- HANDLERS FOR GATES MENU BUTTONS --
void DLG_Home::on_menu_btn_allGates_clicked()
{
    SwitchWidgets(m_pWidgetAllGates);
}
void DLG_Home::on_menu_btn_customGates_clicked()
{
    SwitchWidgets(m_pWidgetCustomGates);
    m_pWidgetCustomGates->UpdateList();
}
void DLG_Home::on_menu_btn_InputGates_clicked()
{
    SwitchWidgets(m_pWidgetInputGates);
}
void DLG_Home::on_menu_btn_standardGates_clicked()
{
    SwitchWidgets(m_pWidgetStandardGates);
}
void DLG_Home::on_menu_btn_advancedGates_clicked()
{
    SwitchWidgets(m_pWidgetAdvancedGates);
}
void DLG_Home::SwitchWidgets(QWidget* w)
{
    if(w != m_pCurrentShownGateWidget)
    {
        w->raise();

        for (int moved = 0; moved < w->geometry().width(); moved++)
        {
            if(m_pCurrentShownGateWidget)
                MoveWidget(m_pCurrentShownGateWidget, -1);

            MoveWidget(w, 1);

            QThread::msleep(1);
        }

        m_pCurrentShownGateWidget = w;
    }
}
void DLG_Home::MoveWidget(QWidget *w, int xDir)
{
    QRect geo = w->geometry();
    w->move(geo.left() + xDir, geo.top());
    w->repaint();
}

// -- OTHER BUTTON HANDLERS --

void DLG_Home::on_btn_zoomIn_clicked()
{
    if(m_ZoomFactor < c_maxZoom)
        m_currentGateField->setZoomLevel(m_ZoomFactor *= 2);
}

void DLG_Home::on_btn_zoomOut_clicked()
{
    if(m_ZoomFactor > c_minZoom)
        m_currentGateField->setZoomLevel(m_ZoomFactor /= 2);
}

void DLG_Home::on_btn_newPage_clicked()
{
    //Request page name
    bool ok;
    QString newPageName = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Page name: "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if(ok)
    {
        addGateField(newPageName);
    }
}

void DLG_Home::on_btn_Save_clicked()
{
    bool saveFailed = false;

    //Loop through all open gate fields and save
    for (GateField* gf : m_allGateFields)
    {
        saveFailed = gf->SaveData();
        if(!saveFailed)
            break;
    }

    //todo
    if(!saveFailed)
    {

    }
}

void DLG_Home::on_btn_load_clicked()
{
    //Promt user for gate colleciton file
    QStringList fileNames = QFileDialog::getOpenFileNames(this);

    //Loop vars
    GateReader reader;
    std::ifstream saveFile;
    for (QString file : fileNames)
    {
        //Open file
        saveFile = std::ifstream(file.toUtf8());

        if(saveFile.is_open())
        {
            //Load gates
            m_currentGateField = new GateField(m_ZoomFactor, file.toStdString(), this);

            //For each loaded gate, add to loadedGateField
            if (reader.ReadGateField(saveFile, m_currentGateField))
            {
                //Add to m_allGateFields
                m_allGateFields.push_back(m_currentGateField);

                //Add to ui
                ui->PlayField->addTab(m_currentGateField,tr(file.toUtf8()));

                continue;
            }
        }

        //todo failed

    }
}

void DLG_Home::on_PlayField_tabCloseRequested(int index)
{
    ui->PlayField->removeTab(index);
}

void DLG_Home::on_PlayField_currentChanged(int index)
{
    QWidget* currentWidget = ui->PlayField->currentWidget();
    if(dynamic_cast<GateField*>(currentWidget))
    {
        m_currentGateField = dynamic_cast<GateField*>(currentWidget);
    }
}


#ifdef zero
//          --------------------------------
//          LogicUpdateThread implementation
//          --------------------------------

LogicUpdateThread::LogicUpdateThread(std::vector<GateField*>* allGateFields) : QThread (),
    m_bStop(false),
    m_pAllGateFields(allGateFields)
{
}

LogicUpdateThread::~LogicUpdateThread()
{
    stopRunning();
    terminate();
}

//Calls the update function of all the gates in all of the gateFields
void LogicUpdateThread::run()
{
    while (!m_bStop)
    {
        for (GateField* gf : *m_pAllGateFields)
        {
            if((gf) && gf->Enabled)
                    gf->updateFunction();

        }
        QThread::msleep(1000);
    }


}

void LogicUpdateThread::stopRunning()
{
    m_bStop = true;
}

void DLG_Home::on_btn_test_clicked()
{
    if(m_currentGateField)
    {
        m_currentGateField->addGameObject(new GateTimer());
        on_btn_Drag_clicked();
    }
}
#endif
