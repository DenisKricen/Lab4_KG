#ifndef CMOUSEOBSERVER_H
#define CMOUSEOBSERVER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>

class CMouseObserver : public QObject {
    Q_OBJECT

    
private:
    QPoint startPoint;  // Stores the starting coordinate of a selection drag
    bool isSelecting;   // Flag to track if the user is currently holding LMB and dragging
    
protected:
    // Core Qt mechanism to intercept events before they reach the target widget
    bool eventFilter(QObject *watched, QEvent *event) override;

public:
    explicit CMouseObserver(QObject *parent = nullptr);

signals:
    // Emitted when the mouse just moves over the canvas (without clicking)
    void mouseHovered(QPoint pos);

    // Emitted when the Left Mouse Button is clicked on a specific pixel
    void pixelClicked(QPoint pos);

    // Emitted continuously while dragging the Left Mouse Button (for drawing the overlay box)
    void areaSelecting(QRect area);

    // Emitted when the Left Mouse Button is released after dragging
    void areaSelected(QRect area);

    // Emitted when the Right Mouse Button is clicked to clear locks/selections
    void selectionCleared();


};

#endif // CMOUSEOBSERVER_H