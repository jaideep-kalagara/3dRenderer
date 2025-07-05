#include "display.h"




SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int width = 800;
int height = 600;


size_t get_pixel(int x, int y) {
    return width * y + x;
}

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // get full screen
    SDL_DisplayMode display_mode;
    SDL_GetDesktopDisplayMode(0, &display_mode);
    // 800x600 resoulution if commented
    width = display_mode.w;
    height = display_mode.h;

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void clear_color_buffer(uint32_t color) {
    for (int i = 0; i < width*height; i++) {
        color_buffer[i] = color;
    }
}

void draw_grid(int spacing, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i % spacing == 0 || j % spacing == 0) {
                color_buffer[get_pixel(i, j)] = color;
            }
        }
    }
}


void draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            color_buffer[get_pixel(i, j)] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    color_buffer[get_pixel(x, y)] = color;
}

void render_color_buffer(void) {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void destroy_window(void) {
    free(color_buffer);

    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}