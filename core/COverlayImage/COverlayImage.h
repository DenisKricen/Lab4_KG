#ifndef COVERLAYIMAGE_H
#define COVERLAYIMAGE_H

#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QColor>

class COverlayImage {
    QPoint lockedPixel;
    QRect selectionArea;

    bool isPixelVisible;
    bool isAreaVisible;

    // Predefined colors for UI elements
    const QColor pixelMarkerColor = QColor(255, 0, 0, 200);       // Semi-transparent red
    const QColor selectionFillColor = QColor(0, 120, 215, 60);    // Very transparent blue
    const QColor selectionBorderColor = QColor(0, 120, 215, 200); // Solid blue border

public:
    COverlayImage();
    ~COverlayImage() = default;

    // Sets the coordinates for the single locked pixel marker
    void setLockedPixel(const QPoint& pos);
    
    // Sets the rectangle for the selected area
    void setSelectionArea(const QRect& area);

    // Visibility toggles
    void setPixelVisible(bool visible);
    void setAreaVisible(bool visible);

    // Clears all visual selections (called on Right Click)
    void clear();

    // Main drawing method called within CCanvas::paintEvent
    // It draws directly on the provided painter instance
    void draw(QPainter* painter);

};

#endif // COVERLAYIMAGE_H