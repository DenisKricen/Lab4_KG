#ifndef BEZIERS_CURVE_H
#define BEZIERS_CURVE_H
#include "Figures/CFigure/CFigure.h"
#include <QColor>
#include <QString>

class CBeziersCurve : public CFigure {

    QVector<QPointF> curve;
    double pace;
    double tMin;
    double tMax;
    QColor curveColor;
    QColor rectColor;
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
    double getPace() const;
    void setTMin(double val);
    double getTMin() const;
    void setTMax(double val);
    double getTMax() const;
    QColor getCurveColor() const;
    QColor getRectColor() const;
    void setCurveColor(const QColor& color);
    void setRectColor(const QColor& color);

    void draw(QPainter& painter) override;
    void drawParam(QPainter& painter);
    void drawMatrix(QPainter& painter);
    void setDrawMethod(void (CBeziersCurve::* drawMethod)(QPainter&));
    bool isMatrixMode() const;

    QString getMatrixInfo() const;

    std::string serialize() const override;
    static CBeziersCurve* deserialize(const std::string data);
    std::string getType() const override;
};

#endif//BEZIERS_CURVE_H

