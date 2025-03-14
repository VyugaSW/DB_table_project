#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "dbtable.h"
#include "window_manager.h"

#define NUM_MENU_BUTTONS 7  /**< Number of menu buttons. */
#define MENU_BUTTON_WIDTH 200 /**< Width of a menu button. */
#define MENU_BUTTON_HEIGHT 40 /**< Height of a menu button. */

#define NUM_HEADERS_BUTTON 4 /**< Number of header buttons. */
#define HEADER_BUTTON_HEIGHT 30 /**< Height of a header button. */
#define HEADER_BUTTON_WIDTH 165 /**< Width of a header button. */

/**
 * @brief Structure representing a button.
 */
typedef struct Button {
    SDL_Rect rect;       /**< Rectangle defining the button's position and size. */
    const char* label;   /**< Text label displayed on the button. */
    SDL_Color textColor; /**< Color of the button's text. */
    SDL_Color bgColor;   /**< Background color of the button. */
} Button;

/**
 * @brief Initializes the menu buttons.
 *
 * @param[out] buttons  Array of Button structures to initialize.
 */
void ButtonManager_InitMenuButtons(Button *buttons);

/**
 * @brief Initializes the header buttons.
 *
 * @param[out] buttons      Array of Button structures to initialize.
 * @param[in]  scrollOffset Vertical scroll offset for button positioning.
 */
void ButtonManager_InitHeaderButtons(Button *buttons, int scrollOffset);

/**
 * @brief Renders the buttons on the screen.
 *
 * @param[in] renderer  The SDL renderer used to draw the buttons.
 * @param[in] font      The TTF font used for button text.
 * @param[in] buttons   Array of Button structures to render.
 * @param[in] count     Number of buttons to render.
 */
void ButtonManager_RenderButtons(SDL_Renderer* renderer, TTF_Font* font, Button buttons[], size_t count);