#ifndef DLG_TRUTHTABLECREATE_H
#define DLG_TRUTHTABLECREATE_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class DLG_TruthTableCreate;
}

class DLG_TruthTableCreate : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TruthTableCreate(QWidget *parent = nullptr);
    ~DLG_TruthTableCreate();

private:
    Ui::DLG_TruthTableCreate *ui;
};

class BinaryLabel : public QLabel
{
    Q_OBJECT

public:
    BinaryLabel(QWidget* parent, const bool& value = false);

    bool value();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DLG_TRUTHTABLECREATE_H
