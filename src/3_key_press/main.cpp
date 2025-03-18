#define SDL_MAIN_HANDLED
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <SDL3/SDL.h>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window *g_window{nullptr};
SDL_Surface *g_screen_surface{nullptr};
SDL_Surface *g_key_press_surface[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *current_surface{nullptr};

bool init() {
    bool success = true;

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        g_window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (g_window == nullptr) {
            printf("SDL_CreateWindow: %s\n", SDL_GetError());
            success = false;
        } else {
            g_screen_surface = SDL_GetWindowSurface(g_window);
        }
    }

    return success;
}

void close() {
    //Deallocate surfaces
    for (auto &i: g_key_press_surface) {
        SDL_DestroySurface(i);
        i = nullptr;
    }

    //Destroy window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface *load_surface(const std::string &path) {
    // Load image at specific path
    SDL_Surface *loaded_surface = SDL_LoadBMP(path.c_str());
    if (loaded_surface == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
    }
    return loaded_surface;
};

bool load_media() {
    bool success = true;

    // Load default surface
    g_key_press_surface[KEY_PRESS_SURFACE_DEFAULT] = load_surface("press.bmp");
    if (g_key_press_surface[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    // Load up surface
    g_key_press_surface[KEY_PRESS_SURFACE_UP] = load_surface("up.bmp");
    if (g_key_press_surface[KEY_PRESS_SURFACE_UP] == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    // Load down surface
    g_key_press_surface[KEY_PRESS_SURFACE_DOWN] = load_surface("down.bmp");
    if (g_key_press_surface[KEY_PRESS_SURFACE_DOWN] == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    // Load left surface
    g_key_press_surface[KEY_PRESS_SURFACE_LEFT] = load_surface("left.bmp");
    if (g_key_press_surface[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    // Load right surface
    g_key_press_surface[KEY_PRESS_SURFACE_RIGHT] = load_surface("right.bmp");
    if (g_key_press_surface[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

int main(int argc, char *argv[]) {
    if (!init()) {
        printf("SDL_Init: %s\n", SDL_GetError());
    } else {
        // Load media
        if (!load_media()) {
            printf("SDL_LoadBMP: %s\n", SDL_GetError());
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            current_surface = g_key_press_surface[KEY_PRESS_SURFACE_DEFAULT];

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_EVENT_KEY_DOWN) {
                        //Select surfaces based on key press
                        switch (e.key.key) {
                            case SDLK_UP:
                                current_surface = g_key_press_surface[KEY_PRESS_SURFACE_UP];
                                break;

                            case SDLK_DOWN:
                                current_surface = g_key_press_surface[KEY_PRESS_SURFACE_DOWN];
                                break;

                            case SDLK_LEFT:
                                current_surface = g_key_press_surface[KEY_PRESS_SURFACE_LEFT];
                                break;

                            case SDLK_RIGHT:
                                current_surface = g_key_press_surface[KEY_PRESS_SURFACE_RIGHT];
                                break;

                            default:
                                current_surface = g_key_press_surface[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }

                //Apply the current image
                SDL_BlitSurface(current_surface, nullptr, g_screen_surface, nullptr);

                //Update the surface
                SDL_UpdateWindowSurface(g_window);
            }
        }
    }

    //Free resources and close SDL
    close();

    return EXIT_SUCCESS;
}
