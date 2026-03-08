#include "CBeziersCurve.h"
#include <cmath>
#include <sstream>

CBeziersCurve::CBeziersCurve() {
    pace=0.05;
    tMin=0.0;
    tMax=1.0;
    curveColor = Qt::blue;
    rectColor = Qt::black;
    drawMethod = &CBeziersCurve::drawParam;
}

void CBeziersCurve::setCurveColor(const QColor& color) {
    curveColor = color;
}

void CBeziersCurve::setRectColor(const QColor& color) {
    rectColor = color;
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

double CBeziersCurve::getPace() const { return pace; }

void CBeziersCurve::setTMin(double val) {
    if (val >= 0.0 && val < tMax)
        tMin = val;
}

double CBeziersCurve::getTMin() const { return tMin; }

void CBeziersCurve::setTMax(double val) {
    if (val <= 1.0 && val > tMin)
        tMax = val;
}

double CBeziersCurve::getTMax() const { return tMax; }
QColor CBeziersCurve::getCurveColor() const { return curveColor; }
QColor CBeziersCurve::getRectColor() const { return rectColor; }

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
    std::ostringstream oss;
    oss << pace << " " << tMin << " " << tMax << " "
        << curveColor.red() << " " << curveColor.green() << " " << curveColor.blue() << " "
        << rectColor.red() << " " << rectColor.green() << " " << rectColor.blue() << " "
        << (isMatrixMode() ? 1 : 0);
    for (const auto& p : curve) {
        oss << " " << p.x() << " " << p.y();
    }
    return oss.str();
}

CBeziersCurve* CBeziersCurve::deserialize(const std::string data) {
    CBeziersCurve* c = new CBeziersCurve();
    std::istringstream iss(data);
    double p, tmin, tmax;
    int cr, cg, cb, rr, rg, rb, mode;
    if (!(iss >> p >> tmin >> tmax >> cr >> cg >> cb >> rr >> rg >> rb >> mode))
        return c;
    c->pace = p;
    c->tMin = tmin;
    c->tMax = tmax;
    c->curveColor = QColor(cr, cg, cb);
    c->rectColor = QColor(rr, rg, rb);
    c->drawMethod = (mode == 1) ? &CBeziersCurve::drawMatrix : &CBeziersCurve::drawParam;
    double x, y;
    while (iss >> x >> y) {
        c->curve.append(QPointF(x, y));
    }
    return c;
}

void CBeziersCurve::setDrawMethod(void (CBeziersCurve::* method)(QPainter&)) {
    drawMethod = method;
}

bool CBeziersCurve::isMatrixMode() const {
    return drawMethod == &CBeziersCurve::drawMatrix;
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
    QPen boxPen(rectColor, 2, Qt::DashLine);
    boxPen.setCosmetic(true);
    painter.setPen(boxPen);

    painter.drawRect(QRectF(QPointF(minX, minY), QPointF(maxX, maxY)));
    painter.restore();
}

void CBeziersCurve::drawParam(QPainter& painter) {
    if(curve.empty()) return;
    int dotsCount = curve.size();
    int n = dotsCount - 1;

    QVector<QPointF> points;
    int numSteps = std::max(1, static_cast<int>(std::ceil((tMax - tMin) / pace)));
    for(int step = 0; step <= numSteps; ++step) {
        double t = tMin + step * (tMax - tMin) / numSteps;
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
    QPen pen(curveColor, 2);
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
    int numSteps = std::max(1, static_cast<int>(std::ceil((tMax - tMin) / pace)));
    for(int step = 0; step <= numSteps; ++step) {
        double t = tMin + step * (tMax - tMin) / numSteps;
        
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
    QPen pen(curveColor, 2);
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.drawPolyline(points);
    painter.restore();
    drawRect(painter);
}

QString CBeziersCurve::getMatrixInfo() const {
    if (curve.size() < 2) return "Not enough points for matrix.";
    int dotsCount = curve.size();
    int n = dotsCount - 1;

    QVector<QVector<double>> M(dotsCount, QVector<double>(dotsCount, 0.0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            double Cnj = (double)fct(n) / (fct(j) * fct(n - j));
            double Cji = (double)fct(n - j) / (fct(n - i - j) * fct((n - j) - (n - i - j)));
            M[i][j] = pow(-1, n - j - i) * Cnj * Cji;
        }
    }

    int zeroCount = 0;
    for (int i = 0; i < dotsCount; i++)
        for (int j = 0; j < dotsCount; j++)
            if (M[i][j] == 0.0) zeroCount++;

    double firstRowSum = 0.0;
    for (int j = 0; j < dotsCount; j++)
        firstRowSum += M[0][j];

    double firstColSum = 0.0;
    for (int i = 0; i < dotsCount; i++)
        firstColSum += M[i][0];

    QString info;
    info += QString("Coefficient matrix (%1x%1):\n").arg(dotsCount);
    info += QString("Zero elements: %1\n").arg(zeroCount);
    info += QString("First row sum: %1\n").arg(firstRowSum, 0, 'f', 4);
    info += QString("First column sum: %1").arg(firstColSum, 0, 'f', 4);
    return info;
}