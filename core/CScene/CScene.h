#ifndef CScene_H
#define CScene_H

#include <QGraphicsScene>
#include <QPainter>

class CScene : public QGraphicsScene {
    Q_OBJECT // Макрос потрібен, якщо будеш використовувати сигнали/слоти
public:
    explicit CScene(QObject *parent = nullptr);

protected:
    // Тут малюється задній фон (сітка, осі)
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // CScene_H