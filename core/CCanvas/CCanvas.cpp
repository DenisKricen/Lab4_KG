#include "CCanvas/CCanvas.h"
#include "CScene/CScene.h"
#include <QPainter>
#include <QWheelEvent>  
#include <QMouseEvent>

CCanvas::CCanvas(QWidget *parent) 
    : QWidget(parent), 
      scene(nullptr), 
      scaleFactor(1.0), 
      offset(0, 0), 
      isPanning(false) {
    setMouseTracking(true);
}

void CCanvas::setScene(CScene* newScene) {
    scene = newScene;
    
    scaleFactor = 1.0;
    offset = QPointF(0, 0);
    update();
}

double CCanvas::getScaleFactor() const {
    return scaleFactor;
}

QPointF CCanvas::getOffset() const {
    return offset;
}

void CCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    if (!scene) 
        return;

    painter.translate(offset);    
    painter.scale(scaleFactor, scaleFactor);
    
    scene->render(painter);
}

void CCanvas::wheelEvent(QWheelEvent *event) {
    double zoomMultiplier = 1.15; 
    if (event->angleDelta().y() < 0) {
        zoomMultiplier = 1.0 / zoomMultiplier;
    }

    QPointF mousePos = event->position();    
    QPointF oldPosInImage = (mousePos - offset) / scaleFactor;

    scaleFactor *= zoomMultiplier;
    if (scaleFactor < 0.05) scaleFactor = 0.05;
    if (scaleFactor > 50.0) scaleFactor = 50.0;

    QPointF newPosInImage = oldPosInImage * scaleFactor;
    
    offset = mousePos - newPosInImage;

    update();
}

void CCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        isPanning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor); 
    }
}

void CCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (isPanning) {
        QPoint delta = event->pos() - lastMousePos;
        
        offset += delta;
        lastMousePos = event->pos();
        
        update();
    }
}

void CCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
}