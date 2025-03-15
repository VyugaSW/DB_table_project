#include "table_manager.h"
#include "window_manager.h"
#include "notifyError.h"
#include "dbtable.h"
#include <stdio.h>
#include <string.h>


void TableManager_HandleHeaderClick(SDL_Point mousePos, Button* headerButtons, size_t count, Table* table, SortState* sortState) {
    for (size_t i = 0; i < count; i++) {
        if (SDL_PointInRect(&mousePos, &headerButtons[i].rect)) {
            if (sortState->sortColumn == i) {
                sortState->ascending = !sortState->ascending;
            } else {
                sortState->sortColumn = i;
                sortState->ascending = true;
            }
            
            switch (i) {
                case 0: 
                    table_sort(table, sortState->ascending, ID);
                    break;
                case 1: 
                    table_sort(table, sortState->ascending, NAME);
                    break;
                case 2: 
                    table_sort(table, sortState->ascending, BOOK_DATE);
                    break;
                case 3: 
                    table_sort(table, sortState->ascending, PRICE);
                    break;
                default:
                    break;
            }
            break;
        }
    }
}

void TableManager_RenderTable(SDL_Renderer* renderer, TTF_Font* font, Table* table, Button *headerButtons, int scrollOfsset) {
    SDL_Color textColor = {255, 255, 255, 255};

    ButtonManager_InitHeaderButtons(headerButtons, scrollOfsset);
    ButtonManager_RenderButtons(renderer, font, headerButtons, NUM_HEADERS_BUTTON);
    
    // Render table data
    int yOffset = 100 - scrollOfsset; // Initial y-position for data
    for (size_t i = 0; i < table->count; i++) {
        Book* book = table->books_arr[i];

        char row[256];
        snprintf(row, sizeof(row), "%zu  \"%s\" |%02u.%02u.%04u| %.2f",
                 book->id, book->name, book->date->day, book->date->month, book->date->year, book->price);

        SDL_Surface* rowSurface = TTF_RenderText_Solid(font, row, textColor);
        if (!rowSurface) {
            LOG_ERROR("Failed to render table row");
            continue;
        }

        SDL_Texture* rowTexture = SDL_CreateTextureFromSurface(renderer, rowSurface);
        if (!rowTexture) {
            LOG_ERROR("Failed to create texture from surface");
            SDL_FreeSurface(rowSurface);
            continue;
        }

        int rowWidth = rowSurface->w;
        int rowHeight = rowSurface->h;
        SDL_FreeSurface(rowSurface);

        SDL_Rect rowRect = {50, yOffset, rowWidth, rowHeight};
        SDL_RenderCopy(renderer, rowTexture, NULL, &rowRect);

        SDL_DestroyTexture(rowTexture);

        yOffset += rowHeight + 10; 
    }

    SDL_RenderPresent(renderer);
}

bool TableManager_HandleTextInput(SDL_Renderer* renderer, TTF_Font* font, const char* prompt, char* input, size_t maxInputLength) {
    bool inputActive = true;
    size_t index = 0; 
    
    while (inputActive) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            } 
            else if (event.type == SDL_TEXTINPUT) {
                if (index + strlen(event.text.text) < maxInputLength - 1) {
                    strcpy(input + index, event.text.text);
                    index += strlen(event.text.text);
                    input[index] = '\0';
                }
                else {
                    LOG_ERROR("Input buffer overflow");
                }
            } 
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    input[index] = '\0';
                    inputActive = false;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0) {
                    // Deleting last char with UTF-8
                    while (index > 0 && (input[--index] & 0xC0) == 0x80) {}
                    input[index] = '\0';
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) return false; 
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%s: %s", prompt, input);

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, buffer, textColor);  

        if (!surface) {
            LOG_ERROR("Failed to render input text");
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        
        if (!texture) {
            LOG_ERROR("Failed to create texture from surface");
            SDL_FreeSurface(surface);
            continue;
        }

        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_FreeSurface(surface);

        SDL_Rect dstRect = {50, 50, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);
    }

    return true;
}

