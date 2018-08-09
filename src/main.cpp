#include "RogueTerm/RogueTerm.h"

#define WINDOW_COLUMNS  64
#define WINDOW_ROWS     32

// The font to use in the game window
RT_Font *font = NULL;

// The main game window
RT_Window *window = NULL;

// Method declarations
bool init();
void cleanup();
void startLoop();
void render();

int player_x, player_y;
RT_Colour player_colour;
char player_char;

int main(int argc, char **argv) {
    // Init RogueTerm window, quit if init fails
    if(!init()) {
        return 1;
    }

    startLoop();

    // Clean up and exit
    cleanup();

    return 0;
}

// Initialise the demo
bool init() {
    font = new RT_Font("./fonts/terminal.png");
    window = new RT_Window(font, WINDOW_COLUMNS, WINDOW_ROWS, "RogueTerm - Demo",
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Initialise player in the center of the 'room'
    player_x = WINDOW_COLUMNS / 2;
    player_y = WINDOW_ROWS / 2;
    player_colour = {255,255,0};
    player_char = '@';

    return true;
}

// Clean up variables
void cleanup() {
    delete window;
    delete font;
}

// Start main program loop
void startLoop() {
    // When set to true, exit loop
    bool quit = false;

    // Event buffer
    SDL_Event e;

    // Program loop
    while(!quit) {
        // Get user input
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        player_y--;
                        break;
                    case SDLK_DOWN:
                        player_y++;
                        break;
                    case SDLK_LEFT:
                        player_x--;
                        break;
                    case SDLK_RIGHT:
                        player_x++;
                        break;
                }
            }
        }
        
        render(); // Render scene
    }
}

// Render program objects
void render() {
    window->clear();

    RT_Colour title_colour = {255,255,255};
    RT_Colour subtitle_colour = {200,200,200};

    window->draw_string("Welcome to the RogueTerm demo!",1,1, &title_colour);
    window->draw_string("Use the arrow keys to move the character around...", 1, 2, &subtitle_colour);

    window->draw_char(player_char, player_x, player_y, &player_colour);

    window->update();
}