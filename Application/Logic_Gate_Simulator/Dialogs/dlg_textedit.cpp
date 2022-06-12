#include "dlg_textedit.h"
#include "ui_dlg_textedit.h"

DLG_TextEdit::DLG_TextEdit() :
    QDialog(),
    ui(new Ui::DLG_TextEdit)
{
    ui->setupUi(this);
    this->setLayout(new QHBoxLayout());

    m_fontBold.setBold(true);
    m_fontUnderlined.setUnderline(true);

    //Create & add font size slider
    const QRect widgetGeo = ui->widget->geometry();
    delete ui->widget;
    ui->widget = new FontSlider(this, widgetGeo, 1, 100, 3);
}

void DLG_TextEdit::Setup(const QString& initalString, const QFont& initalFont)
{
    m_savedString = initalString;
    m_font = initalFont;

    //Inital setup
    ui->textEdit->setText(initalString);
    ui->textEdit->setFont(m_font);
}

DLG_TextEdit::~DLG_TextEdit()
{
    delete ui;
}

void DLG_TextEdit::SetFontSize(const int& size)
{
    m_font.setPointSize(size);
    ui->lbl_fontSize->setText(QString::number(size));
    ui->textEdit->setFont(m_font);
}

void DLG_TextEdit::on_btn_Ok_clicked()
{
    m_savedString = ui->textEdit->toPlainText();
    UpdateOverrideObject();
    hide();
}

void DLG_TextEdit::on_btn_Cancel_clicked()
{
    hide();
}

void DLG_TextEdit::on_btn_clear_clicked()
{
    ui->textEdit->clear();
}

void DLG_TextEdit::on_btn_Underline_clicked()
{
    m_font.setUnderline(!m_font.underline());
    ui->textEdit->setFont(m_font);
    ui->btn_Underline->setFont(m_font.underline() ? m_fontUnderlined : m_fontDisabled);
}

void DLG_TextEdit::on_btn_Bold_clicked()
{
    m_font.setBold(!m_font.bold());
    ui->textEdit->setFont(m_font);
    ui->btn_Bold->setFont(m_font.bold() ? m_fontBold : m_fontDisabled);
}
