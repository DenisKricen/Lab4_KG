#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include "../CScene/CScene.h"     // Підключаємо нашу сцену
#include "../CFigure/CFigure.h"  // Підключаємо наш трикутник

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QWidget {
    Q_OBJECT // Обов'язково для роботи кнопок (slots)

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:
    // Слот, який виконається при натисканні кнопки
    void onAddTriangleClicked();
    void onDrawClicked();
    void onClearClicked();

private:
    CScene *scene;       // Вказівник на сцену
    QGraphicsView *view;  // Вказівник на камеру
    Ui::CMainWindow *ui;
};

#endif // MAINWINDOW_H