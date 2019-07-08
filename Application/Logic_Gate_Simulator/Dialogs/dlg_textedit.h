#ifndef DLG_TEXTEDIT_H
#define DLG_TEXTEDIT_H

#include <QDialog>
#include "simpleslider.h"

namespace Ui {
class DLG_TextEdit;
}

class DLG_TextEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TextEdit(QWidget *parent = nullptr, std::string initalString = "", QFont initalFont = QFont("Helvetica", 5));
    ~DLG_TextEdit();

    std::string GetString();
    QFont GetFont();

    //Called by slider
    void SetFontSize(float size);

private slots:

    void on_btn_Ok_clicked();
    void on_btn_Cancel_clicked();
    void on_btn_clear_clicked();

private:

    //Ui elements
    Ui::DLG_TextEdit *ui;
    FontSlider* dlg_fontSizeSlider;

    QString m_savedString;
    QFont m_font;
};

#endif // DLG_TEXTEDIT_H
