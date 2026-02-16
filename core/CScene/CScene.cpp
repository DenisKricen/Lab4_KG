#include "CScene.h"

void drawAxis(QPainter& painter, int x1, int y1, int x2, int y2, QColor color, int marks) {
    painter.setPen(QPen(color, 1));
    painter.drawLine(x1, y1, x2, y2);
}

void CScene::drawCoorSystem(QPainter& painter, int width, int height, int marks) {
    
    drawAxis(painter, width/2, 0, width/2, height, Qt::black, 1);
    drawAxis(painter, 0, height/2, width, height/2, Qt::black, 1);

    int markSize = 10;
    ordSegment=height/2/marks*0.98;
    absSegment=width/2/marks*0.98;
    double numberBias=absSegment/4;

    painter.setFont(QFont("Arial", width/5/marks));
    painter.drawText(width/2+numberBias*0.9,height/2+(markSize*2)+numberBias,"0");

    for(int i=1;i<=marks;i++) {

        // Abscise
        painter.setFont(QFont("Arial", width/5/marks));
        drawAxis(painter, width/2+i*absSegment, height/2-(markSize/2), width/2+i*absSegment, height/2+(markSize/2), Qt::black, 1);
        drawAxis(painter, width/2-i*absSegment, height/2-(markSize/2), width/2-i*absSegment, height/2+(markSize/2), Qt::black, 1);
        painter.drawText(width/2+i*absSegment-(numberBias),height/2+(markSize*2)+numberBias,QString::number(i));
        painter.drawText(width/2-i*absSegment-(numberBias*2),height/2+(markSize*2)+numberBias,QString::number(-i));

        // Ordinate
        painter.setFont(QFont("Arial", height/5/marks));
        drawAxis(painter, width/2-(markSize/2), height/2-i*(ordSegment), width/2+(markSize/2), height/2-i*(ordSegment), Qt::black, 1);
        drawAxis(painter, width/2-(markSize/2), height/2+i*(ordSegment), width/2+(markSize/2), height/2+i*(ordSegment), Qt::black, 1);
        painter.drawText(width/2+(markSize/2)+(numberBias),height/2-i*(ordSegment)+numberBias,QString::number(i));
        painter.drawText(width/2+(markSize/2)+(numberBias),height/2+i*(ordSegment)+numberBias,QString::number(-i));
    }

}

CScene::CScene(QObject* parent) : QObject(parent){

}

void CScene::setWidget(QWidget* widget){

    canvas = qobject_cast<CCanvas*>(widget);

}

void CScene::addFigure(CFigure* figure) {

    figures.push_back(figure);

}

void CScene::clearFigures() {

    for(auto figure : figures) {
        delete figure;
    }
    figures.clear();
}

double CScene::getAbsSegment() {
    return absSegment;
}

double CScene::getOrdSegment() {
    return ordSegment;
}

void CScene::render(QPainter& painter) {

    int cvWd = canvas->width();       // canvas width
    int cvHt = canvas->height();      // canvas height

    drawCoorSystem(painter, cvWd, cvHt, 25);
    
    painter.save();
    painter.translate(cvWd/2, cvHt/2);
    
    for(auto figure : figures) {
        figure->draw(painter);
    }
    
    painter.restore();

}