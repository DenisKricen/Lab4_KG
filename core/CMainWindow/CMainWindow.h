#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QColor>
#include <QWidget>
#include <QListWidgetItem>
#include "CScene/CScene.h"    
#include "CCanvas/CCanvas.h"
#include "CMouseObserver/CMouseObserver.h"
#include "COverlayImage/COverlayImage.h"
#include "CPixelViewer/CPixelViewer.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QWidget {
    Q_OBJECT
private:
    CScene* scene=nullptr;
    CCanvas* canvas=nullptr;
    Ui::CMainWindow *ui;

    CMouseObserver* mouseObserver=nullptr;
    CPixelViewer* pixelViewer = nullptr;

    const QString DEFAULT_PATH = "/home/denys/Desktop/University/year_2025_2026/sem4/KG/Lab4_KG/save/";

protected:
    void resizeEvent(QResizeEvent *event) override;

public:

    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:

    void onImportClicked();
    void onExportClicked();
    
};

#endif // CMAINWINDOW_H