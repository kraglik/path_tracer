#include <stdlib.h>
#include <stdio.h>
#include <tracer/material.h>


color single_color_get_color_at(void* data, double x, double y) {
    color c;

    c.x = ((color*)data)->x;
    c.y = ((color*)data)->y;
    c.z = ((color*)data)->z;

    return c;
}


texture* build_single_color_texture(color c) {
    color* texture_c = (color*)malloc(sizeof(color));

    texture_c->x = c.x;
    texture_c->y = c.y;
    texture_c->z = c.z;

    texture* t = (texture*) malloc(sizeof(texture));

    t->data = texture_c;
    t->get_color_at = single_color_get_color_at;

    return t;
}
