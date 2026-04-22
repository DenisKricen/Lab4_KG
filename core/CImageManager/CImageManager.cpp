#include "CImageManager/CImageManager.h"
#include "CImage/CImage.h"
#include "CColorMath/CColorMath.h"
#include <QColor>
#include <algorithm>

void CImageManager::adjustBlueBrightness(CImage* image, const QRect& area, double brightnessOffset) {
    if (!image || image->isNull() || area.isNull()) 
        return;

    // Ensure the area stays within the image boundaries
    int startX = std::max(0, area.left());
    int startY = std::max(0, area.top());
    int endX = std::min(image->width() - 1, area.right());
    int endY = std::min(image->height() - 1, area.bottom());

    // Convert percentage offset to a 0.0 - 1.0 range modifier
    double modifier = brightnessOffset / 100.0;

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            QColor pixelColor = image->getPixel(x, y);

            SColorHSB hsb = CColorMath::rgbToHsb(pixelColor);

            // Check if the pixel is blue (Hue between 200 and 280 degrees)
            // Also checking saturation so we don't catch gray pixels
            if (hsb.h >= 200.0 && hsb.h <= 280.0 && hsb.s > 0.1) { 
                
                // Modify brightness and clamp it between 0.0 and 1.0
                hsb.b += modifier;
                hsb.b = std::clamp(hsb.b, 0.0, 1.0);

                // Convert back to RGB and save
                QColor newRgb = CColorMath::hsbToRgb(hsb);
                image->setPixel(x, y, newRgb);
            }
        }
    }
}

void CImageManager::adjustCyanChannel(CImage* image, const QRect& area, double cyanOffset) {
    if (!image || image->isNull() || area.isNull()) return;

    int startX = std::max(0, area.left());
    int startY = std::max(0, area.top());
    int endX = std::min(image->width() - 1, area.right());
    int endY = std::min(image->height() - 1, area.bottom());

    double modifier = cyanOffset / 100.0;

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            QColor pixelColor = image->getPixel(x, y);
            
            SColorCMYK cmyk = CColorMath::rgbToCmyk(pixelColor);
            
            // Adjust Cyan
            cmyk.c += modifier;
            cmyk.c = std::clamp(cmyk.c, 0.0, 1.0);
            
            QColor newRgb = CColorMath::cmykToRgb(cmyk);
            image->setPixel(x, y, newRgb);
        }
    }
}

void CImageManager::convertToCMYK(CImage* image) {
    if (!image || image->isNull()) return;

    for (int y = 0; y < image->height(); ++y) {
        for (int x = 0; x < image->width(); ++x) {
            QColor originalPixel = image->getPixel(x, y);
            
            SColorCMYK cmyk = CColorMath::rgbToCmyk(originalPixel);
            
            QColor newPixel = CColorMath::cmykToRgb(cmyk);
            image->setPixel(x, y, newPixel);
        }
    }
}

void CImageManager::convertToHSB(CImage* image) {
    if (!image || image->isNull()) return;

    for (int y = 0; y < image->height(); ++y) {
        for (int x = 0; x < image->width(); ++x) {
            QColor originalPixel = image->getPixel(x, y);
            
            SColorHSB hsb = CColorMath::rgbToHsb(originalPixel);
            
            QColor newPixel = CColorMath::hsbToRgb(hsb);
            image->setPixel(x, y, newPixel);
        }
    }
}