#include <tracer/material.h>
#include <tracer/math.h>
#include <tracer/object.h>
#include <tracer/tracer.h>
#include <tracer/config.h>

#include <stdio.h>
#include <stdint.h>
#include <qdbmp/qdbmp.h>
#include <math.h>


bool best_hit(tracer* t, ray r, hit* out) {
    hit temp, best;

    bool was_hit = false;

    for (size_t obj = 0; obj < t->n_objects; obj++) {
        object* o = t->objects[obj];

        if (o->intersect(o, r, &temp)) {
            vec3d dist_vec = sub_vv(temp.position, r.origin);
            double temp_hit_distance = len(dist_vec);

            if (dot(r.direction, dist_vec) < 0 || temp_hit_distance < EPSILON) {
                continue;
            }

            if (was_hit) {
                double d_temp = len(dist_vec);
                double d_best = len(sub_vv(best.position, r.origin));

                if (d_temp < d_best) {
                    best = temp;
                }

            } else {
                best = temp;
                was_hit = true;
            };
        }
    }

    if (was_hit) {
        *out = best;
    }

    return was_hit;
}


color trace_ray(tracer* t, ray r, size_t depth) {
    if (depth == 0)
        return t->background;

    hit h;

    if (!best_hit(t, r, &h)) {
        return t->background;
    }

    color emit = h.material->color;

    ray out_r = { .origin = h.position, .direction = random_hemisphere_vec(h.normal) };
    color incoming = trace_ray(t, shift(out_r, EPSILON * 1.01), depth - 1);

    double p = 1 / (2 * M_PI);
    double brdf = h.material->kr / M_PI;
    double cos_theta = dot(out_r.direction, h.normal);

    return add_vv(mul_vd(emit, h.material->ke), mul_vd(incoming, brdf * cos_theta / p));
}

void trace_to_file(tracer* t, const char* path) {

    camera* c = t->camera;

    BMP* img = BMP_Create(c->screen.width, c->screen.height, 24);

    for (size_t x = 0; x < c->screen.width; x++) {
        for (size_t y = 0; y < c->screen.height; y++) {
            color clr = build_vec(0, 0, 0);

            for (size_t sample = 0; sample < t->config->samples_per_pixel; sample++) {
                ray r = spawn_random_ray(c, x, y);
                clr = add_vv(clr, trace_ray(t, r, t->config->recursion_depth));
            }

            clr = clip(0, 1, div_vd(clr, t->config->samples_per_pixel));

            int r = (int)(clr.x * 255.0);
            int g = (int)(clr.y * 255.0);
            int b = (int)(clr.z * 255.0);

            BMP_SetPixelRGB(img, x, y, r, g, b);

        }
    }

    BMP_WriteFile(img, path);
}

