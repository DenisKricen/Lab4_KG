#include "CFigure.h"

MyTriangle::MyTriangle() {
    // Тут можна задати початкові параметри (наприклад, дозволити перетягування)
    setFlag(ItemIsMovable);
}

QRectF MyTriangle::boundingRect() const {
    // ПОВЕРНИ ТУТ розмір свого трикутника (x, y, ширина, висота)
    // Наприклад: return QRectF(-50, -50, 100, 100);
    return QRectF(-50, -50, 100, 100); 
}

void MyTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // ТУТ ПИШИ КОД МАЛЮВАННЯ (painter->drawPolygon...)
    // Використовуй координати відносно центру (0,0)
    QPolygon polygon;
    polygon << QPoint(0, -50) << QPoint(50, 50) << QPoint(-50, 50);
    
    painter->setBrush(Qt::green);
    painter->drawPolygon(polygon);
}