#include "RogueTerm/RogueTerm.h"

// The main game window
RT_Window* window = NULL;

// Method declarations
bool init();
void cleanup();
void startLoop();
void render();

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

// Initialise the RogueTerm window
bool init() {
    RT_Font* font = new RT_Font("./fonts/dejavu.png");
    window = new RT_Window(font, 32, 24, "RogueTerm - Demo");
    return true;
}

// Clean up variables
void cleanup() {
    // TODO
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
        }
        
        render(); // Render scene
    }
}

// Render program objects
void render() {
    window->clear();

    window->draw_string("Hello, world.",1,1);

    window->update();
}