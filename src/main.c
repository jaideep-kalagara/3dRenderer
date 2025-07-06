#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vec.h"

#define N_POINTS 9*9*9


vec3_t cube_points[N_POINTS]; // 9x9x9 cube
vec2_t projected_points[N_POINTS];



vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640;

bool is_running = false;

vec2_t project(vec3_t point, float fov_factor) {
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z
    };
    return projected_point;
}

void setup(void) {
    // create SDL window
    is_running = initialize_window();

    
    // start loading array of vectors
    // from -1 to 1 (9x9x9 cube)
    int point_count = 0;
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { x, y, z };
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
    }

}


void update(void) {
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cube_points[i];

        point.x -= camera_position.x;
        point.y -= camera_position.y;
        point.z -= camera_position.z;

        vec2_t projected_point = project(point, fov_factor);
        projected_points[i] = projected_point;
    }
}



void render(void) {
    for (int i = 0; i < N_POINTS; i++) {
        vec2_t projected_point = projected_points[i];
        draw_rect(projected_point.x + (width / 2), projected_point.y + (height / 2), 4, 4, 0xFFFFFF00);
    }

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    
    SDL_RenderPresent(renderer);
}



int main(void) {
    setup();

    while (is_running) {
        process_input();
        update();
        render(); 
    }

    destroy_window();

    return 0;
}