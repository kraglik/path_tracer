#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include <tracer/math.h>


typedef struct texture {
    void* data;
    color (*get_color_at)(void* data, double x, double y);
} texture;


texture* build_single_color_texture(color c);


typedef struct material {

    texture* emittance_texture;
    texture* surface_structure;

    double ke;  // emittance coefficient
    double kr;  // reflectance coefficient

} material;


#endif
