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
    bool eventFilter(QObject *, QEvent*);

public slots:
    void doFrame();


private:
    void createStarField();
    void createTieFighters();
    void startExplosion(int tie);
    void processExplosions();
    void drawExplosions();
    void initTie(int index);
    void processTies();
    void drawTies();
    void moveStarField();
    void drawStarField();
    void drawCrossHairs();
    void drawLaserBeams();
    void drawPoint(int x, int y, QColor color);
    void drawLine(int p1x, int p1y, int p2x, int p2y, QColor color);
    Ui::MainWindow *ui;
    POINT3D tie_vlist[NUM_TIE_VERTS];
    LINE3D tie_shape[NUM_TIE_EDGES];
    TIE ties[NUM_TIES];
    POINT3D stars[NUM_STARS];
    EXPL explosions[NUM_EXPLOSIONS];
    int player_z_vel = 4;
    float cross_x = 0;
    float cross_y = 0;
    float cross_x_screen;
    float cross_y_screen;
    int cannon_state;
    int cannon_count;
    float target_x_screen;
    float target_y_screen;
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
