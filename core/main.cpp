#include <QApplication>
#include <QString>
#include "CMainWindow/CMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    CMainWindow w;
    w.show();

    return app.exec();
}