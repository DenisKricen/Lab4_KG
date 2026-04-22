#ifndef CCANVAS_H
#define CCANVAS_H

#include <QWidget>
#include <QPainter>
class CScene;

class CCanvas : public QWidget {
    Q_OBJECT

    CScene* scene;

    public:

    explicit CCanvas(CScene* s, QWidget* parent=nullptr);
    explicit CCanvas(QWidget* parent=nullptr);
    void setScene(CScene* s);
    virtual void paintEvent(QPaintEvent* event) override;

    double getScaleFactor() const;
    QPointF getOffset() const;

};

#endif//CCANVAS_H