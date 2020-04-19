#include <stdio.h>

#include <tracer/math.h>
#include <tracer/tracer.h>
#include <math.h>


int main() {

    material s1mat = {
        .surface_structure = build_single_color_texture(build_vec(1, 0, 0)),
        .emittance_texture = build_single_color_texture(build_vec(1, 0, 0)),
        .ke = 0, // M_PI * 4,
        .kr = 0.8
    };

    material s2mat = {
        .surface_structure = build_single_color_texture(build_vec(0, 1, 0)),
        .emittance_texture = build_single_color_texture(build_vec(0, 1, 0)),
        .ke = 0, // M_PI / 2,
        .kr = 0.8
    };

    material s3mat = {
        .surface_structure = build_single_color_texture(build_vec(0, 0, 1)),
        .emittance_texture = build_single_color_texture(build_vec(0, 0, 1)),
        .ke = 0.1, //M_PI * 2,
        .kr = 0.8
    };

    material s4mat = {
        .surface_structure = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .ke = M_PI,
        .kr = 0.0
    };

    material s5mat = {
            .surface_structure = build_single_color_texture(build_vec(1, 1, 0)),
            .emittance_texture = build_single_color_texture(build_vec(1, 1, 0)),
            .ke = M_PI,
            .kr = 1.0
    };

    material p1mat = {
        .surface_structure = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .ke = 0, //M_PI / 5,
        .kr = 0.8
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

    object* s4 = build_sphere(
        build_vec(6, 1, 0),
        1.0,
        &s4mat
    );

    object* s5 = build_sphere(
            build_vec(6, -2, 0),
            0.5,
            &s5mat
    );


    object* p1 = build_plane(
        build_vec(0, 2, 0),
        build_vec(0, -1, 0),
        &p1mat
    );

    screen s = {
        .distance = 1,
        .width = 800,
        .height = 800,
        .scale = 1.0 / 600
    };

    camera c = {
        .screen = s,
        .direction = build_vec(1, 0, 0),
        .position = build_vec(0, 0, 0),
        .up = build_vec(0, 1, 0),
        .focus = 8
    };

    object* objects[6] = { s1, s2, s3, s4, s5, p1 };

    tracer_config t_conf = {
        .recursion_depth = 6,
        .samples_per_pixel = 240
    };

    tracer t = {
        .background = build_vec(0.2, 0.5, 0.8),
        .camera = &c,
        .objects = objects,
        .n_objects = 6,
        .config = &t_conf
    };

    trace_to_file(&t, "result.bmp");

    return 0;
}
