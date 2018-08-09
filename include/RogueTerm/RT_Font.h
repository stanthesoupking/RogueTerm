/**
 * Header file for the RT_Font class
 */
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RogueTerm/RT_Rect.h"
#include "RogueTerm/RT_Colour.h"
#pragma once

class RT_Font {
    private:
        // Font texture
        SDL_Surface *surface = NULL;

        // Number of columns and rows on a typical font image
        const int CHAR_COLUMNS = 32;
        const int CHAR_ROWS = 8;

        // Dimensions of a character in pixels
        RT_Rect character_dimensions;

        RT_Rect get_char_rect(char c);
        SDL_Rect get_char_sdl_rect(char c);
    public:
        RT_Font(const char *src);
        ~RT_Font();
        bool load_font(const char *src);
        RT_Rect get_font_dimensions();
        void blit_char(char c, SDL_Surface* dst, int x, int y, RT_Colour *colour);
};