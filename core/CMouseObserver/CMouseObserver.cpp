#include "CMouseObserver/CMouseObserver.h"

CMouseObserver::CMouseObserver(QObject *parent) 
    : QObject(parent), isSelecting(false) {
}

bool CMouseObserver::eventFilter(QObject *watched, QEvent *event) {
    // We are only interested in mouse events
    if (event->type() == QEvent::MouseMove || 
        event->type() == QEvent::MouseButtonPress || 
        event->type() == QEvent::MouseButtonRelease) {
        
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint currentPos = mouseEvent->pos();

        if (event->type() == QEvent::MouseButtonPress) {
            if (mouseEvent->button() == Qt::LeftButton) {
                // User pressed Left Mouse Button: start tracking for potential drag
                startPoint = currentPos;
                isSelecting = true;
                
                // Immediately emit a click signal in case they just want a single pixel
                emit pixelClicked(currentPos);
            } 
            else if (mouseEvent->button() == Qt::RightButton) {
                // User pressed Right Mouse Button: command to clear
                emit selectionCleared();
            }
        } 
        else if (event->type() == QEvent::MouseMove) {
            if (isSelecting && (mouseEvent->buttons() & Qt::LeftButton)) {
                // User is holding LMB and moving -> calculating the selection area
                // QRect::normalized() ensures width/height are positive regardless of drag direction
                QRect selectionRect = QRect(startPoint, currentPos).normalized();
                
                // Add a small threshold (e.g., 3 pixels) to differentiate an accidental jitter from a real drag
                if (selectionRect.width() > 3 || selectionRect.height() > 3) {
                    emit areaSelecting(selectionRect);
                }
            } else {
                // User is just moving the mouse without holding LMB
                emit mouseHovered(currentPos);
            }
        } 
        else if (event->type() == QEvent::MouseButtonRelease) {
            if (mouseEvent->button() == Qt::LeftButton && isSelecting) {
                isSelecting = false;
                
                QRect finalRect = QRect(startPoint, currentPos).normalized();
                
                // If it was an actual drag (not just a click), confirm the area selection
                if (finalRect.width() > 3 || finalRect.height() > 3) {
                    emit areaSelected(finalRect);
                }
            }
        }
    }

    
    return false; 
}