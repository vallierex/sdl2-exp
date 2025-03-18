#define SDL_MAIN_HANDLED
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <SDL3/SDL.h>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

SDL_Window *g_window{nullptr};
SDL_Surface *g_screen_surface{nullptr};
SDL_Surface *g_x_out{nullptr};

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
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0);
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
    g_x_out = SDL_LoadBMP("x.bmp");
    if (g_x_out == nullptr) {
        printf("SDL_LoadBMP: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Deallocate surface
    SDL_DestroySurface(g_x_out);
    g_x_out = nullptr;

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
            //Apply the image
            SDL_BlitSurface(g_x_out, nullptr, g_screen_surface, nullptr);

            //Update the surface
            SDL_UpdateWindowSurface(g_window);

            // Hack to get the window to stay up
            SDL_Event event;
            bool quit = false;

            while (quit == false) {
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                }
            }
        }
    }
    //Free resources and close SDL
    close();

    return EXIT_SUCCESS;
}
