#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include <iostream>
#include <cmath>
using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);

    // connect(scene, &CScene::changed, canvas, QOverload<>::of(&QWidget::update))

}

CMainWindow::~CMainWindow() {
    delete ui;
}

