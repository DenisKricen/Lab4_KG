#include "CTriangle.h"

CTriangle::CTriangle(int x, int y, int s) : centerX(x), centerY(y), size(s) {

}

void CTriangle::draw(QPainter& painter) {

    painter.setPen(QPen(Qt::red, 3));
    painter.save();
    painter.translate(centerX, centerY);

    QPolygon triangle;

    triangle << QPoint(0, 0) << QPoint(size, 0) << QPoint(0, size);
    painter.drawPolygon(triangle);

    painter.restore();
}