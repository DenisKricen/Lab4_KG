#ifndef CPROPERTIES_H
#define CPROPERTIES_H

#include <QColor>
#include <QString>

namespace Ui {
    class CMainWindow;
}

class CProperties {
    public:
    QColor outColor;
    QColor fillColor;
    double ordinate;
    double abscise;
    double circumradius;

    double absCoef;
    double ordCoef;

    CProperties();
    void updateProperties(Ui::CMainWindow* ui);
    void setCoefs(double absCoef, double ordCoef);

};

#endif//CPROPERTIES_H