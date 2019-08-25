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
    explicit DLG_TextEdit();
    ~DLG_TextEdit();

    //Called by slider
    void SetFontSize(float size);    

protected:
    virtual void UpdateOverrideObject() = 0;

    QString m_savedString;
    QFont m_font;

    void Setup(QString initalString = "", QFont initalFont = QFont("Helvetica", 20));

private slots:
    void on_btn_Ok_clicked();
    void on_btn_Cancel_clicked();
    void on_btn_clear_clicked();
    void on_btn_Underline_clicked();
    void on_btn_Bold_clicked();

private:
    //Ui elements
    Ui::DLG_TextEdit *ui;

    QFont m_fontDisabled = QFont("Helvetica", 7);
    QFont m_fontUnderlined = QFont("Helvetica", 7);
    QFont m_fontBold = QFont("Helvetica", 7);
};

#endif // DLG_TEXTEDIT_H
