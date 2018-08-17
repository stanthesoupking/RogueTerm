#include "RogueTerm/RT_Window.h"
#include <stdio.h>

RT_Window::RT_Window(RT_Font* _font, int width, int height, const char *_title, Uint32 flags) {
    font = _font;
    csize = {0, 0, width, height};
    title = _title;

    init_window(flags);
}

RT_Window::~RT_Window() {
    SDL_FreeSurface(surface);
}

bool RT_Window::init_window(Uint32 flags) {
    // Generate pixel dimensions of window from character dimensions
    RT_Rect fdim = font->get_font_dimensions();
    psize = {0, 0, fdim.width * csize.width, fdim.height * csize.height};

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, psize.width, psize.height, flags);
    
    // Exit if window creation failed
    if(window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Get the window surface
    surface = SDL_GetWindowSurface(window);
    
    return true;
}

void RT_Window::clear() {
    // Update the window surface so the program doesn't freeze when the window
    // is resized.
    surface = SDL_GetWindowSurface(window);


    // Update pixel and characters size
    RT_Rect fdim = font->get_font_dimensions();

    psize = {0, 0, surface->w, surface->h};
    csize = {0, 0, psize.width / fdim.width, psize.height / fdim.height};

    // Fill surface with the color black
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
}

void RT_Window::update() {
    SDL_UpdateWindowSurface(window);
}

// Draws a character at the given coordinates
void RT_Window::draw_char(char c, RT_Point2D pos, RT_Colour *colour) {
    RT_Rect fdim = font->get_font_dimensions();

    font->blit_char(c, surface, {pos.x*fdim.width, pos.y*fdim.height}, colour);
}

// Draws a string at the given coordinates
void RT_Window::draw_string(const char* string, RT_Point2D pos, RT_Colour *colour) {
    RT_Rect fdim = font->get_font_dimensions();

    int i = 0;
    char c;
    while((c = string[i++]) != '\0') {
        font->blit_char(c, surface, {(pos.x + i - 1)*fdim.width, pos.y*fdim.height}, colour);
    }
}

// Draws a character at the given coordinates in custom font
void RT_Window::draw_char(char c, RT_Point2D pos, RT_Colour *colour, RT_Font* cfont) {
    RT_Rect fdim = cfont->get_font_dimensions();

    cfont->blit_char(c, surface, {pos.x*fdim.width, pos.y*fdim.height}, colour);
}

// Draws a string at the given coordinates in custom font
void RT_Window::draw_string(const char* string, RT_Point2D pos, RT_Colour *colour, RT_Font* cfont) {
    RT_Rect fdim = cfont->get_font_dimensions();

    int i = 0;
    char c;
    while((c = string[i++]) != '\0') {
        cfont->blit_char(c, surface, {(pos.x + i - 1)*fdim.width, pos.y*fdim.height}, colour);
    }
}

// Convert pixel to character cell coordinates
RT_Point2D RT_Window::pixel_to_cell_coordinates(RT_Point2D pos) {
    RT_Rect fdim = font->get_font_dimensions();
    pos.x = pos.x / fdim.width;
    pos.y = pos.y / fdim.height;

    return pos;
}

// Return window size in characters
RT_Rect RT_Window::get_window_size() {
    return csize;
}

// Return window size in pixels
RT_Rect RT_Window::get_window_pixel_size() {
    return psize;
}