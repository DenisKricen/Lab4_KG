#ifndef CScene_H
#define CScene_H

#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include "CCanvas/CCanvas.h"
#include <vector>
#include <string>

class CScene : public QObject {
    Q_OBJECT

    CCanvas* canvas;

public:

    explicit CScene(QObject* parent=nullptr);
    void setWidget(QWidget* widget);
    void render(QPainter& painter);

};

#endif // CScene_H