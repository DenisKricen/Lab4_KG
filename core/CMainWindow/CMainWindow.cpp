#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include "Figures/CTriangle/CTriangle.h"
#include "Figures/CHexagon/CHexagon.h"
#include <QColorDialog>
#include <QPushButton>
#include <QResizeEvent>
#include <iostream>
#include <cmath>
using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);

    scene->loadFigures("figures.txt");

    lineColor = Qt::red;
    fillColor = Qt::red;

    connect(ui->btnCreate, &QPushButton::clicked, this, &CMainWindow::onCreateClicked);
    connect(ui->btnClear,  &QPushButton::clicked, this, &CMainWindow::onClearClicked);
    connect(ui->btnOutCol, &QPushButton::clicked, this, &CMainWindow::onChooseOutColor);
    connect(ui->btnInCol,  &QPushButton::clicked, this, &CMainWindow::onChooseInColor);
}

CMainWindow::~CMainWindow() {
    scene->saveFigures("figures.txt");
    delete ui;
}

void CMainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int currentWidth = event->size().width();

    int targetHeight = currentWidth*3/4; 

    if (this->height() != targetHeight) {
        this->resize(currentWidth, targetHeight);
    }
}

void CMainWindow::onCreateClicked() {

    CProperties prop;
    prop.setCoefs(scene->getAbsSegment(), scene->getOrdSegment());
    prop.updateProperties(ui, lineColor, fillColor);

    CHexagon* hex = new CHexagon();
    hex->setProperties(prop);   
    scene->addFigure(hex);

    canvas->update();
}

void CMainWindow::onClearClicked() {

    scene->clearFigures();
    canvas->update();

}

void CMainWindow::onChooseOutColor() {
    QColor color = QColorDialog::getColor(lineColor, this, "Choose outline color");
    if (!color.isValid()) {
        return;
    }
    lineColor = color;
}

void CMainWindow::onChooseInColor() {
    QColor color = QColorDialog::getColor(fillColor, this, "Choose inner color");
    if (!color.isValid()) {
        return;
    }
    fillColor = color;
}

