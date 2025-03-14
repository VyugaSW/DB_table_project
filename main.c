#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "dbtable.h"
#include "window_manager.h"
#include "diagram_manager.h"
#include "table_manager.h"
#include "dbfile.h"
#include "button_manager.h"

int main(int argc, char* argv[]) {
    #ifdef _WIN32
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
    #endif

    freopen("data/logs.txt", "w", stderr);

    WindowManager windowManager;
    if (!WindowManager_Init(&windowManager)) return 1;

    Button menuButtons[NUM_MENU_BUTTONS];
    ButtonManager_InitMenuButtons(menuButtons);

    Button headerButtons[NUM_HEADERS_BUTTON];
    
    Table *table = init_table();
    if(!table) return 1;

    fread_table(table, DEFAULT_TB_PATH); // TESTING

    int bins[NUM_BINS] = {0}; // for diagrams
    bool running = true;
    bool waitingForReturn = false;
    int scrollOffset = 0;
    size_t indexOption = 999;
    SortState sortState = {0,true};

    while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;

                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE){ 
                            waitingForReturn = false;
                            if(indexOption == 0) sortElements_table(table,true,ID);
                        }
                        break;

                    case SDL_MOUSEBUTTONDOWN: {

                        SDL_Point mousePos = {event.button.x, event.button.y};
                        if(indexOption == 0)
                            TableManager_HandleHeaderClick(mousePos, headerButtons, NUM_HEADERS_BUTTON, table, &sortState);

                        for (size_t i = 0; i < NUM_MENU_BUTTONS; i++) {
                            if (SDL_PointInRect(&mousePos, &menuButtons[i].rect) && !waitingForReturn) {
                                printf("Button clicked: %s\n", menuButtons[i].label);
                                indexOption = i;

                                switch (i) {
                                    case 0: // Show table
                                        waitingForReturn = true;
                                        scrollOffset = 0;
                                        break;

                                    case 1: { // Add element
                                        char input_name[50] = {0};
                                        char input_price[8] = {0};
                                        char input_date[12] = {0};

                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter book name", input_name, sizeof(input_name))) break;
                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter book price", input_price, sizeof(input_price))) break;
                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter book date", input_date, sizeof(input_date))) break;

                                        char* endPtr;
                                        double price = strtod(input_price, &endPtr);
                                        if (*endPtr != '\0' || input_price == endPtr || errno == ERANGE) {
                                            printf("Price of adding book was converted to 0.0. Check input\n");
                                            price = 0.1;
                                        }

                                        Book* input_book = init_book(input_name, stringToDate(input_date), price);
                                        addElement_table(table, input_book);
                                        printf("Added\n");
                                        free(input_book);
                                        break;
                                    }

                                    case 2: { // Delete element
                                        char input_id[8] = {0};
                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter book id", input_id, sizeof(input_id))) break;

                                        char* endPtr;
                                        size_t id = strtoull(input_id, &endPtr, 10);
                                        if (input_id != endPtr && errno != ERANGE) {
                                            delElement_table(table, id);
                                            printf("Deleted\n");
                                        }
                                        break;
                                    }

                                    case 3: // Tab chart
                                    case 4: // Pie chart
                                        waitingForReturn = true;
                                        groupDataIntoBins((const Book**)table->books_arr, table->count, bins);
                                        break;

                                    case 5: { // Save table
                                        char input_path[255] = {0};
                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter path for saving to .txt file", input_path, sizeof(input_path))) break;

                                        fwrite_table(table, input_path);
                                        printf("Saved (check log.txt)\n");
                                        break;
                                    }

                                    case 7: { // Load table
                                        char input_path[255] = {0};
                                        if (!TableManager_HandleTextInput(windowManager.renderer, windowManager.fonts->mediumFont, "Enter path for loading to .txt file", input_path, sizeof(input_path))) break;

                                        fread_table(table, input_path);
                                        printf("Loaded (check log.txt)\n");
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }

                    case SDL_MOUSEWHEEL:
                        if (waitingForReturn) {
                            scrollOffset -= event.wheel.y * 20;
                            if (scrollOffset < 0) scrollOffset = 0;
                        }
                        break;
                }
            }

            SDL_SetRenderDrawColor(windowManager.renderer, 30, 30, 30, 255);
            SDL_RenderClear(windowManager.renderer);

            if (!waitingForReturn) {
                ButtonManager_RenderButtons(windowManager.renderer, windowManager.fonts->mediumFont, menuButtons, NUM_MENU_BUTTONS);
            } else {
                switch (indexOption) {
                    case 0:
                        TableManager_RenderTable(windowManager.renderer, windowManager.fonts->mediumFont, table, headerButtons, scrollOffset);
                        break;
                    case 3:
                        DiagramManager_RenderBarChart(windowManager.renderer, windowManager.fonts, bins);
                        break;
                    case 4:
                        DiagramManager_RenderPieChart(windowManager.renderer, windowManager.fonts, bins);
                        break;
                    default:
                        break;
                }
            }

        SDL_RenderPresent(windowManager.renderer);
    }

    WindowManager_Cleanup(&windowManager);
    free_table(table);

    #ifdef _WIN32
        FreeConsole();
    #endif
        return 0;
}