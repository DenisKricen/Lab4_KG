#include "CPointDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

CPointDialog::CPointDialog(QWidget* parent, bool editMode, QPointF initial)
    : QDialog(parent), deleteRequested(false) {

    setWindowTitle(editMode ? "Edit Point" : "Add Point");
    setModal(true);

    auto* layout = new QVBoxLayout(this);

    // X coordinate
    auto* rowX = new QHBoxLayout();
    rowX->addWidget(new QLabel("X:"));
    sbX = new QDoubleSpinBox();
    sbX->setRange(-10.0, 10.0);
    sbX->setDecimals(1);
    sbX->setValue(initial.x());
    rowX->addWidget(sbX);
    layout->addLayout(rowX);

    // Y coordinate
    auto* rowY = new QHBoxLayout();
    rowY->addWidget(new QLabel("Y:"));
    sbY = new QDoubleSpinBox();
    sbY->setRange(-10.0, 10.0);
    sbY->setDecimals(1);
    sbY->setValue(initial.y());
    rowY->addWidget(sbY);
    layout->addLayout(rowY);

    // Buttons
    auto* btnRow = new QHBoxLayout();

    auto* btnOk = new QPushButton("OK");
    connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
    btnRow->addWidget(btnOk);

    auto* btnCancel = new QPushButton("Cancel");
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    btnRow->addWidget(btnCancel);

    if (editMode) {
        auto* btnDelete = new QPushButton("Delete");
        connect(btnDelete, &QPushButton::clicked, this, [this]() {
            deleteRequested = true;
            accept();
        });
        btnRow->addWidget(btnDelete);
    }

    layout->addLayout(btnRow);
    setLayout(layout);
}

QPointF CPointDialog::getPoint() const {
    return QPointF(sbX->value(), sbY->value());
}

bool CPointDialog::isDeleteRequested() const {
    return deleteRequested;
}
