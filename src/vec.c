#include <math.h>
#include "vec.h"

vec3_t vec3_rotate_x(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) + v.z * sin(angle),   
        .z = -v.y * sin(angle) + v.z * cos(angle)  

    };

    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),  
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)   

    };

    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) + v.y * sin(angle),   
        .y = -v.x * sin(angle) + v.y * cos(angle), 
        .z = v.z
    };

    return rotated_vector;
}

vec3_t vec3_rotate(vec3_t v, vec3_t a) {
    vec3_t rotated_vector = v;
    rotated_vector = vec3_rotate_x(rotated_vector, a.x);
    rotated_vector = vec3_rotate_y(rotated_vector, a.y);
    rotated_vector = vec3_rotate_z(rotated_vector, a.z);

    return rotated_vector;
}