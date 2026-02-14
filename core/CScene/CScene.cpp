#include "CScene.h"

CScene::CScene(QObject *parent) : QGraphicsScene(parent) {
    // Тут можна задати розмір сцени, якщо треба фіксований
    // setSceneRect(-500, -500, 1000, 1000);
}

void CScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // 1. Спочатку малюємо стандартний фон (білий/сірий)
    // QGraphicsScene::drawBackground(painter, rect);

    // 2. ТУТ ПИШИ КОД ДЛЯ ОСЕЙ І СІТКИ
    // painter->drawLine(...)
    
    // Приклад (просто щоб ти бачив, що воно працює):
    painter->setPen(QPen(Qt::lightGray, 1));
    painter->drawRect(rect); // Обводка по межі видимості
}