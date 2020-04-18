#include <tracer/math.h>

ray shift(ray r, double x) {
    ray new_ray = {
        .origin = add_vv(r.origin, mul_vd(r.direction, x)),
        .direction = r.direction
    };

    return new_ray;
}
