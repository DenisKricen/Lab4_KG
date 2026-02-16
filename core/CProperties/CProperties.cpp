#include "CProperties.h"
#include "CMainWindow/CMainWindow.h"
#include <ui_CMainWindow.h>

QColor getColor(const QString& text) {

    QColor res=Qt::black;

    if(text=="Red")  res=Qt::red;
    if(text=="Green")res=Qt::green;
    if(text=="Blue") res=Qt::blue;

    return res;
}

CProperties::CProperties() {

}

void CProperties::updateProperties(Ui::CMainWindow* ui) {

    outColor=getColor(ui->cmbOutCol->currentText());
    fillColor=getColor(ui->cmbInCol->currentText());
    ordinate=ui->sbOrd->value(); 
    abscise =ui->sbAbs->value();    
    circumradius=ui->sbRadius->value();  
}

void CProperties::setCoefs(double abs, double ord) {
    absCoef=abs;
    ordCoef=ord;
}