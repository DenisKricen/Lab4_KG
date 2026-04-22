#ifndef CCOLORMATH_H
#define CCOLORMATH_H

#include <QColor>
#include <algorithm>
#include <cmath>

// Custom structures to hold high-precision color data.
struct SColorCMYK {
    double c; // Cyan    (0.0 to 1.0)
    double m; // Magenta (0.0 to 1.0)
    double y; // Yellow  (0.0 to 1.0)
    double k; // Black   (0.0 to 1.0)
};

struct SColorHSB {
    double h; // Hue        (0.0 to 360.0 degrees)
    double s; // Saturation (0.0 to 1.0)
    double b; // Brightness (0.0 to 1.0)
};

class CColorMath {
public:
    CColorMath() = delete;

    // --- RGB to CMYK & CMYK to RGB ---
    static SColorCMYK rgbToCmyk(const QColor& rgb);
    static QColor cmykToRgb(const SColorCMYK& cmyk);

    // --- RGB to HSB & HSB to RGB ---
    static SColorHSB rgbToHsb(const QColor& rgb);
    static QColor hsbToRgb(const SColorHSB& hsb);
};

#endif // CCOLORMATH_H