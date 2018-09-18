#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    createStarField();

    ui->setupUi(this);    
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doFrame()));
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::doFrame() {
    moveStarField();
    update();//will trigger call to paintEvent()
}


void MainWindow::paintEvent(QPaintEvent *e) {
    drawStarField();
}

void MainWindow::createStarField() {
    for (int index = 0; index < NUM_STARS; index++) {
        stars[index].x = -WINDOW_WIDTH/2 + rand()%WINDOW_WIDTH;
        stars[index].y = -WINDOW_HEIGHT/2 + rand()%WINDOW_HEIGHT;
        stars[index].z = NEAR_Z + rand()%(FAR_Z - NEAR_Z);
        stars[index].color = Qt::white;
    }
}

void MainWindow::moveStarField() {
    for (int index = 0; index < NUM_STARS; index++) {
        stars[index].z -= PLAYER_Z_VEL;
        if (stars[index].z <= NEAR_Z) {
            stars[index].z = FAR_Z;
        }
    }
}

void MainWindow::drawStarField() {
    for (int index = 0; index < NUM_STARS; index++) {
        float x_per = VIEW_DISTANCE * stars[index].x / stars[index].z;
        float y_per = VIEW_DISTANCE * stars[index].y / stars[index].z;

        int x_screen = WINDOW_WIDTH/2 + x_per;
        int y_screen = WINDOW_HEIGHT/2 + y_per;

        if ((x_screen >= WINDOW_WIDTH) || x_screen < 0 || (y_screen >= WINDOW_HEIGHT) || y_screen < 0) {
            continue;
        } else {
            drawPoint(x_screen, y_screen, stars[index].color);
        }
    }
    update();
}

void MainWindow::drawPoint(int x, int y, QColor color) {
    QPainter painter(this);
    QPen pointPen(color);
    painter.setPen(pointPen);
    QPoint p;
    p.setX(x);
    p.setY(y);
    painter.drawPoint(p);
}

void MainWindow::createTieFighters() {
    // create the tie fighter model
    // the vertex list for the tie fighter
    POINT3D temp_tie_vlist[NUM_TIE_VERTS] =
    {   { QColor::white, -40, 40, 0},   // p0
        { QColor::white, -40, 0, 0},    // p1
        { QColor::white, -40, -40, 0},  // p2
        { QColor::white, -10, 0, 0},    // p3
        { QColor::white, 0, 20, 0},     // p4
        { QColor::white, 10, 0, 0},     // p5
        { QColor::white, 0, -20, 0},    // p6
        { QColor::white, 40, -40, 0},   // p7
        { QColor::white, 40, 0, 0},     // p8
        { QColor::white, 40, -40, 0}};  // p9

    //TODO...
}

void MainWindow::initTie(int index) {

}
