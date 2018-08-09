#include "RogueTerm/RT_Font.h"

RT_Font::RT_Font(const char *src) {
    // Attempt to load font from given source path
    if(!load_font(src)) {
        printf("Error: failed to load font\n");
    }
}

// Free used memory
RT_Font::~RT_Font() {
    SDL_FreeSurface(surface);
}

bool RT_Font::load_font(const char *src) {
    SDL_RWops *rwop = SDL_RWFromFile(src, "rb");
    surface = IMG_LoadPNG_RW(rwop);
    
    // Return false if surface failed to load
    if(surface == NULL) {
        return false;
    }

    character_dimensions = {0,0,surface->w/CHAR_COLUMNS, surface->h/CHAR_ROWS};
    return true;
}

RT_Rect RT_Font::get_font_dimensions() {
    return character_dimensions;
}

RT_Rect RT_Font::get_char_rect(char c) {
    return {0,0,10,16};
}

SDL_Rect RT_Font::get_char_sdl_rect(char c) {
    int row, col;
    if((32 <= c) && (c <= 63)) {
        row = 0;
        col = c - 32;
    }
    else if(c == 64) {
        row = 1;
        col = 0;
    }
    else if((65 <= c) && (c <= 90)) {
        row = 3;
        col = c - 65;
    }
    else if((97 <= c) && (c <= 122)) {
        row = 4;
        col = c - 97;
    }
    else if((91 <= c) && (c <= 96)) {
        row = 1;
        col = c - 90;
    }
    else if((123 <= c) && (c <= 126)) {
        row = 1;
        col = c - 116;
    }
    else if((176 <= c) && (c <= 181)) {
        row = 1;
        col = c - 165;
    }

    return {col*character_dimensions.width,
            row*character_dimensions.height,
            character_dimensions.width,
            character_dimensions.height};
}

void RT_Font::blit_char(char c, SDL_Surface* dst, int x, int y, RT_Colour *colour) {
    // Generate the rect of character texture and output rect
    SDL_Rect crect = get_char_sdl_rect(c);
    SDL_Rect drect = {x, y, crect.w, crect.h};

    // Blit character to the destination surface
    SDL_BlitSurface(surface, &crect, dst, &drect);

    // If a colour was given then apply it
    if(colour != NULL) {
        // Generate surface filled with the given colour
        SDL_Surface *cmod = SDL_CreateRGBSurface(0, character_dimensions.width, character_dimensions.height, 32, 0, 0, 0, 0);
        SDL_FillRect(cmod, NULL, SDL_MapRGB(cmod->format, colour->r, colour->g, colour->b));

        // Blit colour modulator surface to the destination surface
        SDL_SetSurfaceBlendMode(cmod, SDL_BLENDMODE_MOD);
        SDL_BlitSurface(cmod, NULL, dst, &drect);

        // Free cmod from memory
        SDL_FreeSurface(cmod);
    }
}