#include "CImageTransfer.h"
#include "CImage/CImage.h" 
#include <QDebug>

CImage* CImageTransfer::importImage(const QString& path) {
    // Validate the provided file path
    if (path.isEmpty()) {
        qWarning() << "Failed to import: File path is empty.";
        return nullptr;
    }

    // Allocate a new CImage object dynamically
    CImage* newImage = new CImage();

    // Attempt to load the image data from the file
    if (newImage->load(path)) {
        qDebug() << "Successfully imported image from:" << path;
        // Return the pointer. The caller (e.g., CMainWindow or CScene) must take ownership.
        return newImage;
    } else {
        // If loading fails, clean up the allocated memory immediately to prevent leaks
        delete newImage;
        qWarning() << "Failed to load image from:" << path;
        return nullptr;
    }
}

bool CImageTransfer::exportImage(const QString& path, const CImage* image) {
    // Check if the provided pointer is valid
    if (!image) {
        qWarning() << "Failed to export: CImage pointer is null.";
        return false;
    }

    // Check if the image actually contains data
    if (image->isNull()) {
        qWarning() << "Failed to export: The image is empty (null).";
        return false;
    }

    // Validate the provided file path
    if (path.isEmpty()) {
        qWarning() << "Failed to export: File path is empty.";
        return false;
    }

    // Attempt to save the image to the specified path
    if (image->save(path)) {
        qDebug() << "Successfully exported image to:" << path;
        return true;
    } else {
        qWarning() << "Failed to save image to:" << path;
        return false;
    }
}