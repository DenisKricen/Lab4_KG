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
#include <QPoint>
#include <QPointF>
#include <iostream>
#include <cmath>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "CImageTransfer/CImageTransfer.h"
#include "CMouseObserver/CMouseObserver.h"
#include "COverlayImage/COverlayImage.h"
using std::cout, std::endl;

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    canvas = qobject_cast<CCanvas*>(ui->canvas);
    canvas->setMouseTracking(true);
    scene = new CScene(this);
    
    canvas->setScene(scene);
    scene->setWidget(canvas);

    // Enabling mouse observer
    mouseObserver = new CMouseObserver(this);
    canvas->installEventFilter(mouseObserver);

    pixelViewer = new CPixelViewer();

    // Gather data about hovered pixel
    connect(mouseObserver, &CMouseObserver::mouseHovered, this, [this](QPoint screenPos) {
        // Change data only if there is no selected pixel
        if (pixelViewer->isLocked()) {
            return; 
        }

        if(!scene->getMainImage()) {
            ui->pixelInfo->setText(
                "NO IMAGE PROVIDED."
            );
            return;
        }

        double scale = canvas->getScaleFactor();
        QPointF offset = canvas->getOffset();
        
        pixelViewer->updateHoverData(screenPos, scale, offset, scene->getMainImage());
        
        ui->pixelInfo->setText(
            pixelViewer->getCoordinatesText() + "\n" +
            pixelViewer->getStatusRGB() + "\n" +
            pixelViewer->getStatusCMYK() + "\n" +
            pixelViewer->getStatusHSB()
        );
        
        QPalette pal = ui->currentPixelColor->palette();
        pal.setColor(QPalette::Window, pixelViewer->getCurrentColor());
        ui->currentPixelColor->setPalette(pal);
        ui->currentPixelColor->setAutoFillBackground(true);
    });

    // Select pixel
    connect(mouseObserver, &CMouseObserver::pixelClicked, this, [this](QPoint screenPos) {
        double scale = canvas->getScaleFactor();
        QPointF offset = canvas->getOffset();
        
        QPoint realPos = pixelViewer->mapToImage(screenPos, scale, offset);
        
        pixelViewer->lockPixel(realPos);                  
        scene->getOverlayImage()->setLockedPixel(realPos);   
        canvas->update();                                 
    });

    // Select area
    connect(mouseObserver, &CMouseObserver::areaSelecting, this, [this](QRect screenArea) {
        double scale = canvas->getScaleFactor();
        QPointF offset = canvas->getOffset();
        
        QPoint topLeft = pixelViewer->mapToImage(screenArea.topLeft(), scale, offset);
        QPoint bottomRight = pixelViewer->mapToImage(screenArea.bottomRight(), scale, offset);
        QRect realArea = QRect(topLeft, bottomRight).normalized();
        
        pixelViewer->lockArea(realArea);                  
        scene->getOverlayImage()->setSelectionArea(realArea); 
        canvas->update();
    });

    // Clear locks
    connect(mouseObserver, &CMouseObserver::selectionCleared, this, [this]() {
        pixelViewer->clearLocks();
        scene->getOverlayImage()->clear();
        canvas->update();
    });

    // Slots connections
    connect(ui->btnImport, &QPushButton::clicked, this, &CMainWindow::onImportClicked);
    connect(ui->btnExport, &QPushButton::clicked, this, &CMainWindow::onExportClicked);
    
}

CMainWindow::~CMainWindow() {
    delete ui;
    delete scene;
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

void CMainWindow::onImportClicked() {
    // Open a native file dialog to select an image for import
    // "tr" is used for potential translation, but the strings remain in English
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Import Image"), 
        DEFAULT_PATH, 
        tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if (fileName.isEmpty()) {
        return;
    }

    CImage* newImage = CImageTransfer::importImage(fileName);
        
    if (!newImage) {
        // Display an error message if the file couldn't be processed
        QMessageBox::critical(this, tr("Import Error"), tr("Failed to open the image file."));
    }

    // Update the scene with the newly loaded image
    scene->setMainImage(newImage);
    
    // Notify the canvas that it needs to redraw with the new image
    ui->canvas->update();
    
    qDebug() << "Successfully loaded image from dialog.";
}

void CMainWindow::onExportClicked() {
    // Check if there is an image to export before opening the dialog
    CImage* currentImage = scene->getMainImage();
    
    if (!currentImage || currentImage->isNull()) {
        QMessageBox::warning(this, tr("Export Warning"), tr("No image found in the scene to export."));
        return;
    }

    // Open a native file dialog to select the destination path and filename
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Export Image"), 
        DEFAULT_PATH, 
        tr("PNG Image (*.png);;JPEG Image (*.jpg);;BMP Image (*.bmp)"));

    if (!fileName.isEmpty()) {
        // Execute the export operation via the transfer service
        bool success = CImageTransfer::exportImage(fileName, currentImage);
        
        if (success) {
            QMessageBox::information(this, tr("Export Success"), tr("Image has been successfully saved."));
        } else {
            QMessageBox::critical(this, tr("Export Error"), tr("Could not save the image to the specified path."));
        }
    }
}