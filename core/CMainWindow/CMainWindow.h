#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "CScene/CScene.h"    
#include "CCanvas/CCanvas.h"
#include "Figures/CFigure/CFigure.h"  

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QWidget {
    Q_OBJECT
private:
    CScene* scene;
    CCanvas* canvas;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:


    // void onAddTriangleClicked();
    // void onDrawClicked();
    // void onClearClicked();

private:
    Ui::CMainWindow *ui;
};

#endif // CMAINWINDOW_H