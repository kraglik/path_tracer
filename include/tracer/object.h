#ifndef PATH_TRACER_OBJECT_H
#define PATH_TRACER_OBJECT_H

#include <stdbool.h>

#include <tracer/math.h>
#include <tracer/material.h>

struct hit;

typedef struct object {
    void* data;
    material* material;
    vec3d (*get_normal_at)(void* data, vec3d position);
    bool (*intersect)(struct object* o, ray r, struct hit* h);
} object;

object* build_sphere(vec3d center, double radius, material* material);

object* build_plane(vec3d position, vec3d normal, material* material);

#endif
