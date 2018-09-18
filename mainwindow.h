#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QColor>

#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void doFrame();
    void createStarField();
    void createTieFighters();
    void initTie(int index);

private:
    void moveStarField();
    void drawStarField();
    void drawPoint(int x, int y, QColor color);
    Ui::MainWindow *ui;
    POINT3D stars[NUM_STARS];
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
