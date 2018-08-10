/**
 * Header file for the RT_Window class
 */
#include "SDL2/SDL.h"
#include "RT_Font.h"
#include "RT_Point2D.h"
#include "RT_Rect.h"
#include "RogueTerm/RT_CharacterMatrix.h"
#pragma once

class RT_Window
{
    private:
        SDL_Window* window;
        SDL_Surface* surface;

        int cwidth, cheight, pwidth, pheight;
        const char *title;
        RT_CharacterMatrix *character_matrix;

        RT_Font* font;
    public:
        RT_Window(RT_Font* _font, int _width, int _height, const char *title, Uint32 flags);
        ~RT_Window();
        bool init_window(Uint32 flags);
        void clear();
        void update();

        // Drawing methods
        void draw_char(char c, RT_Point2D pos, RT_Colour *colour);
        void draw_string(const char *string, RT_Point2D pos, RT_Colour *colour);

        // Font override
        void draw_char(char c, RT_Point2D pos, RT_Colour *colour, RT_Font* font);
        void draw_string(const char *string, RT_Point2D pos, RT_Colour *colour, RT_Font* font);

        // Utility methods
        RT_Point2D pixel_to_cell_coordinates(RT_Point2D pos);
};