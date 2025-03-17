#define SDL_MAIN_HANDLED
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <SDL.h>

SDL_Window *g_window{nullptr};
SDL_Surface *g_screen_surface{nullptr};
SDL_Surface *g_hello_world{nullptr};

bool init() {
    bool success = true;

    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        g_window = SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN);
        if (g_window == nullptr) {
            printf("SDL_CreateWindow: %s\n", SDL_GetError());
            success = false;
        } else {
            g_screen_surface = SDL_GetWindowSurface(g_window);
        }
    }

    return success;
}

bool load_media() {
    bool success = true;

    // Load splash image
    // Hack (copy the bmp file to cmake build, src files)
    g_hello_world = SDL_LoadBMP("hello_world.bmp");
    if (g_hello_world == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Deallocate surface
    SDL_FreeSurface(g_hello_world);
    g_hello_world = nullptr;

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        printf("SDL_Init: %s\n", SDL_GetError());
    } else {
        // Load media
        if (!load_media()) {
            printf("SDL_LoadBMP: %s\n", SDL_GetError());
        } else {
            SDL_BlitSurface(g_hello_world, nullptr, g_screen_surface, nullptr);
            SDL_UpdateWindowSurface(g_window);

            // Hack to get the window to stay up
            SDL_Event event;
            bool quit = false;
            while (quit == false) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }
    }

    close();
    return EXIT_SUCCESS;
}
