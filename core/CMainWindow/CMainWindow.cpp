#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include <QColorDialog>
#include <QPushButton>
#include <QResizeEvent>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <iostream>
#include <cmath>
#include <fstream>
using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);



    // connect(ui->btnSetPoints, &QPushButton::clicked, this, &CMainWindow::onSetPointsClicked);

    
}

CMainWindow::~CMainWindow() {
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

