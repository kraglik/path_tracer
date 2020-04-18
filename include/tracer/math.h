#ifndef PATH_TRACER_MATH_H
#define PATH_TRACER_MATH_H

#define EPSILON 1e-8

typedef struct vec3d {
    double x, y, z;
} vec3d;

typedef struct vec2d {
    double x, y;
} vec2d;

typedef struct ray {
    vec3d origin, direction;
} ray;

typedef vec3d color;
typedef double refract_index;

double dot(vec3d a, vec3d b);
vec3d cross(vec3d a, vec3d b);
double mag(vec3d a);
double len(vec3d a);
vec3d norm(vec3d a);

vec3d build_vec(double x, double y, double z);

vec3d from_val(double val);

vec3d add_vv(vec3d a, vec3d b);
vec3d sub_vv(vec3d a, vec3d b);
vec3d mul_vv(vec3d a, vec3d b);
vec3d div_vv(vec3d a, vec3d b);

vec3d add_vd(vec3d a, double x);
vec3d sub_vd(vec3d a, double x);
vec3d mul_vd(vec3d a, double x);
vec3d div_vd(vec3d a, double x);

vec3d add_dv(double x, vec3d a);
vec3d sub_dv(double x, vec3d a);
vec3d mul_dv(double x, vec3d a);
vec3d div_dv(double x, vec3d a);

vec3d clip(double min, double max, vec3d a);

vec3d reflect(vec3d dir, vec3d norm);
vec3d refract(vec3d dir, vec3d norm, refract_index ior);

ray shift(ray r, double x);

vec3d random_hemisphere_vec(vec3d hemisphere_up);


#endif