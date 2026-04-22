#ifndef CPIXELVIEWER_H
#define CPIXELVIEWER_H

#include <QString>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QColor>

// Forward declaration to avoid including the whole image header
class CImage;

class CPixelViewer {

    QColor currentColor;
    QPoint currentRealPos;
    
    QPoint lockedPixel;
    QRect lockedArea;
    bool isAreaLocked;

public:
    CPixelViewer();
    ~CPixelViewer() = default;

    // Maps screen coordinates to real image coordinates using current zoom and offset
    QPoint mapToImage(const QPoint& screenPos, double scale, const QPointF& offset) const;

    // Processes a hover event, extracting pixel color if coordinates are valid
    void updateHoverData(const QPoint& screenPos, double scale, const QPointF& offset, const CImage* image);

    // Locks a specific pixel or area (stores real coordinates)
    void lockPixel(const QPoint& realPos);
    void lockArea(const QRect& realArea);
    
    // Clears all locks
    void clearLocks();

    // Gets the finalized area that CImageManager will use
    QRect getLockedArea() const;

    // These methods format the stored color into nice strings for your UI
    QString getStatusRGB() const;
    QString getStatusCMYK() const;
    QString getStatusHSB() const;
    QString getCoordinatesText() const;

    // Returns the raw color to update your QFrame background
    QColor getCurrentColor() const;

    bool isLocked() const;
};

#endif // CPIXELVIEWER_H