#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "Figures/CFigure/CFigure.h"
#include "CProperties/CProperties.h"

class CHexagon : public CFigure {

    int centerX;
    int centerY;
    int size;

    QColor fillColor;
    QColor outColor;

    double absCoef;
    double ordCoef;

    public:

    CHexagon();
    virtual void draw(QPainter& painter) override;
    void setProperties(CProperties& prop);

};

#endif//CHEXAGON_H