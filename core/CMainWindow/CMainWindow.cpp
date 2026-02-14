#include "CMainWindow.h"
#include "ui_CMainWindow.h"

CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CMainWindow) {
    ui->setupUi(this);

    scene = new CScene(this);
    view = ui->graphicsView;
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);

    // connect(ui->pushButton, &QPushButton::clicked, this, &CMainWindow::onAddTriangleClicked);
}

CMainWindow::~CMainWindow() {
    delete ui; // Обов'язково чистимо пам'ять
}

// void CMainWindow::onAddTriangleClicked() {
//     // Створюємо новий трикутник і кидаємо на сцену
//     MyTriangle *triangle = new MyTriangle();
//     scene->addItem(triangle);
// }

void CMainWindow::onAddTriangleClicked() {
    // TODO: Реалізувати додавання фігури на сцену.
}

void CMainWindow::onDrawClicked() {
    // TODO: Реалізувати малювання.
}

void CMainWindow::onClearClicked() {
    // TODO: Реалізувати очищення сцени.
}