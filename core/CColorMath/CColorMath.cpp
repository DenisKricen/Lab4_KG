#include "CColorMath/CColorMath.h"

// ---------------------------------------------------------
// CMYK CONVERSIONS
// ---------------------------------------------------------

SColorCMYK CColorMath::rgbToCmyk(const QColor& rgb) {
    SColorCMYK result = {0.0, 0.0, 0.0, 0.0};

    // Normalize RGB values to 0.0 - 1.0 range
    double r = rgb.redF();
    double g = rgb.greenF();
    double b = rgb.blueF();

    // Calculate Key (Black)
    double k = 1.0 - std::max({r, g, b});
    result.k = k;

    // Prevent division by zero if the color is pure black (K = 1.0)
    if (k < 1.0) {
        result.c = (1.0 - r - k) / (1.0 - k);
        result.m = (1.0 - g - k) / (1.0 - k);
        result.y = (1.0 - b - k) / (1.0 - k);
    } else {
        // Pure black
        result.c = 0.0;
        result.m = 0.0;
        result.y = 0.0;
    }

    return result;
}

QColor CColorMath::cmykToRgb(const SColorCMYK& cmyk) {
    // Reverse the formulas to get normalized RGB
    double r = (1.0 - cmyk.c) * (1.0 - cmyk.k);
    double g = (1.0 - cmyk.m) * (1.0 - cmyk.k);
    double b = (1.0 - cmyk.y) * (1.0 - cmyk.k);

    // Convert back to 0-255 range and clamp safely
    int red = std::clamp(static_cast<int>(std::round(r * 255.0)), 0, 255);
    int green = std::clamp(static_cast<int>(std::round(g * 255.0)), 0, 255);
    int blue = std::clamp(static_cast<int>(std::round(b * 255.0)), 0, 255);

    return QColor(red, green, blue);
}

// ---------------------------------------------------------
// HSB (HSV) CONVERSIONS
// ---------------------------------------------------------

SColorHSB CColorMath::rgbToHsb(const QColor& rgb) {
    SColorHSB result = {0.0, 0.0, 0.0};

    double r = rgb.redF();
    double g = rgb.greenF();
    double b = rgb.blueF();

    double cmax = std::max({r, g, b});
    double cmin = std::min({r, g, b});
    double delta = cmax - cmin;

    // Brightness is simply the maximum color component
    result.b = cmax;

    // Calculate Saturation
    if (cmax > 0.0) {
        result.s = delta / cmax;
    } else {
        result.s = 0.0;
    }

    // Calculate Hue
    if (delta == 0.0) {
        result.h = 0.0; // Grayscale, hue is undefined (set to 0)
    } else if (cmax == r) {
        result.h = 60.0 * std::fmod(((g - b) / delta), 6.0);
    } else if (cmax == g) {
        result.h = 60.0 * (((b - r) / delta) + 2.0);
    } else if (cmax == b) {
        result.h = 60.0 * (((r - g) / delta) + 4.0);
    }

    // Ensure Hue is always positive
    if (result.h < 0.0) {
        result.h += 360.0;
    }

    return result;
}

QColor CColorMath::hsbToRgb(const SColorHSB& hsb) {
    double c = hsb.b * hsb.s;
    double x = c * (1.0 - std::abs(std::fmod(hsb.h / 60.0, 2.0) - 1.0));
    double m = hsb.b - c;

    double rPrime = 0.0, gPrime = 0.0, bPrime = 0.0;

    if (hsb.h >= 0.0 && hsb.h < 60.0) {
        rPrime = c; gPrime = x; bPrime = 0.0;
    } else if (hsb.h >= 60.0 && hsb.h < 120.0) {
        rPrime = x; gPrime = c; bPrime = 0.0;
    } else if (hsb.h >= 120.0 && hsb.h < 180.0) {
        rPrime = 0.0; gPrime = c; bPrime = x;
    } else if (hsb.h >= 180.0 && hsb.h < 240.0) {
        rPrime = 0.0; gPrime = x; bPrime = c;
    } else if (hsb.h >= 240.0 && hsb.h < 300.0) {
        rPrime = x; gPrime = 0.0; bPrime = c;
    } else if (hsb.h >= 300.0 && hsb.h < 360.0) {
        rPrime = c; gPrime = 0.0; bPrime = x;
    }

    int red = std::clamp(static_cast<int>(std::round((rPrime + m) * 255.0)), 0, 255);
    int green = std::clamp(static_cast<int>(std::round((gPrime + m) * 255.0)), 0, 255);
    int blue = std::clamp(static_cast<int>(std::round((bPrime + m) * 255.0)), 0, 255);

    return QColor(red, green, blue);
}