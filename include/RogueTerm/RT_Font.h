/**
 * Header file for the RT_Font class
 */
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RogueTerm/RT_Rect.h"
#include "RogueTerm/RT_Point2D.h"
#include "RogueTerm/RT_Colour.h"
#pragma once

class RT_Font {
    private:
        // Font texture
        SDL_Surface *surface = NULL;

        // Number of columns and rows inside the font texture
        RT_Rect csize = {0, 0, 16, 16};

        // Dimensions of a character in pixels
        RT_Rect character_dimensions;

        RT_Point2D get_char_tile(char c);
    public:
        RT_Font(const char *src);
        RT_Font(const char *src, RT_Rect _csize);
        ~RT_Font();
        bool load_font(const char *src);
        RT_Rect get_font_dimensions();

        void blit_char(char c, SDL_Surface* dst, RT_Point2D pos, RT_Colour *colour);
        void blit_tile(RT_Point2D tpos, SDL_Surface* dst, RT_Point2D pos, RT_Colour *colour);
};