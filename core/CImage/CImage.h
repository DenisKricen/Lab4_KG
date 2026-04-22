#ifndef CIMAGE_H
#define CIMAGE_H

#include <QImage>
#include <QColor>
#include <QString>

class CImage {
public:
    // Default constructor
    CImage();

    // Constructor that loads an image from a file
    explicit CImage(const QString& filePath);

    // Destructor
    ~CImage() = default;

    // Loads an image from the specified file path
    bool load(const QString& filePath);

    // Saves the current image to the specified file path
    bool save(const QString& filePath) const;

    // Returns the color of the pixel at the specified coordinates (x, y)
    QColor getPixel(int x, int y) const;

    // Sets the color of the pixel at the specified coordinates (x, y)
    void setPixel(int x, int y, const QColor& color);

    // Returns the width of the image
    int width() const;

    // Returns the height of the image
    int height() const;

    // Checks if the image is empty or failed to load
    bool isNull() const;

    // Returns a copy of the underlying QImage (useful for rendering in CCanvas)
    QImage getRawImage() const;

private:
    QImage m_image;
};

#endif//CIMAGE_H