#include "CImage.h"
#include <QDebug>

CImage::CImage() {
    // Initializes an empty QImage by default
}

CImage::CImage(const QString& filePath) {
    load(filePath);
}

bool CImage::load(const QString& filePath) {
    bool success = m_image.load(filePath);
    
    // Ensure the image is converted to a format suitable for pixel manipulation (32-bit RGB)
    if (success) {
        m_image = m_image.convertToFormat(QImage::Format_ARGB32);
    } else {
        qWarning() << "Failed to load image from:" << filePath;
    }
    
    return success;
}

bool CImage::save(const QString& filePath) const {
    if (isNull()) {
        qWarning() << "Cannot save an empty image.";
        return false;
    }
    return m_image.save(filePath);
}

QColor CImage::getPixel(int x, int y) const {
    // Boundary check to prevent application crashes
    if (x < 0 || x >= width() || y < 0 || y >= height()) {
        return QColor(); // Returns an invalid color
    }
    return m_image.pixelColor(x, y);
}

void CImage::setPixel(int x, int y, const QColor& color) {
    // Boundary check
    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        m_image.setPixelColor(x, y, color);
    }
}

int CImage::width() const {
    return m_image.width();
}

int CImage::height() const {
    return m_image.height();
}

bool CImage::isNull() const {
    return m_image.isNull();
}

QImage CImage::getRawImage() const {
    return m_image;
}