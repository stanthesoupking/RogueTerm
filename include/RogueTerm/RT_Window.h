/**
 * Header file for the RT_Window class
 */
#include "SDL2/SDL.h"
#include "RT_Font.h"
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
        RT_Window(RT_Font* _font, int _width, int _height, const char *title);
        ~RT_Window();
        bool init_window();
        void clear();
        void update();

        void draw_char(char c, int cx, int cy);
        void draw_string(const char *string, int cx, int cy);
};