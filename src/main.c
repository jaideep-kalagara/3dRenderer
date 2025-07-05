#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


#define WIDTH 800
#define HEIGHT 600

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;




uint32_t get_pixel(int x, int y) {
    return color_buffer[(WIDTH * y) + x];
}

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }


    return true;
}
void setup(void) {
    // create SDL window
    is_running = initialize_window();

    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WIDTH * HEIGHT);

    // set pixel at row 10 and column 20 to red (ARGB)
    color_buffer[get_pixel(10, 20)] = 0xFFFF0000;
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
    
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    
    SDL_RenderPresent(renderer);
}

int main(void) {

    
    setup();

    while (is_running) {
        process_input();
        update();
        render(); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(color_buffer);

    return 0;
}