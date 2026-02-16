#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include "Figures/CTriangle/CTriangle.h"
#include "Figures/CHexagon/CHexagon.h"
#include <iostream>
#include <cmath>
using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);

    connect(ui->btnCreate, &QPushButton::clicked, this, &CMainWindow::onAddTriangleClicked);
    connect(ui->btnClear,  &QPushButton::clicked, this, &CMainWindow::onClearClicked);
}

CMainWindow::~CMainWindow() {
    delete ui;
}

void CMainWindow::onAddTriangleClicked() {

    CProperties prop;
    prop.setCoefs(scene->getAbsSegment(), scene->getOrdSegment());
    prop.updateProperties(ui);

    CHexagon* hex = new CHexagon();
    hex->setProperties(prop);   
    scene->addFigure(hex);

    canvas->update();
}

void CMainWindow::onClearClicked() {

    scene->clearFigures();
    canvas->update();

}

