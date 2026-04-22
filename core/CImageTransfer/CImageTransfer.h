#ifndef CIMAGETRANSFER_H
#define CIMAGETRANSFER_H

#include <QString>

// Forward declaration of CImage to avoid including the full header
class CImage;

class CImageTransfer {
public:
    // Delete the default constructor to prevent instantiation
    // This emphasizes that CImageTransfer is purely a static utility class
    CImageTransfer() = delete;

    // Imports an image from the specified file path.
    // Returns a dynamically allocated pointer to CImage on success, or nullptr on failure.
    // The caller is responsible for managing the memory of the returned object.
    static CImage* importImage(const QString& path);

    // Exports the provided image to the specified file path.
    // Returns true if the save was successful, false otherwise.
    static bool exportImage(const QString& path, const CImage* image);
};

#endif // CIMAGETRANSFER_H