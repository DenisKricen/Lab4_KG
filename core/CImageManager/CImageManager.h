#ifndef CIMAGEMANAGER_H
#define CIMAGEMANAGER_H

#include <QRect>

class CImage;

class CImageManager {
public:
    CImageManager() = delete;

    static void convertToCMYK(CImage* image);
    static void convertToHSB(CImage* image);

    static void adjustBlueBrightness(CImage* image, const QRect& area, double brightnessOffset);
    static void adjustCyanChannel(CImage* image, const QRect& area, double cyanOffset);
};

#endif//CIMAGEMANAGER_H