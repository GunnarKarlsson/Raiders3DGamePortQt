#ifndef COMMON_H
#define COMMON_H

#include <QColor>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define NUM_STARS 250
#define NUM_TIES 10

#define NEAR_Z 10
#define FAR_Z 2000
#define VIEW_DISTANCE 320

#define CROSS_VEL 8
#define PLAYER_Z_VEL 8

#define NUM_TIE_VERTS  10
#define NUM_TIE_EDGES 8

#define NUM_EXPLOSIONS (NUM_TIES)

#define HIT_AREA 10

#define GAME_RUNNING 1
#define GAME_OVER 0

typedef struct POINT_TYP
{
    QColor color;
    float x;
    float y;
    float z;
} POINT3D, *POINT3D_PTR;

typedef struct LINE_TYP
{
    QColor color;
    int v1;
    int v2;
} LINE3D, *LINE3D_PTR;

typedef struct TIE_TYP
{
    int state;
    float x;
    float y;
    float z;
    float xv;
    float yv;
    float zv;
} TIE, *TIE_PTR;


typedef struct VEC3D_TYP
{
    float x;
    float y;
    float z;
} VEC3D, *VEC3D_PTR;

typedef struct EXPL_TYP
{
    int state;
    int counter;
    QColor color;
    POINT3D p1[NUM_TIE_EDGES];
    POINT3D p2[NUM_TIE_EDGES];

    VEC3D vel[NUM_TIE_EDGES];
} EXPL, *EXPL_PTR;



#endif // COMMON_H
