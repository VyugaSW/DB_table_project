#include "window_manager.h"
#include "notifyError.h"
#include <stdio.h>

bool WindowManager_Init(WindowManager* manager) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR("Failed to initialize SDL.\n");
        return false;
    }

    if (TTF_Init()) {
        LOG_ERROR("Failed to initialize SDL_ttf.\n");
        SDL_Quit();
        return false;
    }

    manager->window = SDL_CreateWindow("Table Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!manager->window) {
        LOG_ERROR("Failed to create window.\n");
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    manager->renderer = SDL_CreateRenderer(manager->window, -1, SDL_RENDERER_ACCELERATED);
    if (!manager->renderer) {
        LOG_ERROR("Failed to create renderer.\n");
        SDL_DestroyWindow(manager->window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    manager->fonts = malloc(sizeof(Fonts));
    if(!manager->fonts){
        LOG_ERROR("Failed to allocate memory for Fonts.\n");
        SDL_DestroyWindow(manager->window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    manager->fonts->mediumFont = TTF_OpenFont(FONT_PATH, FONT_MEDIUM_SIZE);
    manager->fonts->smallFont = TTF_OpenFont(FONT_PATH, FONT_SMALL_SIZE);
    if (!manager->fonts->mediumFont || !manager->fonts->smallFont) {
        LOG_ERROR("Failed to load font.\n");
        SDL_DestroyRenderer(manager->renderer);
        SDL_DestroyWindow(manager->window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void WindowManager_Cleanup(WindowManager* manager) {
    if (manager->fonts) {
        TTF_CloseFont(manager->fonts->mediumFont);
        TTF_CloseFont(manager->fonts->smallFont);
    }

    free(manager->fonts);

    if (manager->renderer) {
        SDL_DestroyRenderer(manager->renderer);
    }
    if (manager->window) {
        SDL_DestroyWindow(manager->window);
    }
    TTF_Quit();
    SDL_Quit();
}