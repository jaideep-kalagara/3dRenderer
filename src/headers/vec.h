#ifndef VEC_H
#define VEC_H


typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;



vec3_t vec3_rotate(vec3_t v, vec3_t a);

#endif