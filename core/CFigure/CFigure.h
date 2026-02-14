#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include <QGraphicsItem>
#include <QPainter>

class MyTriangle : public QGraphicsItem {
public:
    MyTriangle();

    // 1. Цей метод визначає межі фігури (щоб мишка знала, де клікати)
    QRectF boundingRect() const override;

    // 2. Цей метод малює саму фігуру
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYTRIANGLE_H