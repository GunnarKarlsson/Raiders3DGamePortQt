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

private:
    void initTie(int index);
    void processTies();
    void drawTies();
    void moveStarField();
    void drawStarField();
    void drawPoint(int x, int y, QColor color);
    void drawLine(int p1x, int p1y, int p2x, int p2y, QColor color);
    Ui::MainWindow *ui;
    POINT3D tie_vlist[NUM_TIE_VERTS];
    LINE3D tie_shape[NUM_TIE_EDGES];
    TIE ties[NUM_TIES];
    POINT3D stars[NUM_STARS];
    int player_z_vel = 4;
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
