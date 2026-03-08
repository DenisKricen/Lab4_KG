#ifndef BEZIERS_CURVE_H
#define BEZIERS_CURVE_H
#include "Figures/CFigure/CFigure.h"

class CBeziersCurve : public CFigure {

    QVector<QPointF> curve;
    double pace;
    double tMin;
    double tMax;
    void (CBeziersCurve::* drawMethod)(QPainter&);

    void drawRect(QPainter& painter);

    public:

    CBeziersCurve();  

    void addPoint(const QPointF& point); 
    void editPoint(int index, const QPointF& point);
    void removePoint(int index);
    void movePoint(int from, int to);
    void clearPoints();
    const QVector<QPointF>& getPoints() const;

    void setPace(double p);
    void setTMin(double val);
    void setTMax(double val);

    void draw(QPainter& painter) override;
    void drawParam(QPainter& painter);
    void drawMatrix(QPainter& painter);
    void setDrawMethod(void (CBeziersCurve::* drawMethod)(QPainter&));

    std::string serialize() const override;
    static CBeziersCurve* deserialize(const std::string data);
    std::string getType() const override;
};

#endif//BEZIERS_CURVE_H

