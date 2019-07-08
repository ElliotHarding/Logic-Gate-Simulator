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
    explicit DLG_TextEdit(QString initalString = "", QFont initalFont = QFont("Helvetica", 5), bool isUnderlined = false);
    ~DLG_TextEdit();

    //Called by slider
    void SetFontSize(float size);

protected:
    virtual void UpdateOverrideObject() = 0;

    QString m_savedString;
    QFont m_font;
    bool m_bIsUnderlined;

private slots:
    void on_btn_Ok_clicked();
    void on_btn_Cancel_clicked();
    void on_btn_clear_clicked();

private:
    //Ui elements
    Ui::DLG_TextEdit *ui;
    FontSlider* dlg_fontSizeSlider;
};

#endif // DLG_TEXTEDIT_H
