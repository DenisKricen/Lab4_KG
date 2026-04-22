#ifndef CCANVAS_H
#define CCANVAS_H

#include <QWidget>
#include <QPainter>
class CScene;

class CCanvas : public QWidget {
    Q_OBJECT

    CScene* scene;

    double scaleFactor;
    QPointF offset;

    QPoint lastMousePos;
    bool isPanning;

    public:

    explicit CCanvas(CScene* s, QWidget* parent=nullptr);
    explicit CCanvas(QWidget* parent=nullptr);
    
    void setScene(CScene* s);
    double getScaleFactor() const;
    QPointF getOffset() const;
    
    protected:

    virtual void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif//CCANVAS_H