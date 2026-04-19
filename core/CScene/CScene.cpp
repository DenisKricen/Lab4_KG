#include "CScene.h"
#include <fstream>
#include <sstream>
#include <algorithm>



CScene::CScene(QObject* parent) : QObject(parent){

}


void CScene::setWidget(QWidget* widget){

    canvas = qobject_cast<CCanvas*>(widget);

}



void CScene::render(QPainter& painter) {

    

}

