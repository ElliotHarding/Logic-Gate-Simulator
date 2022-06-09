#include "dlg_textedit.h"
#include "ui_dlg_textedit.h"

#include <qlayout.h>

DLG_TextEdit::DLG_TextEdit() :
    QDialog(),
    ui(new Ui::DLG_TextEdit)
{
    ui->setupUi(this);
    this->setLayout(new QHBoxLayout());

    m_fontBold.setBold(true);
    m_fontUnderlined.setUnderline(true);

    //Create & add font size slider
    ui->widget = new FontSlider(1, 100, 3, this);
}

void DLG_TextEdit::Setup(QString initalString, QFont initalFont)
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

void DLG_TextEdit::SetFontSize(float size)
{
    m_font.setPointSize(int(size));
    ui->lbl_fontSize->setText(std::to_string(int(size)).c_str());
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
