#define SDL_MAIN_HANDLED   //workaround, to prevent SDL from overwriting our existing main function
#include <SDL.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"


bool handleMessage() {
    SDL_Event event;

    //loop throug all available Events
    while (SDL_PollEvent(&event)) {

        // check the event type (for now only quit gets handled to exit the mainloop)
        switch (event.type) {
            case SDL_QUIT:
                return false;
        }
    }
    
    return true;
}


int main() {
    
    // Initialize the SDL Instance
    spdlog::info("initializing SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("Error initializing SDL: ", SDL_GetError());
        return 1;
    }

    // Create the SDL-Window Instance (supplying the Name, Position, Size, Flags)
    spdlog::info("creating SDL window");
    SDL_Window* window = SDL_CreateWindow("Vulkan Fun", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_VULKAN);
    if (!window) {
        spdlog::error("Error creating SDL window");
    }

    // Run the Mainloop and check for SDL-Events
    while (handleMessage()) {
        
    }

    // Destroy Window and exit SDL
    spdlog::info("cleaning up SDL");
    SDL_DestroyWindow(window);
    SDL_Quit();
    

    return 0;
}