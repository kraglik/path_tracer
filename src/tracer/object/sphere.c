#include <tracer/object.h>
#include <tracer/tracer.h>
#include <math.h>

typedef struct sphere {

    vec3d center;
    double radius;

} sphere;

vec3d sphere_get_normal_at(void* data, vec3d position) {
    return norm(sub_vv(position, ((sphere*)data)->center));
}


bool solve_quadratic(double a, double b, double c, double* x1, double* x2) {
    double discr = b * b - 4 * a * c;
    if (discr < 0)
        return false;

    else if (discr == 0) {
        double p =  - 0.5 * b / a;
        *x1 = p;
        *x2 = p;

        return true;
    }
    else {
        double q = (b > 0) ?
                  -0.5 * (b + sqrt(discr)) :
                  -0.5 * (b - sqrt(discr));

        double v1 = q / a;
        double v2 = c / q;

        if (v1 > v2) {
            *x1 = v2;
            *x2 = v1;
        }
        else {
            *x1 = v1;
            *x2 = v2;
        }

        return true;
    }
}


bool sphere_intersect(object* o, ray r, hit* h) {
    sphere* s = (sphere*)o->data;

    vec2d texture_coords = {.x = 0, .y = 0};  // TODO: implement texture coordinates for basic surfaces

    double x1, x2;

    vec3d d = sub_vv(r.origin, s->center);
    double a = dot(r.direction, r.direction);
    double b = 2 * dot(r.direction, d);
    double c = dot(d, d) - s->radius * s->radius;

    if (!solve_quadratic(a, b, c, &x1, &x2)) {
        return false;
    }

    double distance = x1 > x2 ? x2 : x1;

    h->position = add_vv(r.origin, mul_vd(r.direction, distance));
    h->normal = sphere_get_normal_at(o->data, h->position);
    h->material = o->material;
    h->texture_coords = texture_coords;

    return true;
}

object* build_sphere(vec3d center, double radius, material* material) {
    sphere* s = (sphere*)malloc(sizeof(sphere));

    s->center = center;
    s->radius = radius;

    object* o = (object*) malloc(sizeof(object));

    o->data = s;
    o->material = material;
    o->get_normal_at = sphere_get_normal_at;
    o->intersect = sphere_intersect;

    return o;
}
