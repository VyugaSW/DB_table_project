#include "button_manager.h"


void ButtonManager_InitMenuButtons(Button *buttons) {
    const char *labels[] = {"Show table", "Add element", "Delete element", "Column chart", "Circular Chart", "Save table", "Load table"};
    int y = 65;
    for (size_t i = 0; i < NUM_MENU_BUTTONS; i++) {
        buttons[i].rect = (SDL_Rect){(WINDOW_WIDTH-MENU_BUTTON_WIDTH)/2, y, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT};
        buttons[i].label = labels[i];
        buttons[i].textColor = (SDL_Color){255, 255, 255, 255};
        buttons[i].bgColor = (SDL_Color){50, 150, 255, 255};
        y += MENU_BUTTON_HEIGHT+20;
    }
}

void ButtonManager_InitHeaderButtons(Button *buttons, int scrollOffset) {
    const char *labels[] = {"ID", "Name", "Date", "Price"};
    int x = 50;
    for (size_t i = 0; i < NUM_MENU_BUTTONS; i++) {
        buttons[i].rect = (SDL_Rect){x, 50 - scrollOffset, HEADER_BUTTON_WIDTH, HEADER_BUTTON_HEIGHT};
        buttons[i].label = labels[i];
        buttons[i].textColor = (SDL_Color){255, 255, 255, 255};
        buttons[i].bgColor = (SDL_Color){0, 0, 0, 255};
        x += HEADER_BUTTON_WIDTH;
    }
}

void ButtonManager_RenderButtons(SDL_Renderer* renderer, TTF_Font* font, Button buttons[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        // Render button background
        SDL_SetRenderDrawColor(renderer, buttons[i].bgColor.r, buttons[i].bgColor.g, buttons[i].bgColor.b, buttons[i].bgColor.a);
        SDL_RenderFillRect(renderer, &buttons[i].rect);

        // Render button text
        SDL_Surface* surface = TTF_RenderText_Solid(font, buttons[i].label, buttons[i].textColor);

        if (!surface) {
            LOG_ERROR("Failed to render button text");
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

        SDL_Rect dstRect = {buttons[i].rect.x + (buttons[i].rect.w - textWidth) / 2,
                            buttons[i].rect.y + (buttons[i].rect.h - textHeight) / 2,
                            textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        SDL_DestroyTexture(texture);

        // Button frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &buttons[i].rect);
    }
}