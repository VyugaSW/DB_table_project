#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "dbtable.h"
#include "button_manager.h"

/**
 * @brief Structure representing the sorting state of a table.
 */
typedef struct SortState {
    size_t sortColumn; /**< The column index by which the table is sorted. */
    bool ascending;    /**< Flag indicating whether the sorting is in ascending order. */
} SortState;

/**
 * @brief Handles a click on a table header.
 *
 * @param[in] mousePos      The position of the mouse click.
 * @param[in] headerButtons Array of header buttons.
 * @param[in] count         Number of header buttons.
 * @param[in,out] table     Pointer to the Table object.
 * @param[in,out] sortState Pointer to the SortState object to update.
 */
void TableManager_HandleHeaderClick(SDL_Point mousePos, Button* headerButtons, size_t count, Table* table, SortState* sortState);

/**
 * @brief Renders the table on the screen.
 *
 * @param[in] renderer      The SDL renderer used to draw the table.
 * @param[in] font          The TTF font used for rendering text.
 * @param[in] table         Pointer to the Table object to render.
 * @param[in] headerButtons Array of header buttons.
 * @param[in] scrollOffset  Vertical scroll offset for table rendering.
 */
void TableManager_RenderTable(SDL_Renderer* renderer, TTF_Font* font, Table *table, Button *headerButtons, int scrollOffset);

/**
 * @brief Handles text input from the user.
 *
 * @param[in] renderer       The SDL renderer used to display the input prompt.
 * @param[in] font           The TTF font used for rendering text.
 * @param[in] prompt         The prompt message to display.
 * @param[out] input         Buffer to store the user's input.
 * @param[in] maxInputLength Maximum length of the input buffer.
 * @return true if input was successfully captured, false if the user canceled or an error occurred.
 */
bool TableManager_HandleTextInput(SDL_Renderer* renderer, TTF_Font* font, const char* prompt, char* input, size_t maxInputLength);

