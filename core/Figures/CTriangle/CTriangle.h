#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "Figures/CFigure/CFigure.h"

class CTriangle : public CFigure {

    int centerX;
    int centerY;
    int size;

    public:

    CTriangle(int x,int y,int s);
    
    virtual void draw(QPainter& painter) override;

};

#endif//CTRIANGLE_H