#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"


bool is_running = false;

void setup(void) {
    // create SDL window
    is_running = initialize_window();

    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * width * height);
    if (!color_buffer) {
        fprintf(stderr, "Failed to allocate color buffer\n");
        is_running = false;
    }

    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!color_buffer_texture) {
        fprintf(stderr, "Failed to create color buffer texture: %s\n", SDL_GetError());
        is_running = false;
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
// TODO: add update logic
}



void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_color_buffer();

    clear_color_buffer(0xFFFFFF00);
    draw_pixel(100, 100, 0xFF0000FF);

    
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