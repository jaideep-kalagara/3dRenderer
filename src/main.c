#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


int width = 800;
int height = 600;

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

uint32_t* color_buffer = NULL;




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

void render_color_buffer(void) {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_color_buffer();

    clear_color_buffer(0xFFFFFF00);
    draw_rect(100, 100, 100, 100, 0xFF0000FF);

    
    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    free(color_buffer);

    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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