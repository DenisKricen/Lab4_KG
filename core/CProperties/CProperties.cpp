#include "CProperties.h"
#include <ui_CMainWindow.h>

CProperties::CProperties() {

}

void CProperties::updateProperties(Ui::CMainWindow* ui, const QColor& out, const QColor& fill) {

    outColor = out;
    fillColor = fill;
}

void CProperties::setCoefs(double abs, double ord) {
    absCoef=abs;
    ordCoef=ord;
}