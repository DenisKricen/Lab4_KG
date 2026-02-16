#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "CScene/CScene.h"    
#include "CCanvas/CCanvas.h"
#include "Figures/CFigure/CFigure.h"

// Forward declaration для використання в CProperties
namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QWidget {
    Q_OBJECT
private:
    CScene* scene;
    CCanvas* canvas;
    Ui::CMainWindow *ui;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    void onAddTriangleClicked();
    void onClearClicked();
    // void onDrawClicked();
    // void onClearClicked();
};

#endif // CMAINWINDOW_H