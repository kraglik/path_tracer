#include <stdio.h>

#include <tracer/math.h>
#include <tracer/tracer.h>
#include <math.h>


int main() {
    material s1mat = {
        .color = build_vec(1, 0, 0),
        .ke = M_PI * 4,
        .kr = 0.5
    };

    material s2mat = {
        .color = build_vec(0, 1, 0),
        .ke = M_PI / 2,
        .kr = 0.5
    };

    material s3mat = {
        .color = build_vec(0, 0, 1),
        .ke = M_PI * 2,
        .kr = 0.5
    };

    material p1mat = {
        .color = build_vec(1, 1, 1),
        .ke = M_PI / 5,
        .kr = 0.5
    };

    object* s1 = build_sphere(
        build_vec(8, 0, 0),
        2.0,
        &s1mat
    );

    object* s2 = build_sphere(
        build_vec(8, 0, 4),
        2.0,
        &s2mat
    );

    object* s3 = build_sphere(
        build_vec(8, 0, -4),
        2.0,
        &s3mat
    );

    object* p1 = build_plane(
        build_vec(0, 2, 0),
        build_vec(0, -1, 0),
        &p1mat
    );

    screen s = {
        .distance = 1,
        .width = 1920,
        .height = 1080,
        .scale = 1.0 / 1000
    };

    camera c = {
        .screen = s,
        .direction = build_vec(1, 0, 0),
        .position = build_vec(0, 0, 0),
        .up = build_vec(0, 1, 0),
        .focus = 8
    };

    object* objects[4] = { s1, s2, s3, p1 };

    tracer_config t_conf = {
        .recursion_depth = 5,
        .samples_per_pixel = 120
    };

    tracer t = {
        .background = build_vec(0.2, 0.5, 0.8),
        .camera = &c,
        .objects = objects,
        .n_objects = 4,
        .config = &t_conf
    };

    trace_to_file(&t, "result.bmp");

    return 0;
}
