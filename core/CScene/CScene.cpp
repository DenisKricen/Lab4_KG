#include "CScene.h"

void drawAxis(QPainter& painter, int x1, int y1, int x2, int y2, QColor color, int marks) {
    painter.setPen(QPen(color, 3));
    painter.drawLine(x1, y1, x2, y2);
    // double lineLength = std::sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void drawCoorSystem(QPainter& painter, int width, int height, int marks) {
    
    drawAxis(painter, width/2, 0, width/2, height, Qt::blue, 1);
    drawAxis(painter, 0, height/2, width, height/2, Qt::red, 1);

}

CScene::CScene(QObject* parent) : QObject(parent){
    // Тут можна задати розмір сцени, якщо треба фіксований
    // setSceneRect(-500, -500, 1000, 1000);


}

void CScene::setWidget(QWidget* widget){

    canvas = qobject_cast<CCanvas*>(widget);

}

void CScene::addFigure(CFigure* figure) {

    figures.push_back(figure);

}

void CScene::render(QPainter& painter) {

    int cvWd = canvas->width();       // canvas width
    int cvHt = canvas->height();      // canvas height

    drawCoorSystem(painter, cvWd, cvHt, 1);
    for(auto figure : figures) {
        figure->draw(painter);
    }

}