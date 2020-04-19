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
        object *o = t->objects[obj];

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


color trace_reflect(tracer* t, ray r, hit* hit, size_t depth) {

    if (hit->material->reflect == 0)
        return build_vec(0, 0, 0);

    vec2d t_coords = hit->texture_coords;
    void* texture_data = hit->material->surface_texture->data;
    color surface_color = hit->material->surface_texture->get_color_at(texture_data, t_coords.x, t_coords.y);

    vec3d reflect_dir = reflect(r.direction, hit->normal);
    vec3d noise = random_hemisphere_vec(reflect_dir);

    reflect_dir = norm(add_vv(reflect_dir, mul_vd(noise, hit->material->reflect_randomness)));

    ray reflected_ray = { .origin = hit->position, .direction = reflect_dir };

    color incoming = trace_ray(t, shift(reflected_ray, EPSILON * 1.01), depth - 1);

    color result = mul_vv(surface_color, incoming);
    result = mul_vd(result, 1.0 - hit->material->diffuse);
    result = add_vv(result, mul_vd(surface_color, len(incoming) * hit->material->diffuse));

    return result;
}


color trace_refract(tracer* t, ray r, hit* hit, size_t depth) {
    if (hit->material->refract == 0)
        return build_vec(0, 0, 0);

    vec2d t_coords = hit->texture_coords;
    void* texture_data = hit->material->surface_texture->data;
    color surface_color = hit->material->surface_texture->get_color_at(texture_data, t_coords.x, t_coords.y);

    vec3d refract_dir = refract(r.direction, hit->normal, hit->material->refract_index);
    vec3d noise = random_hemisphere_vec(refract_dir);

    refract_dir = norm(add_vv(refract_dir, mul_vd(noise, hit->material->refract_randomness)));

    ray refracted_ray = { .origin = hit->position, .direction = refract_dir };

    color incoming = trace_ray(t, shift(refracted_ray, EPSILON * 1.01), depth - 1);

    return mul_vv(incoming, surface_color);
}


color trace_ray(tracer* t, ray r, size_t depth) {
    if (depth == 0)
        return t->background;

    hit h;

    if (!best_hit(t, r, &h)) {
        return t->background;
    }

    texture* emit_texture = h.material->emittance_texture;

    color emit_c = emit_texture->get_color_at(emit_texture->data, h.texture_coords.x, h.texture_coords.y);

    color reflect = mul_vd(trace_reflect(t, r, &h, depth), h.material->reflect);
    color refract = mul_vd(trace_refract(t, r, &h, depth), h.material->refract);

    color incoming = add_vv(reflect, refract);

    return add_vv(mul_vd(emit_c, h.material->emittance_strength), incoming);
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

