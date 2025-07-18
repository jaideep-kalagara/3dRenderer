#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int width;
extern int height;

// helpers
size_t get_pixel(int x, int y);

// window
bool initialize_window(void);
void destroy_window(void);

// drawing
void draw_grid(int spacing, uint32_t color);
void draw_rect(int x, int y, int w, int h, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);

// rendering
void clear_color_buffer(uint32_t color);
void render_color_buffer(void);


#endif