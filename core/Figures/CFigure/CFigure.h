#ifndef CFIGURE_H
#define CFIGURE_H

#include <QPainter>
#include "CProperties/CProperties.h"

class CFigure {

public:

    virtual void draw(QPainter& painter)=0;
    virtual ~CFigure() = default;

};

#endif//CFIGURE_H