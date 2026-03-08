#include "CScene.h"
#include "Figures/CHexagon/CHexagon.h"
#include "Figures/CTriangle/CTriangle.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void drawAxis(QPainter& painter, int x1, int y1, int x2, int y2, QColor color, int marks) {
    painter.setPen(QPen(color, 1));
    painter.drawLine(x1, y1, x2, y2);

}

void CScene::drawCoorSystem(QPainter& painter, int width, int height, int marks) {
    
    drawAxis(painter, width/2, 0, width/2, height,  Qt::black, 1);
    drawAxis(painter, 0, height/2, width, height/2, Qt::black, 1);

    //Arrows for axis
    double offset=width*0.02;
    painter.drawLine(width/2, 0, width/2+offset, 0+offset);
    painter.drawLine(width/2, 0, width/2-offset, 0+offset);
    painter.setFont(QFont("Arial", width/5/marks));
    painter.drawText(width/2-offset*2, height*0.02, "Y");

    painter.drawLine(width, height/2, width-offset, height/2+offset);
    painter.drawLine(width, height/2, width-offset, height/2-offset);
    painter.drawText(width-offset, height/2*0.95, "X");

    int markSize = 10;
    ordSegment=height/2/marks*0.98;
    absSegment=width/2/marks*0.98;
    // Use uniform scaling so figures aren't distorted
    double uniformSegment = std::min(absSegment, ordSegment);
    absSegment = uniformSegment;
    ordSegment = uniformSegment;
    double numberBias=absSegment/4;
    double ordBias=ordSegment/4;

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
        painter.drawText(width/2+(markSize/2)+(ordBias),height/2-i*(ordSegment)+ordBias,QString::number(i));
        painter.drawText(width/2+(markSize/2)+(ordBias),height/2+i*(ordSegment)+ordBias,QString::number(-i));
    }

}

CScene::CScene(QObject* parent) : QObject(parent){
    CBeziersCurve* c = new CBeziersCurve();
    addFigure(c);
}

CBeziersCurve* CScene::getCurve() {
    for (auto fig : figures) {
        if (fig->getType() == "beziers_curve")
            return static_cast<CBeziersCurve*>(fig);
    }
    return nullptr;
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

    drawCoorSystem(painter, cvWd, cvHt, 10);
    
    painter.save();
    painter.translate(cvWd/2, cvHt/2);
    QPen pen(Qt::black, 2);
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.scale(absSegment, -ordSegment); 
    
    for(auto figure : figures) {
        figure->draw(painter);
    }
    
    painter.restore();

}

void CScene::saveFigures(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    for(auto fig : figures) {
        file << fig->getType() << " " << fig->serialize() << "\n";
    }
    file.close();
}

void CScene::loadFigures(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    clearFigures();
    
    std::string line;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        std::string data;
        std::getline(iss, data);
        if(!data.empty() && data[0] == ' ') data = data.substr(1);
        
        if(type == "hexagon") {
            figures.push_back(CHexagon::deserialize(data));
        } else if(type == "triangle") {
            figures.push_back(CTriangle::deserialize(data));
        } else if(type == "beziers_curve") {
            figures.push_back(CBeziersCurve::deserialize(data));
        }
    }
    file.close();

    if (!getCurve()) {
        addFigure(new CBeziersCurve());
    }
}