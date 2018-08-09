/**
 * Struct for representing geometric 2D rectangles with x,y coordinates, width
 * and height.
 */
#pragma once

struct RT_Rect
{
    int x;
    int y;
    int width;
    int height;

    operator SDL_Rect() {
        return {x, y, width, height};
    }
};