#include <tracer/object.h>
#include <tracer/tracer.h>

typedef struct plane {
    vec3d position;
    vec3d normal;
} plane;


vec3d plane_get_normal_at(void* data, vec3d position) {
    return ((plane*)data)->normal;
}

bool plane_intersect(object* o, ray r, hit* h) {
    plane* p = (plane*)o->data;
    double distance =
            dot(sub_vv(p->position, r.origin), p->normal) /
            dot(r.direction, p->normal);

    if (distance < EPSILON) {
        return false;
    }

    vec2d texture_coords = {.x = 0, .y = 0};  // TODO: implement texture coordinates for basic surfaces

    h->position = add_vv(r.origin, mul_vd(r.direction, distance));
    h->normal = p->normal;
    h->material = o->material;
    h->texture_coords = texture_coords;

    return true;
}

object* build_plane(vec3d position, vec3d normal, material* material) {
    plane* p = (plane*)malloc(sizeof(plane));

    p->position = position;
    p->normal = normal;

    object* o = (object*) malloc(sizeof(object));

    o->data = p;
    o->material = material;
    o->get_normal_at = plane_get_normal_at;
    o->intersect = plane_intersect;

    return o;
}

