#ifndef CScene_H
#define CScene_H

#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include "Figures/CFigure/CFigure.h"
#include "CCanvas/CCanvas.h"
#include <vector>

class CScene : public QObject {
    Q_OBJECT

    CCanvas* canvas;
    std::vector<CFigure*> figures;

public:

    explicit CScene(QObject* parent=nullptr);
    void setWidget(QWidget* widget);
    void addFigure(CFigure* figure);
    void render(QPainter& painter);

};

#endif // CScene_H