#include "dlg_textedit.h"
#include "ui_dlg_textedit.h"

DLG_TextEdit::DLG_TextEdit(QWidget *parent, std::string initalString, QFont initalFont) :
    QDialog(parent),
    ui(new Ui::DLG_TextEdit),
    m_savedString(initalString.c_str()),
    m_font(initalFont)
{
    ui->setupUi(this);   

    dlg_fontSizeSlider = new FontSlider(5,20, ui->layout_fontSizeSlider->geometry(), this);
}

DLG_TextEdit::~DLG_TextEdit()
{
    delete ui;
}

std::string DLG_TextEdit::GetString()
{
    return m_savedString.toStdString();
}

QFont DLG_TextEdit::GetFont()
{
    return m_font;
}

void DLG_TextEdit::SetFontSize(float size)
{
    m_font.setWeight(int(size));
}

void DLG_TextEdit::on_btn_Ok_clicked()
{
    m_savedString = ui->textEdit->toPlainText();
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
