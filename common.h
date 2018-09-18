#ifndef COMMON_H
#define COMMON_H

#include <QColor>

#define NUM_STARS 250
#define NEAR_Z 10
#define FAR_Z 2000
#define VIEW_DISTANCE 320
#define PLAYER_Z_VEL 8
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct POINT_TYP
{
    QColor color;
    float x;
    float y;
    float z;
} POINT3D, *POINT3D_PTR;

#endif // COMMON_H
