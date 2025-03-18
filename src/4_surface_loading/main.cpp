#define SDL_MAIN_HANDLED
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <SDL3/SDL.h>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool load_media();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface *load_surface(const std::string &path);

//The window we'll be rendering to
SDL_Window *g_window = nullptr;

//The surface contained by the window
SDL_Surface *g_screen_surface = nullptr;

//Current displayed image
SDL_Surface *gStretchedSurface = nullptr;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        g_window = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH,SCREEN_HEIGHT, 0);
        if (g_window == nullptr) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get window surface
            g_screen_surface = SDL_GetWindowSurface(g_window);
        }
    }

    return success;
}

bool load_media() {
    //Loading success flag
    bool success = true;

    //Load stretching surface
    gStretchedSurface = load_surface("stretch.bmp");
    if (gStretchedSurface == nullptr) {
        printf("Failed to load stretching image!\n");
        success = false;
    }

    return success;
}

void close() {
    //Free loaded image
    SDL_DestroySurface(gStretchedSurface);
    gStretchedSurface = nullptr;

    //Destroy window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface *load_surface(const std::string &path) {
    //The final optimized image
    SDL_Surface *optimizedSurface = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, g_screen_surface->format);
        if (optimizedSurface == nullptr) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    return optimizedSurface;
}

int main(int argc, char *args[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!load_media()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                }

                //Apply the image stretched
                SDL_Rect stretchRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                SDL_BlitSurfaceScaled(gStretchedSurface, nullptr, g_screen_surface, &stretchRect, SDL_SCALEMODE_LINEAR);

                //Update the surface
                SDL_UpdateWindowSurface(g_window);
            }
        }
    }

    //Free resources and close SDL
    close();

    return EXIT_SUCCESS;
}
