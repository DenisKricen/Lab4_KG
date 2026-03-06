#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QColor>
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
    Ui::CMainWindow *ui;

    QColor fillColor;
    QColor lineColor;

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    void onCreateClicked();
    void onClearClicked();
    void onChooseOutColor();
    void onChooseInColor();
};

#endif // CMAINWINDOW_H