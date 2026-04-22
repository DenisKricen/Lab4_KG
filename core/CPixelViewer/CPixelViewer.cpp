#include "CPixelViewer/CPixelViewer.h"
#include "CImage/CImage.h"

CPixelViewer::CPixelViewer() 
    : currentRealPos(-1, -1), lockedPixel(-1, -1), isAreaLocked(false) {
}

QPoint CPixelViewer::mapToImage(const QPoint& screenPos, double scale, const QPointF& offset) const {
    // Avoid division by zero just in case
    if (scale <= 0.0) 
        return QPoint(-1, -1);

    // Standard math to convert screen coordinates back to original image scale
    int realX = static_cast<int>((screenPos.x() - offset.x()) / scale);
    int realY = static_cast<int>((screenPos.y() - offset.y()) / scale);

    return QPoint(realX, realY);
}

void CPixelViewer::updateHoverData(const QPoint& screenPos, double scale, const QPointF& offset, const CImage* image) {
    // Calculate real coordinates
    currentRealPos = mapToImage(screenPos, scale, offset);

    // Read the pixel color if the image exists and coordinates are within bounds
    if (image && !image->isNull()) {
        currentColor = image->getPixel(currentRealPos.x(), currentRealPos.y());
    } else {
        currentColor = QColor(); // Invalid color if out of bounds
    }
}

void CPixelViewer::lockPixel(const QPoint& realPos) {
    lockedPixel = realPos;
    // When locking a single pixel, the area is just 1x1 pixel
    lockedArea = QRect(realPos, QSize(1, 1));
    isAreaLocked = true;
}

void CPixelViewer::lockArea(const QRect& realArea) {
    lockedArea = realArea;
    isAreaLocked = true;
}

void CPixelViewer::clearLocks() {
    lockedPixel = QPoint(-1, -1);
    lockedArea = QRect();
    isAreaLocked = false;
}

QRect CPixelViewer::getLockedArea() const {
    return lockedArea;
}

QString CPixelViewer::getStatusRGB() const {
    if (!currentColor.isValid()) 
        return "RGB: -";

    return QString("RGB: (%1, %2, %3)")
        .arg(currentColor.red()).arg(currentColor.green()).arg(currentColor.blue());
}

QString CPixelViewer::getStatusCMYK() const {
    if (!currentColor.isValid()) 
        return "CMYK: -";

    int c, m, y, k, a;
    currentColor.getCmyk(&c, &m, &y, &k, &a);
    return QString("CMYK: (%1, %2, %3, %4)").arg(c).arg(m).arg(y).arg(k);
}

QString CPixelViewer::getStatusHSB() const {
    if (!currentColor.isValid()) 
        return "HSB: -";

    // In Qt, HSV and HSB are identical
    int h, s, v, a;
    currentColor.getHsv(&h, &s, &v, &a);
    return QString("HSB: (%1°, %2%, %3%)").arg(h).arg(s).arg(v);
}

QString CPixelViewer::getCoordinatesText() const {
    if (currentRealPos.x() < 0 || currentRealPos.y() < 0) 
        return "Pos: INVALID";
    return QString("Pos: [%1, %2]").arg(currentRealPos.x()).arg(currentRealPos.y());
}

QColor CPixelViewer::getCurrentColor() const {
    return currentColor;
}

bool CPixelViewer::isLocked() const {
    return isAreaLocked;
}