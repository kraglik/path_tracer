#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include <stdlib.h>
#include <tracer/math.h>

typedef struct screen {

    size_t width;
    size_t height;

    double scale;
    double distance;

} screen;

typedef struct camera {

    vec3d position;
    vec3d direction;
    vec3d up;

    double focus;

    screen screen;

} camera;

vec3d u(camera* c);
vec3d v(camera* c);
vec3d w(camera* c);

ray spawn_random_ray(camera* c, size_t x, size_t y);

#endif