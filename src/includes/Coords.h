#ifndef COORDS_H
#define COORDS_H

/**
 * Structure contenant deux float : x et y
 */
struct Coord2d {
    float x, y;
};

typedef struct Coord2d Coord2d;

/**
 * Structure contenant trois GLfloat : x, y et z
 */
struct Coord3d {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

typedef struct Coord3d Coord3d;

#endif
