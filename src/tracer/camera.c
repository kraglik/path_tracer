#include <tracer/camera.h>


vec3d w(camera* c) {
    return norm(mul_dv(-1, c->direction));
}

vec3d u(camera* c) {
    return norm(cross(c->up, w(c)));
}

vec3d v(camera* c) {
    return norm(cross(w(c), u(c)));
}

ray place_on_screen(camera* c, ray r) {
    return shift(r, dot(r.direction, c->direction) * c->screen.distance);
}

ray spawn_random_ray(camera* c, size_t pixel_x, size_t pixel_y) {

    double a = (double)rand() / RAND_MAX;
    double b = (double)rand() / RAND_MAX;

    double full_height = (double)c->screen.height;
    double full_width  = (double)c->screen.width;
    double half_height = full_height / 2;
    double half_width  = full_width / 2;

    double x = (pixel_x + a) - half_width;
    double y = (pixel_y + b) - half_height;

    vec3d center = add_vv(c->position, mul_vd(c->direction, c->screen.distance));

    vec3d target = add_vv(
        center,
        add_vv(
            mul_vd(u(c), c->screen.scale * x),
            mul_vd(v(c), c->screen.scale * y)
        )
    );

    ray r = {
        .origin = c->position,
        .direction = norm(sub_vv(target, c->position))
    };

    return place_on_screen(c, r);

}
