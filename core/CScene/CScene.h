#ifndef CScene_H
#define CScene_H

#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include "Figures/CFigure/CFigure.h"
#include "Figures/CBeziersCurve/CBeziersCurve.h"
#include "CCanvas/CCanvas.h"
#include <vector>
#include <string>

class CScene : public QObject {
    Q_OBJECT

    CCanvas* canvas;
    std::vector<CFigure*> figures;
    CBeziersCurve curve;

    double ordSegment;
    double absSegment;

public:

    explicit CScene(QObject* parent=nullptr);
    void setWidget(QWidget* widget);
    void drawCoorSystem(QPainter& painter, int width, int height, int marks);
    double getOrdSegment();
    double getAbsSegment();
    void addFigure(CFigure* figure);
    void clearFigures();
    void render(QPainter& painter);
    CBeziersCurve* getCurve();
    
    void saveFigures(const std::string& filename);
    void loadFigures(const std::string& filename);

};

#endif // CScene_H