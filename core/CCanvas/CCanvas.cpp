#include "CCanvas.h"
#include "CScene/CScene.h"

CCanvas::CCanvas(CScene* s, QWidget* parent) : QWidget(parent), scene(s) {

}

CCanvas::CCanvas(QWidget* parent) : QWidget(parent), scene(nullptr) {

}

void CCanvas::setScene(CScene* s) {
    scene=s;
}

void CCanvas::paintEvent(QPaintEvent* event) {

    QPainter painter(this);

    scene->render(painter);
}

double CCanvas::getScaleFactor() const {
    return 1;
}

QPointF CCanvas::getOffset() const {
    return QPointF(0, 0);
}