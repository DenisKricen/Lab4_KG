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

    // Load saved curve from file
    scene->loadFigures("figures.txt");

    // Restore UI state from loaded curve
    CBeziersCurve* loadedCurve = scene->getCurve();
    if (loadedCurve) {
        lineColor = loadedCurve->getRectColor();
        fillColor = loadedCurve->getCurveColor();
        matrixMode = loadedCurve->isMatrixMode();
    } else {
        lineColor = Qt::red;
        fillColor = Qt::red;
        matrixMode = false;
    }

    connect(ui->btnCreate, &QPushButton::clicked, this, &CMainWindow::onAddPointClicked);
    connect(ui->btnClear,  &QPushButton::clicked, this, &CMainWindow::onClearClicked);
    connect(ui->btnOutCol, &QPushButton::clicked, this, &CMainWindow::onChooseOutColor);
    connect(ui->btnInCol,  &QPushButton::clicked, this, &CMainWindow::onChooseInColor);
    connect(ui->pointList, &QListWidget::itemDoubleClicked, this, &CMainWindow::onPointItemClicked);
    connect(ui->pointList->model(), &QAbstractItemModel::rowsMoved, this, &CMainWindow::onPointsMoved);
    connect(ui->toMatrixMode, &QPushButton::clicked, this, &CMainWindow::onMatrixMode);
    connect(ui->toParamMode, &QPushButton::clicked, this, &CMainWindow::onParamMode);

    if (loadedCurve) {
        ui->valueT->setValue(loadedCurve->getPace());
        ui->minValueT->setValue(loadedCurve->getTMin());
        ui->maxValueT->setValue(loadedCurve->getTMax());
        rebuildPointList();
    } else {
        ui->valueT->setValue(0.05);
        ui->minValueT->setValue(0.0);
        ui->maxValueT->setValue(1.0);
    }

    updateLog();

    connect(ui->valueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setPace(val);
            canvas->update();
        }
    });
    connect(ui->minValueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        ui->maxValueT->setMinimum(val + ui->maxValueT->singleStep());
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setTMin(val);
            canvas->update();
        }
    });
    connect(ui->maxValueT, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        ui->minValueT->setMaximum(val - ui->minValueT->singleStep());
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->setTMax(val);
            canvas->update();
        }
    });
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

void CMainWindow::onAddPointClicked() {
    CPointDialog dlg(this, false);
    if (dlg.exec() == QDialog::Accepted) {
        CBeziersCurve* curve = scene->getCurve();
        if (curve) {
            curve->addPoint(dlg.getPoint());
            rebuildPointList();
            updateLog();
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
    updateLog();
    canvas->update();
}

void CMainWindow::onChooseOutColor() {
    QColor color = QColorDialog::getColor(lineColor, this, "Choose rectangle color");
    if (!color.isValid()) return;
    lineColor = color;
    CBeziersCurve* curve = scene->getCurve();
    if (curve) {
        curve->setRectColor(color);
        canvas->update();
    }
}

void CMainWindow::onChooseInColor() {
    QColor color = QColorDialog::getColor(fillColor, this, "Choose curve color");
    if (!color.isValid()) return;
    fillColor = color;
    CBeziersCurve* curve = scene->getCurve();
    if (curve) {
        curve->setCurveColor(color);
        canvas->update();
    }
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
        updateLog();
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

    const auto& oldPts = curve->getPoints();
    QVector<QPointF> newOrder;

    for (int i = 0; i < ui->pointList->count(); ++i) {
        QString text = ui->pointList->item(i)->text();
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

void CMainWindow::onMatrixMode() {
    CBeziersCurve* curve = scene->getCurve();
    if (curve) {
        curve->setDrawMethod(&CBeziersCurve::drawMatrix);
        matrixMode = true;
        updateLog();
        canvas->update();
    }
}

void CMainWindow::onParamMode() {
    CBeziersCurve* curve = scene->getCurve();
    if (curve) {
        curve->setDrawMethod(&CBeziersCurve::drawParam);
        matrixMode = false;
        updateLog();
        canvas->update();
    }
}

void CMainWindow::updateLog() {
    ui->logText->clear();
    CBeziersCurve* curve = scene->getCurve();
    if (!curve) return;

    if (matrixMode) {
        ui->logText->appendPlainText("=== MATRIX MODE ===");
        ui->logText->appendPlainText(curve->getMatrixInfo());
    } else {
        ui->logText->appendPlainText("=== PARAMETERS MODE ===");
    }
}
