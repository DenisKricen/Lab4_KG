#ifndef CPOINTDIALOG_H
#define CPOINTDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QPointF>

class CPointDialog : public QDialog {
    Q_OBJECT

    QDoubleSpinBox* sbX;
    QDoubleSpinBox* sbY;
    bool deleteRequested;

public:
    // mode: false = add, true = edit (shows Delete button)
    CPointDialog(QWidget* parent = nullptr, bool editMode = false, QPointF initial = QPointF(0, 0));

    QPointF getPoint() const;
    bool isDeleteRequested() const;
};

#endif // CPOINTDIALOG_H
