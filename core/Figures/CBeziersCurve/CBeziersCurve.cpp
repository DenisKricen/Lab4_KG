#include "CBeziersCurve.h"
#include <cmath>

CBeziersCurve::CBeziersCurve() {
    pace=0.05;
    tMin=0.0;
    tMax=1.0;
    drawMethod = &CBeziersCurve::drawParam;
}

void CBeziersCurve::addPoint(const QPointF& point) {
    curve.append(point);
}

void CBeziersCurve::editPoint(int index, const QPointF& point) {
    if (index >= 0 && index < curve.size())
        curve[index] = point;
}

void CBeziersCurve::removePoint(int index) {
    if (index >= 0 && index < curve.size())
        curve.remove(index);
}

void CBeziersCurve::movePoint(int from, int to) {
    if (from >= 0 && from < curve.size() && to >= 0 && to < curve.size()) {
        QPointF point = curve[from];
        curve.remove(from);
        curve.insert(to, point);
    }
}

void CBeziersCurve::clearPoints() {
    curve.clear();
}

const QVector<QPointF>& CBeziersCurve::getPoints() const {
    return curve;
}

void CBeziersCurve::setPace(double p) {
    if (p > 0) pace = p;
}

void CBeziersCurve::setTMin(double val) {
    if (val >= 0.0 && val < tMax)
        tMin = val;
}

void CBeziersCurve::setTMax(double val) {
    if (val <= 1.0 && val > tMin)
        tMax = val;
}

std::string CBeziersCurve::getType() const{
    return "beziers_curve";
}

int fct(int num) {
    int result = 1;
    for (int i = 2; i <= num; ++i)
        result *= i;
    return result;
}

std::string CBeziersCurve::serialize() const {
    return " ";
}

CBeziersCurve* CBeziersCurve::deserialize(const std::string data) {
    return new CBeziersCurve();
}

void CBeziersCurve::setDrawMethod(void (CBeziersCurve::* method)(QPainter&)) {
    drawMethod = method;
}

void CBeziersCurve::draw(QPainter& painter) {
    (this->*drawMethod)(painter);
}

void CBeziersCurve::drawRect(QPainter& painter) {
    if (curve.isEmpty()) return;

    double minX = curve[0].x();
    double maxX = curve[0].x();
    double minY = curve[0].y();
    double maxY = curve[0].y();

    for (const QPointF& p : curve) {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }

    painter.save();
    QPen boxPen(Qt::green, 1, Qt::DashLine);
    painter.setPen(boxPen);

    painter.drawRect(QRectF(QPointF(minX, minY), QPointF(maxX, maxY)));
    painter.restore();
}

void CBeziersCurve::drawParam(QPainter& painter) {
    if(curve.empty()) return;
    int dotsCount = curve.size();
    int n = dotsCount - 1;

    QVector<QPointF> points;
    for(double t=tMin; t<=tMax+pace/2; t+=pace) {
        QPointF point;
        for(int i=0;i<dotsCount;i++) {

            double A = (double)fct(n)/(fct(i)*fct(n-i));
            double B = A * pow(t,i)*pow(1-t,n-i);

            point.rx() += curve[i].x() * B;
            point.ry() += curve[i].y() * B;
        }
        points.append(point);
    }

    painter.save();
    QPen pen(Qt::blue, 2);
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.drawPolyline(points);
    painter.restore();
    drawRect(painter);
}

void CBeziersCurve::drawMatrix(QPainter& painter) {
    if(curve.empty()) return;
    int dotsCount = curve.size();
    int n = dotsCount - 1;

    QVector<QVector<double>> M(dotsCount, QVector<double>(dotsCount, 0.0));
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n-i; j++) {
            double Cnj = (double)fct(n) / (fct(j) * fct(n - j));
            double Cji = (double)fct(n-j) / (fct(n-i-j) * fct((n-j)-(n-i-j)));
            M[i][j] = pow(-1, n-j-i) * Cnj * Cji;
        }
    }

    QVector<QVector<double>> Mt(dotsCount, QVector<double>(dotsCount, 0.0));
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            Mt[i][j] = M[j][i];
        }
    }

    QVector<QPointF> points;
    for(double t = tMin; t <= tMax + pace / 2.0; t += pace) {
        
        QVector<double> T;
        for(int i = n; i >= 0; i--) {
            T.append(pow(t, i));
        }

        QVector<double> C(dotsCount, 0.0);
        for(int j = 0; j <= n; j++) {
            for(int i = 0; i <= n; i++) {
                C[j] += T[i] * M[i][j]; 
            }
        }

        QPointF point(0, 0);
        for(int j = 0; j <= n; j++) {
            point.rx() += curve[j].x() * C[j];
            point.ry() += curve[j].y() * C[j];
        }

        points.append(point);
    }

    painter.save();
    QPen pen(Qt::red, 2);
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.drawPolyline(points);
    painter.restore();
    drawRect(painter);
}