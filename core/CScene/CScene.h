#ifndef CScene_H
#define CScene_H

#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include <vector>
#include <string>
#include "CCanvas/CCanvas.h"
#include "CImage/CImage.h"
#include "COverlayImage/COverlayImage.h"

class CScene : public QObject {
    Q_OBJECT

    CCanvas* canvas;
    CImage* mainImage=nullptr;
    COverlayImage* overlay=nullptr;


public:

    explicit CScene(QObject* parent=nullptr);
    ~CScene();
    void setWidget(QWidget* widget);
    void render(QPainter& painter);

    CImage* getMainImage() const;
    void setMainImage(CImage* newImage);
    COverlayImage* getOverlayImage() const;

};

#endif // CScene_H