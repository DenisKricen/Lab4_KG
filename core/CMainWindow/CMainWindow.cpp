#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include "Figures/CTriangle/CTriangle.h"
#include "Figures/CHexagon/CHexagon.h"
#include "CPointDialog/CPointDialog.h"
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

    lineColor = Qt::red;
    fillColor = Qt::red;

    connect(ui->btnCreate, &QPushButton::clicked, this, &CMainWindow::onAddPointClicked);
    connect(ui->btnClear,  &QPushButton::clicked, this, &CMainWindow::onClearClicked);
    connect(ui->btnOutCol, &QPushButton::clicked, this, &CMainWindow::onChooseOutColor);
    connect(ui->btnInCol,  &QPushButton::clicked, this, &CMainWindow::onChooseInColor);
    connect(ui->pointList, &QListWidget::itemDoubleClicked, this, &CMainWindow::onPointItemClicked);
    connect(ui->pointList->model(), &QAbstractItemModel::rowsMoved, this, &CMainWindow::onPointsMoved);

    // Set initial spinbox values and connect t-parameter controls
    ui->valueT->setValue(0.05);
    ui->minValueT->setValue(0.0);
    ui->maxValueT->setValue(1.0);

    connect(ui->valueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setPace(val);
            canvas->update();
        }
    });
    connect(ui->minValueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setTMin(val);
            canvas->update();
        }
    });
    connect(ui->maxValueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setTMax(val);
            canvas->update();
        }
    });
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

void CMainWindow::onAddPointClicked() {
    CPointDialog dlg(this, false);
    if (dlg.exec() == QDialog::Accepted) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->addPoint(dlg.getPoint());
            rebuildPointList();
            canvas->update();
        }
    }
}

void CMainWindow::onClearClicked() {
    CBeziersCurve* curve = scene->getCurve();
    if (curve) {
        curve->clearPoints();
    }
    rebuildPointList();
    canvas->update();
}

void CMainWindow::onChooseOutColor() {
    QColor color = QColorDialog::getColor(lineColor, this, "Choose rectangle color");
    if (!color.isValid()) return;
    lineColor = color;
}

void CMainWindow::onChooseInColor() {
    QColor color = QColorDialog::getColor(fillColor, this, "Choose curve color");
    if (!color.isValid()) return;
    fillColor = color;
}

void CMainWindow::onPointItemClicked(QListWidgetItem* item) {
    int index = ui->pointList->row(item);
    CBeziersCurve* curve = scene->getCurve();
    if (!curve) return;

    const auto& pts = curve->getPoints();
    if (index < 0 || index >= pts.size()) return;

    CPointDialog dlg(this, true, pts[index]);
    if (dlg.exec() == QDialog::Accepted) {
        if (dlg.isDeleteRequested()) {
            curve->removePoint(index);
        } else {
            curve->editPoint(index, dlg.getPoint());
        }
        rebuildPointList();
        canvas->update();
    }
}

void CMainWindow::rebuildPointList() {
    ui->pointList->clear();

    CBeziersCurve* curve = scene->getCurve();
    if (!curve) return;

    const auto& pts = curve->getPoints();
    for (int i = 0; i < pts.size(); ++i) {
        ui->pointList->addItem(
            QString("X: %1 , Y: %2").arg(pts[i].x(), 0, 'f', 2).arg(pts[i].y(), 0, 'f', 2)
        );
    }
}

void CMainWindow::onPointsMoved() {
    CBeziersCurve* curve = scene->getCurve();
    if (!curve) return;

    // Rebuild curve points order from the current list order
    const auto& oldPts = curve->getPoints();
    QVector<QPointF> newOrder;

    for (int i = 0; i < ui->pointList->count(); ++i) {
        QString text = ui->pointList->item(i)->text();
        // Parse "X: ..., Y: ..." back to find the original index
        // Match by iterating old points to find which one corresponds
        for (int j = 0; j < oldPts.size(); ++j) {
            QString expected = QString("X: %1 , Y: %2").arg(oldPts[j].x(), 0, 'f', 2).arg(oldPts[j].y(), 0, 'f', 2);
            if (text == expected) {
                newOrder.append(oldPts[j]);
                break;
            }
        }
    }

    curve->clearPoints();
    for (const auto& pt : newOrder) {
        curve->addPoint(pt);
    }

    canvas->update();
}

