#include <stdio.h>

#include <tracer/math.h>
#include <tracer/tracer.h>
#include <math.h>


int main() {

    material s1mat = {
        .surface_texture = build_single_color_texture(build_vec(1, 0, 0)),
        .emittance_texture = build_single_color_texture(build_vec(1, 0, 0)),
        .emittance_strength = 0.5, // M_PI * 4,
        .reflect = 1.0,
        .reflect_randomness = 0.3,
        .diffuse = 0.0,
        .refract = 0,
        .refract_randomness = 0,
        .refract_index = 0.0
    };

    material s2mat = {
        .surface_texture = build_single_color_texture(build_vec(0, 1, 0)),
        .emittance_texture = build_single_color_texture(build_vec(0, 1, 0)),
        .emittance_strength = 0, // M_PI / 2,
        .reflect = 1.0,
        .reflect_randomness = 0.01,
        .diffuse = 0.2,
        .refract = 0,
        .refract_randomness = 0,
        .refract_index = 0.0
    };

    material s3mat = {
        .surface_texture = build_single_color_texture(build_vec(0, 0, 1)),
        .emittance_texture = build_single_color_texture(build_vec(0, 0, 1)),
        .emittance_strength = 0.1, //M_PI * 2,
        .reflect = 1.0,
        .reflect_randomness = 1.0,
        .diffuse = 0.8,
        .refract = 0,
        .refract_randomness = 0,
        .refract_index = 0.0
    };

    material s4mat = {
        .surface_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_strength = M_PI,
        .reflect = 0.0,
        .reflect_randomness = 1.0,
        .diffuse = 0.0,
        .refract = 0,
        .refract_randomness = 0,
        .refract_index = 0.0
    };

    material s5mat = {
        .surface_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_strength = 0.0,
        .diffuse = 0.0,
        .reflect = 0.1,
        .reflect_randomness = 0.1,
        .refract = 0.9,
        .refract_randomness = 0.1,
        .refract_index = 10.0
    };

    material s6mat = {
            .surface_texture = build_single_color_texture(build_vec(1, 1, 0)),
            .emittance_texture = build_single_color_texture(build_vec(1, 1, 0)),
            .emittance_strength = 0.01, //M_PI * 2,
            .reflect = 1.0,
            .reflect_randomness = 1.0,
            .diffuse = 0.8,
            .refract = 0,
            .refract_randomness = 0,
            .refract_index = 0.0
    };

    material p1mat = {
        .surface_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_texture = build_single_color_texture(build_vec(1, 1, 1)),
        .emittance_strength = 0, //M_PI / 5,
        .diffuse = 0.5,
        .reflect = 0.5,
        .reflect_randomness = 0.7,
        .refract = 0,
        .refract_randomness = 0,
        .refract_index = 0.0
    };

    object* s1 = build_sphere(
        build_vec(8, 0, 0),
        2.0,
        &s1mat
    );

    object* s2 = build_sphere(
        build_vec(6.5, 0, 3.6),
        2.0,
        &s2mat
    );

    object* s3 = build_sphere(
        build_vec(6.5, 0, -3.6),
        2.0,
        &s3mat
    );

    object* s4 = build_sphere(
        build_vec(6, -2, 0),
        1.0,
        &s4mat
    );

    object* s5 = build_sphere(
        build_vec(5, 1, 0),
        1,
        &s5mat
    );

    object* s6 = build_sphere(
        build_vec(4, 1, -2),
        1.0,
        &s6mat
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

    object* objects[7] = { s1, s2, s3, s4, s5, s6, p1 };

    tracer_config t_conf = {
        .recursion_depth = 6,
        .samples_per_pixel = 1200
    };

    tracer t = {
        .background = build_vec(0.2, 0.5, 0.8),
        .camera = &c,
        .objects = objects,
        .n_objects = 7,
        .config = &t_conf
    };

    trace_to_file(&t, "result.bmp");

    return 0;
}
