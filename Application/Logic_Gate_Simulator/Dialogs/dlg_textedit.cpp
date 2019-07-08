#include "dlg_textedit.h"
#include "ui_dlg_textedit.h"

DLG_TextEdit::DLG_TextEdit(QString initalString, QFont initalFont, bool isUnderlined) :
    QDialog(),
    m_savedString(initalString),
    m_font(initalFont),
    m_bIsUnderlined(isUnderlined),
    ui(new Ui::DLG_TextEdit)
{
    ui->setupUi(this);   
    ui->textEdit->setText(initalString);
    dlg_fontSizeSlider = new FontSlider(5,20, ui->layout_fontSizeSlider->geometry(), this);

    ui->btn_Underline->setDown(m_bIsUnderlined);
}

DLG_TextEdit::~DLG_TextEdit()
{
    delete ui;
}

void DLG_TextEdit::SetFontSize(float size)
{
    m_font.setWeight(int(size));
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
    m_bIsUnderlined = !m_bIsUnderlined;
    ui->btn_Underline->setDown(m_bIsUnderlined);
}
