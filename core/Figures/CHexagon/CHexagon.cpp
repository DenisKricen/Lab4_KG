#include "CHexagon.h"

CHexagon::CHexagon() {

    size=0;
    centerX=0;
    centerY=0;

    fillColor= Qt::black;
    outColor= Qt::black;

    absCoef=1;
    ordCoef=1;
}

void CHexagon::setProperties(CProperties& prop) {
    size=prop.circumradius;
    centerX=prop.abscise;    
    centerY=prop.ordinate;   
    fillColor=prop.fillColor;
    outColor=prop.outColor;
    absCoef=prop.absCoef;
    ordCoef=prop.ordCoef;
}

void CHexagon::draw(QPainter& painter) {
    painter.setPen(QPen(outColor, 3));
    painter.setBrush(fillColor);
    painter.save();
    
    double pixelCenterX = centerX * absCoef;
    double pixelCenterY = -centerY * ordCoef;  // Inversing ordinate (in Qt Y axis goes dows)
    painter.translate(pixelCenterX, pixelCenterY);

    QPolygon hexagon;
    for (int i = 0; i < 6; i++) {
        double angle = M_PI / 3.0 * i;
        double dx = size * cos(angle);
        double dy = size * sin(angle);
        
        int x = dx * absCoef;
        int y = -dy * ordCoef;  // Inversing ordinate
        
        hexagon << QPoint(x, y);
    }
    painter.drawPolygon(hexagon);

    painter.restore();
}