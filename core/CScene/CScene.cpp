#include "CScene.h"
#include <fstream>
#include <sstream>
#include <algorithm>



CScene::CScene(QObject* parent) : QObject(parent){
    overlay = new COverlayImage();
}

CScene::~CScene() {
    if(mainImage) {
        delete mainImage;
    }

    delete overlay;
}

void CScene::setWidget(QWidget* widget){
    canvas = qobject_cast<CCanvas*>(widget);
}

void CScene::render(QPainter& painter) {

    if (!mainImage) {
        return;
    }

    if (mainImage->isNull()) {
        return;
    }

    painter.drawImage(0, 0, mainImage->getRawImage());

    // Overlay drawing
    if (overlay) {
        overlay->draw(&painter);
    }
}

CImage* CScene::getMainImage() const {
    return mainImage;
}

void CScene::setMainImage(CImage* newImage) {
    // If there is an existing image, we must release its memory first
    if (mainImage) {
        delete mainImage;
    }

    // Assign the pointer to the new image object
    mainImage = newImage;
}

COverlayImage* CScene::getOverlayImage() const {
    return overlay;
}