#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "dbtable.h"
#include "window_manager.h"

#define NUM_BINS 10     /**< Number of bins for grouping data. */
#define BIN_SIZE 10     /**< Size of each bin. */

extern SDL_Color binColors[]; /**< Array of colors for each bin. */
extern const char *legendText[]; /**< Array of legend text for each bin. */

/**
 * @brief Renders a bar chart based on the provided bin data.
 *
 * @param[in] renderer The SDL renderer used to draw the chart.
 * @param[in] fonts    Pointer to the Fonts structure containing loaded fonts.
 * @param[in] bins     Array of integers representing the count of elements in each bin.
 */
void DiagramManager_RenderBarChart(SDL_Renderer* renderer, Fonts *fonts, int *bins);

/**
 * @brief Renders a pie chart based on the provided bin data.
 *
 * @param[in] renderer The SDL renderer used to draw the chart.
 * @param[in] fonts    Pointer to the Fonts structure containing loaded fonts.
 * @param[in] bins     Array of integers representing the count of elements in each bin.
 */
void DiagramManager_RenderPieChart(SDL_Renderer *renderer, Fonts *fonts, int *bins);

/**
 * @brief Renders a legend for the charts.
 *
 * @param[in] renderer The SDL renderer used to draw the legend.
 * @param[in] font     The TTF font used for rendering text.
 * @param[in] xOffset  The x-coordinate offset for the legend.
 * @param[in] yOffset  The y-coordinate offset for the legend.
 */
void DiagramManager_RenderLegend(SDL_Renderer *renderer, TTF_Font *font, int xOffset, int yOffset);

/**
 * @brief Groups book data into bins based on price.
 *
 * @param[in] values Array of pointers to Book objects.
 * @param[in] count  Number of books in the array.
 * @param[out] bins  Array to store the count of books in each bin.
 */
void groupDataIntoBins(const Book** values, size_t count, int *bins);