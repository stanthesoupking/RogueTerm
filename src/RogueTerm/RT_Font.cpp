#include "RogueTerm/RT_Font.h"
#include <stdio.h>

RT_Font::RT_Font(const char *src) {
    // Attempt to load font from given source path
    if(!load_font(src)) {
        printf("Error: failed to load font '%s'\n", src);
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

    character_dimensions = {0,0,surface->w/csize.width, surface->h/csize.height};

    return true;
}

RT_Rect RT_Font::get_font_dimensions() {
    return character_dimensions;
}

RT_Point2D RT_Font::get_char_tile(char c) {
    RT_Point2D pos = {c % csize.width, c / csize.width};

    return pos;
}

void RT_Font::blit_char(char c, SDL_Surface* dst, RT_Point2D pos, RT_Colour *colour) {
    // Get tile position of character on the tileset
    RT_Point2D tpos = get_char_tile(c);

    // Blit wth the tile position
    blit_tile(tpos, dst, pos, colour);
}

void RT_Font::blit_tile(RT_Point2D tpos, SDL_Surface* dst, RT_Point2D pos, RT_Colour *colour) {
    // Generate the rect of tile texture
    SDL_Rect crect = {tpos.x * character_dimensions.width,
                      tpos.y  * character_dimensions.height,
                      character_dimensions.width, character_dimensions.height};
    
    // Generate output rect
    SDL_Rect drect = {pos.x, pos.y, character_dimensions.width, character_dimensions.height};

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