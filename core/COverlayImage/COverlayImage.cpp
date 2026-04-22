#include "COverlayImage/COverlayImage.h"

COverlayImage::COverlayImage() 
    : lockedPixel(-1, -1), isPixelVisible(false), isAreaVisible(false) {
}

void COverlayImage::setLockedPixel(const QPoint& pos) {
    lockedPixel = pos;
    isPixelVisible = true;
}

void COverlayImage::setSelectionArea(const QRect& area) {
    selectionArea = area;
    isAreaVisible = true;
}

void COverlayImage::setPixelVisible(bool visible) {
    isPixelVisible = visible;
}

void COverlayImage::setAreaVisible(bool visible) {
    isAreaVisible = visible;
}

void COverlayImage::clear() {
    isPixelVisible = false;
    isAreaVisible = false;
    lockedPixel = QPoint(-1, -1);
    selectionArea = QRect();
}

void COverlayImage::draw(QPainter* painter) {
    if (!painter) return;

    // Draw the Selection Area (Rectangle)
    if (isAreaVisible && !selectionArea.isNull()) {
        painter->save(); // Save state to avoid affecting other drawing operations
        
        // Fill the inside
        painter->fillRect(selectionArea, selectionFillColor);
        
        // Draw the border
        QPen pen(selectionBorderColor);
        pen.setStyle(Qt::DashLine); // Dashed border looks more like a selection tool
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRect(selectionArea);
        
        painter->restore();
        return;
    }

    // Draw the Locked Pixel Marker (Crosshair or small dot)
    if (isPixelVisible && lockedPixel.x() != -1) {
        painter->save();
        
        QPen pen(pixelMarkerColor);
        pen.setWidth(2);
        painter->setPen(pen);
        
        // Drawing a small crosshair centered on the pixel
        int size = 7;
        painter->drawLine(lockedPixel.x() - size, lockedPixel.y(), lockedPixel.x() + size, lockedPixel.y());
        painter->drawLine(lockedPixel.x(), lockedPixel.y() - size, lockedPixel.x(), lockedPixel.y() + size);
        
        painter->restore();
        return;
    }
}