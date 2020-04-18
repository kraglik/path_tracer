#ifndef PATH_TRACER_TRACER_H
#define PATH_TRACER_TRACER_H

#include <tracer/camera.h>
#include <tracer/math.h>
#include <tracer/material.h>
#include <tracer/config.h>
#include <tracer/object.h>


typedef struct hit {
    vec3d position;
    vec3d normal;
    vec2d texture_coords;
    material* material;
} hit;

typedef struct tracer {
    color background;
    camera* camera;
    object** objects;
    size_t n_objects;
    tracer_config* config;
} tracer;


color trace_ray(tracer* t, ray r, size_t depth);

void trace_to_file(tracer* t, const char* path);

#endif