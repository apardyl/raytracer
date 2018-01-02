#include "SDLFrontend.h"
#include "SDLError.h"
#include "backends/solid_color_cuda/SolidColorCudaBackend.h"

SDLFrontend::SDLFrontend() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLError("SDL could not initialize");
    }

    window = SDL_CreateWindow(
            "Ray Tracer",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw SDLError("Window could not be created");
    }

    screenSurface = SDL_GetWindowSurface(window);
}

SDLFrontend::~SDLFrontend() {
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void SDLFrontend::run() {
    createRenderedImageSurface();

    bool quit = false;
    SDL_Event e{};

    while (!quit) {
        Uint32 startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        render();

        Uint32 frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }
}

void SDLFrontend::createRenderedImageSurface() {
    SolidColorCudaBackend backend;
    backend.setResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(
            backend.render(), SCREEN_WIDTH, SCREEN_HEIGHT, 24,
            SCREEN_WIDTH * 3, SDL_PIXELFORMAT_RGB24);
    if (surface == nullptr) {
        throw SDLError("Could not create rendered image surface");
    }

    renderedImage = SDL_ConvertSurface(surface, screenSurface->format, 0);
    if (renderedImage == nullptr) {
        throw SDLError("Could not convert rendered image surface");
    }
}

void SDLFrontend::render() {
    SDL_FillRect(screenSurface, nullptr, 0);
    SDL_BlitSurface(renderedImage, nullptr, screenSurface, nullptr);
    SDL_UpdateWindowSurface(window);
}
