#include "CHexagon.h"

CHexagon::CHexagon() {

    size=0;
    centerX=0;
    centerY=0;

    fillColor= Qt::black;
    outColor= Qt::black;
}

void CHexagon::setProperties(CProperties& prop) {
    size=prop.circumradius;
    centerX=prop.abscise;    
    centerY=prop.ordinate;   
    fillColor=prop.fillColor;
    outColor=prop.outColor;
}

void CHexagon::draw(QPainter& painter) {
    QPen pen(outColor, 2);
    pen.setCosmetic(true);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setMiterLimit(10.0);
    
    painter.setPen(pen);
    painter.setBrush(fillColor);
    painter.save();
    
    painter.translate(centerX, centerY);

    QPolygonF hexagon;
    QPolygonF center;
    for (int i = 0; i < 6; i++) {
        double angle = M_PI / 3.0 * i;
        double dx = size * cos(angle);
        double dy = size * sin(angle);
        
        hexagon << QPointF(dx, dy);
    }
    painter.drawPolygon(hexagon);

    //Center
    double dotScale=0.0001;
    center << QPointF(size*dotScale,   size*dotScale)   << QPointF(size*dotScale*2, size*dotScale) \
           << QPointF(size*dotScale*2, size*dotScale*2) << QPointF(size*dotScale,   size*dotScale*2);

    painter.save();
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::black));
    painter.scale(0.2,0.2);
    painter.drawPolygon(center);
    painter.restore();

    //Radius
    painter.save();
    painter.setPen(QPen(Qt::black, 0.1));
    painter.drawLine(0, 0,size,0);
    painter.restore();

    //Circle
    painter.save();
    painter.setPen(QPen(Qt::black, 0.1));
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.drawEllipse(-size,-size,size*2, size*2);
    painter.restore();

    painter.restore();
}

std::string CHexagon::getType() const {
    return "hexagon";
}

std::string CHexagon::serialize() const {
    std::ostringstream oss;
    oss << centerX << " " << centerY << " " << size << " "
        << fillColor.red() << " " << fillColor.green() << " " << fillColor.blue() << " "
        << outColor.red() << " " << outColor.green() << " " << outColor.blue();
    return oss.str();
}

CHexagon* CHexagon::deserialize(const std::string& data) {
    std::istringstream iss(data);
    CHexagon* hex = new CHexagon();
    int fr, fg, fb, or_, og, ob;
    iss >> hex->centerX >> hex->centerY >> hex->size >> fr >> fg >> fb >> or_ >> og >> ob;
    hex->fillColor = QColor(fr, fg, fb);
    hex->outColor = QColor(or_, og, ob);
    return hex;
}