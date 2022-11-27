#ifndef DLG_KARNAUGHMAP_H
#define DLG_KARNAUGHMAP_H

#include <QDialog>
#include <QLabel>
#include "karnaughmap.h"

namespace Ui {
class DLG_KarnaughMap;
}

namespace Settings
{
const QRect TableDisplayDimensions = QRect(50, 70, 300, 300);
}

class OutputLabel;
class DLG_Home;

class DLG_KarnaughMap : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_KarnaughMap(DLG_Home* pHome);
    ~DLG_KarnaughMap();

    void show(const KarnaughMap& kMap);

private:
    Ui::DLG_KarnaughMap *ui;

    void clearUI();

    KarnaughMap m_kMap;

    std::vector<QLabel*> m_tableLabels;
    std::vector<std::vector<OutputLabel*>> m_tableOutputLabels;

    DLG_Home* m_pHome;
};

#endif // DLG_KARNAUGHMAP_H
