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
    installEventFilter(this);

    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    createStarField();
    createTieFighters();

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
    processTies();
    processExplosions();
    update();//will trigger call to paintEvent()
}


void MainWindow::paintEvent(QPaintEvent *e) {
    drawStarField();
    drawTies();
    drawExplosions();
    drawCrossHairs();
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
        stars[index].z -= player_z_vel;
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

void MainWindow::drawLine(int p1x, int p1y, int p2x, int p2y, QColor color) {
    QPainter painter(this);
    QPen linePen(color);
    painter.setPen(linePen);
    QPoint p1;
    p1.setX(p1x);
    p1.setY(p1y);
    QPoint p2;
    p2.setX(p2x);
    p2.setY(p2y);
    painter.drawLine(p1, p2);
}

void MainWindow::createTieFighters() {
    // create the tie fighter model
    // the vertex list for the tie fighter
    POINT3D temp_tie_vlist[NUM_TIE_VERTS] =
    {   { Qt::white, -40, 40, 0},   // p0
        { Qt::white, -40, 0, 0},    // p1
        { Qt::white, -40, -40, 0},  // p2
        { Qt::white, -10, 0, 0},    // p3
        { Qt::white, 0, 20, 0},     // p4
        { Qt::white, 10, 0, 0},     // p5
        { Qt::white, 0, -20, 0},    // p6
        { Qt::white, 40, 40, 0},   // p7
        { Qt::white, 40, 0, 0},     // p8
        { Qt::white, 40, -40, 0}};  // p9

    for (int index = 0; index < NUM_TIE_VERTS; index++) {
        tie_vlist[index] = temp_tie_vlist[index];
    }

    LINE3D temp_tie_shape[NUM_TIE_EDGES] =
    {{Qt::green, 0, 2},
     {Qt::green, 1, 3},
     {Qt::green, 3, 4},
     {Qt::green, 4, 5},
     {Qt::green, 5, 6},
     {Qt::green, 6, 3},
     {Qt::green, 5, 8},
     {Qt::green, 7, 9}};

    for (int index = 0; index < NUM_TIE_EDGES; index++) {
        tie_shape[index] = temp_tie_shape[index];
    }

    for (int index = 0; index < NUM_TIES; index++) {
        initTie(index);
    }
}

void MainWindow::initTie(int index) {
    ties[index].x = -WINDOW_WIDTH + rand()%(2*WINDOW_WIDTH);
    ties[index].y = -WINDOW_HEIGHT + rand()%(2*WINDOW_HEIGHT);
    ties[index].z = 4*FAR_Z;

    ties[index].xv = -4+rand()%8;
    ties[index].yv = -4+rand()%8;
    ties[index].zv = -4-rand()%64;

    ties[index].state = 1;
}

void MainWindow::processTies() {
    for (int index = 0; index < NUM_TIES; index++) {
        if (ties[index].state == 0) {
            continue;
        }
        ties[index].z += ties[index].zv;
        ties[index].x += ties[index].xv;
        ties[index].y += ties[index].yv;

        if (ties[index].z <= NEAR_Z) {
            initTie(index);
        }
    }
}

void MainWindow::drawTies() {
    for (int index = 0; index < NUM_TIES; index++) {
        if (ties[index].state == 0) {
            continue;
        }
        for (int edge = 0; edge < NUM_TIE_EDGES; edge++) {
            POINT3D p1_per, p2_per;
            p1_per.x = VIEW_DISTANCE * (ties[index].x + tie_vlist[tie_shape[edge].v1].x) / (tie_vlist[tie_shape[edge].v1].z + ties[index].z);
            p1_per.y = VIEW_DISTANCE * (ties[index].y + tie_vlist[tie_shape[edge].v1].y) / (tie_vlist[tie_shape[edge].v1].z + ties[index].z);
            p2_per.x = VIEW_DISTANCE * (ties[index].x + tie_vlist[tie_shape[edge].v2].x) / (tie_vlist[tie_shape[edge].v2].z + ties[index].z);
            p2_per.y = VIEW_DISTANCE * (ties[index].y + tie_vlist[tie_shape[edge].v2].y) / (tie_vlist[tie_shape[edge].v2].z + ties[index].z);

            int p1_screen_x = WINDOW_WIDTH/2 + p1_per.x;
            int p1_screen_y = WINDOW_HEIGHT/2 + p1_per.y;
            int p2_screen_x = WINDOW_WIDTH/2 + p2_per.x;
            int p2_screen_y = WINDOW_HEIGHT/2 + p2_per.y;

            drawLine(p1_screen_x, p1_screen_y, p2_screen_x, p2_screen_y, Qt::green);
        }
    }
}

void MainWindow::startExplosion(int tie) {
    for (int index = 0; index < NUM_EXPLOSIONS; index++) {
        if (explosions[index].state == 0) {
            explosions[index].state = 1;
            explosions[index].counter = 0;
            explosions[index].color = Qt::green;
            for (int edge = 0; edge < NUM_TIE_EDGES; edge++) {
                explosions[index].p1[edge].x = ties[tie].x + tie_vlist[tie_shape[edge].v1].x;
                explosions[index].p1[edge].y = ties[tie].y + tie_vlist[tie_shape[edge].v1].y;
                explosions[index].p1[edge].z = ties[tie].z + tie_vlist[tie_shape[edge].v1].z;

                explosions[index].p2[edge].x = ties[tie].x + tie_vlist[tie_shape[edge].v2].x;
                explosions[index].p2[edge].y = ties[tie].y + tie_vlist[tie_shape[edge].v2].y;
                explosions[index].p2[edge].z = ties[tie].z + tie_vlist[tie_shape[edge].v2].z;

                explosions[index].vel[edge].x = ties[tie].xv - 8+rand()%16;
                explosions[index].vel[edge].y = ties[tie].yv - 8+rand()%16;
                explosions[index].vel[edge].z = -3 + rand()%4;
            }
        }
    }
}

void MainWindow::processExplosions() {
    for (int index = 0; index < NUM_EXPLOSIONS; index++) {
        if (explosions[index].state == 0) {
            continue;
        }
        for (int edge = 0; edge < NUM_TIE_EDGES; edge++) {
            explosions[index].p1[edge].x += explosions[index].vel[edge].x;
            explosions[index].p1[edge].y += explosions[index].vel[edge].y;
            explosions[index].p1[edge].z += explosions[index].vel[edge].z;

            explosions[index].p2[edge].x += explosions[index].vel[edge].x;
            explosions[index].p2[edge].y += explosions[index].vel[edge].y;
            explosions[index].p2[edge].z += explosions[index].vel[edge].z;
        }

        if (++explosions[index].counter > 100) {
            explosions[index].state = explosions[index].counter = 0;
        }
    }
}

void MainWindow::drawExplosions() {
    for (int index = 0; index < NUM_EXPLOSIONS; index++) {
        if (explosions[index].state == 0) {
            continue;
        }

        for (int edge = 0; edge < NUM_TIE_EDGES; edge++) {
            POINT3D p1_per, p2_per;

            if (explosions[index].p1[edge].z < NEAR_Z && explosions[index].p2[edge].z < NEAR_Z) {
                continue;
            }

            p1_per.x = VIEW_DISTANCE * explosions[index].p1[edge].x / explosions[index].p1[edge].z;
            p1_per.y = VIEW_DISTANCE * explosions[index].p1[edge].y / explosions[index].p1[edge].z;
            p2_per.x = VIEW_DISTANCE * explosions[index].p2[edge].x / explosions[index].p2[edge].z;
            p2_per.y = VIEW_DISTANCE * explosions[index].p2[edge].y / explosions[index].p2[edge].z;

            int p1_screen_x = WINDOW_WIDTH/2 + p1_per.x;
            int p1_screen_y = WINDOW_HEIGHT/2 + p1_per.y;
            int p2_screen_x = WINDOW_WIDTH/2 + p2_per.x;
            int p2_Screen_y = WINDOW_HEIGHT/2 + p2_per.y;

            drawLine(p1_screen_x, p1_screen_y, p2_screen_x, p2_Screen_y, Qt::green);
        }
    }
}

bool MainWindow::eventFilter( QObject* object, QEvent* event) {
    switch(event->type()) {
    case QEvent::KeyPress:{
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Space) {
            for (int index = 0; index < NUM_TIES; index++) {
                startExplosion(index);
            }
        }
        if (keyEvent->key() == Qt::Key_Right) {
            cross_x += CROSS_VEL;
            if (cross_x > WINDOW_WIDTH/2) {
                cross_x = -WINDOW_WIDTH/2;
            }
        } else if (keyEvent->key() == Qt::Key_Left) {
            cross_x -= CROSS_VEL;
            if (cross_x < -WINDOW_WIDTH/2) {
                cross_x = WINDOW_WIDTH/2;
            }
        }
        if (keyEvent->key() == Qt::Key_Down) {
            cross_y -= CROSS_VEL;
            if (cross_y < -WINDOW_HEIGHT/2) {
                cross_y = WINDOW_HEIGHT/2;
            }
        } else if (keyEvent->key() == Qt::Key_Up) {
            cross_y += CROSS_VEL;
            if (cross_y > WINDOW_HEIGHT/2) {
                cross_y = -WINDOW_HEIGHT/2;
            }
        } else if (keyEvent->key() == Qt::Key_W) {
            player_z_vel++;
        } else if (keyEvent->key() == Qt::Key_S) {
            player_z_vel--;
            if (player_z_vel < 0) {
                player_z_vel = 0;
            }
        }
    }
    }
}

void MainWindow::drawCrossHairs() {
    int cross_x_screen = WINDOW_WIDTH/2 + cross_x;
    int cross_y_screen = WINDOW_HEIGHT/2 - cross_y;
    drawLine(cross_x_screen - 16,
             cross_y_screen,
             cross_x_screen + 16,
             cross_y_screen,
             Qt::red);
    drawLine(cross_x_screen,
             cross_y_screen - 16,
             cross_x_screen,
             cross_y_screen + 16,
             Qt::red);
    drawLine(cross_x_screen - 16,
             cross_y_screen - 4,
             cross_x_screen - 16,
             cross_y_screen + 4,
             Qt::red);
    drawLine(cross_x_screen + 16,
             cross_y_screen - 4,
             cross_x_screen + 16,
             cross_y_screen + 4,
             Qt::red);

}
