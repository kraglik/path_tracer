#include <tracer/math.h>

#include <math.h>
#include <stdlib.h>

#define CLIP(min, max, val) (val) > (max) ? (max) : (val) < (min) ? (min) : (val)

double dot(vec3d a, vec3d b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3d cross(vec3d a, vec3d b) {
    vec3d vec = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
    return vec;
}

double mag(vec3d a) {
    return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

double len(vec3d a) {
    return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

vec3d norm(vec3d a) {
    double len = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

    vec3d vec;

    if (len == 0.0) {
        vec.x = vec.y = vec.z = 0;
    }
    else {
        vec.x = a.x / len;
        vec.y = a.y / len;
        vec.z = a.z / len;
    }

    return vec;
}

vec3d from_val(double v) {
    vec3d vec = {
        .x = v,
        .y = v,
        .z = v
    };

    return vec;
}

vec3d clip(double min, double max, vec3d v) {
    vec3d vec = {
        .x = CLIP(min, max, v.x),
        .y = CLIP(min, max, v.y),
        .z = CLIP(min, max, v.z)
    };

    return vec;
}

vec3d reflect(vec3d dir, vec3d normal) {
    return norm(
        sub_vv(
            dir,
            mul_dv(
                2 * dot(dir, normal),
                normal
            )
        )
    );
}

vec3d refract(vec3d dir, vec3d normal, refract_index ior) {
    double nv = dot(dir, normal);
    refract_index a = 1 / ior;

    if (nv > 0) {
        return refract(
            dir,
            mul_vd(normal, -1),
            a
        );
    }

    double d = 1 - (a * a) * (1 - nv * nv);

    vec3d refracted;

    if (d < 0) {
        refracted.x = 0;
        refracted.y = 0;
        refracted.z = 0;
    }
    else {
        refracted = sub_vv(
            mul_vd(dir, a),
            mul_vd(normal, nv * a + sqrt(d))
        );
    }

    return refracted;
}


vec3d add_vv(vec3d a, vec3d b) {
    vec3d result = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };

    return result;
}

vec3d sub_vv(vec3d a, vec3d b) {
    vec3d result = {
            .x = a.x - b.x,
            .y = a.y - b.y,
            .z = a.z - b.z
    };

    return result;
}

vec3d mul_vv(vec3d a, vec3d b) {
    vec3d result = {
            .x = a.x * b.x,
            .y = a.y * b.y,
            .z = a.z * b.z
    };

    return result;
}

vec3d div_vv(vec3d a, vec3d b) {
    vec3d result = {
            .x = a.x / b.x,
            .y = a.y / b.y,
            .z = a.z / b.z
    };

    return result;
}


vec3d add_vd(vec3d a, double x) {
    vec3d result = {
            .x = a.x + x,
            .y = a.y + x,
            .z = a.z + x
    };

    return result;
}

vec3d sub_vd(vec3d a, double x) {
    vec3d result = {
            .x = a.x - x,
            .y = a.y - x,
            .z = a.z - x
    };

    return result;
}

vec3d mul_vd(vec3d a, double x) {
    vec3d result = {
            .x = a.x * x,
            .y = a.y * x,
            .z = a.z * x
    };

    return result;
}

vec3d div_vd(vec3d a, double x) {
    vec3d result = {
            .x = a.x / x,
            .y = a.y / x,
            .z = a.z / x
    };

    return result;
}


vec3d add_dv(double x, vec3d a) {
    vec3d result = {
            .x = x + a.x,
            .y = x + a.y,
            .z = x + a.z
    };

    return result;
}

vec3d sub_dv(double x, vec3d a) {
    vec3d result = {
            .x = x - a.x,
            .y = x - a.y,
            .z = x - a.z
    };

    return result;
}

vec3d mul_dv(double x, vec3d a) {
    vec3d result = {
            .x = x * a.x,
            .y = x * a.y,
            .z = x * a.z
    };

    return result;
}

vec3d div_dv(double x, vec3d a) {
    vec3d result = {
            .x = x / a.x,
            .y = x / a.y,
            .z = x / a.z
    };

    return result;
}


vec3d random_vector() {
    vec3d vec = {
        .x = ((double)rand() / RAND_MAX) * 2.0 - 1.0,
        .y = ((double)rand() / RAND_MAX) * 2.0 - 1.0,
        .z = ((double)rand() / RAND_MAX) * 2.0 - 1.0
    };

    return norm(vec);
}


vec3d random_hemisphere_vec(vec3d hemisphere_up) {
    vec3d vec = random_vector();

    if (dot(vec, hemisphere_up) < 0) {
        vec = mul_vd(vec, -1);
    }

    return vec;
}

vec3d build_vec(double x, double y, double z) {
    vec3d v = { .x = x, .y = y, .z = z };
    return v;
}
