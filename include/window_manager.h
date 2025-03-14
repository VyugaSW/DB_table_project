#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 900       /**< Width of the application window. */
#define WINDOW_HEIGHT 600      /**< Height of the application window. */
#define FONT_MEDIUM_SIZE 22    /**< Size of the medium font. */
#define FONT_SMALL_SIZE 14     /**< Size of the small font. */
#define FONT_PATH "fonts/arial.ttf" /**< Path to the font file. */

/**
 * @brief Structure representing fonts used in the application.
 */
typedef struct {
    TTF_Font *mediumFont; /**< Pointer to the medium-sized font. */
    TTF_Font *smallFont;  /**< Pointer to the small-sized font. */
} Fonts;

/**
 * @brief Structure representing the window manager.
 *
 * This structure holds the SDL window, renderer, and fonts used in the application.
 */
typedef struct {
    SDL_Window *window;   /**< Pointer to the SDL window. */
    SDL_Renderer *renderer; /**< Pointer to the SDL renderer. */
    Fonts *fonts;         /**< Pointer to the Fonts structure. */
} WindowManager;

/**
 * @brief Initializes the SDL window, renderer, and fonts.
 *
 * @param[in,out] manager Pointer to the WindowManager object to initialize.
 * @return true if initialization is successful, false otherwise.
 */
bool WindowManager_Init(WindowManager* manager);

/**
 * @brief Cleans up and frees resources used by the window manager.
 *
 * @param[in] manager Pointer to the WindowManager object to clean up.
 */
void WindowManager_Cleanup(WindowManager* manager);
