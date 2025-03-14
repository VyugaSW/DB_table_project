#include "table_manager.h"
#include "diagram_manager.h"
#include "window_manager.h"
#include "notifyError.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

SDL_Color binColors[NUM_BINS] = {
    {255, 0, 0, 255},     // Red (0–10)
    {0, 255, 0, 255},     // Green (10–20)
    {0, 0, 255, 255},     // Dark blue (20–30)
    {255, 255, 0, 255},   // Yellow (30–40)
    {255, 0, 255, 255},   // Purpure (40–50)
    {0, 255, 255, 255},   // Blue (50–60)
    {128, 0, 128, 255},   // Phiolite (60–70)
    {255, 165, 0, 255},   // Orange (70-80)
    {128, 128, 128, 255}, // Gray (80–90)
    {0, 0, 0, 255}        // Black (90+)
};

const char *legendTexts[NUM_BINS] = {
    "0 - 10", "10 - 20", "20 - 30", "30 - 40", "40 - 50",
    "50 - 60", "60 - 70", "70 - 80", "80 - 90", "90+"
};

void groupDataIntoBins(const Book** values, size_t count, int *bins) {
    if(!values || !bins){
        LOG_ERROR("Grouping data into bins went wrong.\n");
        return;
    }

    memset(bins, 0, sizeof(int)*NUM_BINS);

    for (size_t i = 0; i < count; i++) {
        double price = values[i]->price;
        int binIndex = (int)(price / (BIN_SIZE+1)); 

        if (binIndex >= NUM_BINS) {
            binIndex = NUM_BINS - 1;
        }

        bins[binIndex]++; 
    }
}

void DiagramManager_RenderBarChart(SDL_Renderer* renderer, Fonts *fonts, int *bins) {
    if(!bins){
        LOG_ERROR("Rendering bar chart is false.\n");
        return;
    }

    int chartWidth = WINDOW_WIDTH / 2;
    int barSpacing = 1; 
    int barWidth = (chartWidth - (NUM_BINS - 1) * barSpacing) / NUM_BINS;

    int totalElements = 0;
    int maxBinValue = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        if (bins[i] > maxBinValue) {
            maxBinValue = bins[i];
        }
        totalElements+=bins[i];
    }

    if (maxBinValue == 0) return;

    int maxBarHeight = WINDOW_HEIGHT / 2;

    int xOffset = (WINDOW_WIDTH - chartWidth) / 2;

    for (size_t i = 0; i < NUM_BINS; i++) {
        int barHeight = (int)((bins[i] * maxBarHeight) / maxBinValue) + 5;

        SDL_Rect barRect = {
            xOffset + ((int)i * (barWidth + barSpacing)), 
            WINDOW_HEIGHT - barHeight,     
            barWidth - 10,                 
            barHeight                      
        };

        SDL_SetRenderDrawColor(renderer, binColors[i].r, binColors[i].g, binColors[i].b, binColors[i].a);
        SDL_RenderFillRect(renderer, &barRect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &barRect);

        // Calculatin percents 
        float percentage = ((float)bins[i] / (float)totalElements) * 100;
        char percentageText[16];
        snprintf(percentageText, sizeof(percentageText), "%.1f%%", percentage);

        // Render percentage text
        SDL_Surface *textSurface = TTF_RenderText_Solid(fonts->smallFont, percentageText, (SDL_Color){255, 255, 255, 255});
        if (!textSurface) {
            LOG_ERROR("Failed to render percentage text.\n");
            continue;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            LOG_ERROR("Failed to create texture from surface.\n");
            SDL_FreeSurface(textSurface);
            continue;
        }

        SDL_Rect textRect = {
            barRect.x + (barRect.w - textSurface->w) / 2,  
            barRect.y - textSurface->h - 5,                
            textSurface->w,
            textSurface->h
        };

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    
    DiagramManager_RenderLegend(renderer, fonts->mediumFont, 25, 50);
}

void DiagramManager_RenderLegend(SDL_Renderer *renderer, TTF_Font *font, int xOffset, int yOffset) {
    if (!renderer || !font) {
        LOG_ERROR("Rendering legend failed: renderer or font is NULL.\n");
        return;
    }

    const int legendSquareSize = 20;  
    const int legendTextOffset = 30;  
    const int legendSpacing = 30;

    // Render price title 
    SDL_Surface *priceSurface = TTF_RenderText_Solid(font, "Price", (SDL_Color){255, 255, 255, 255});
    if (!priceSurface) {
        LOG_ERROR("Failed to render 'Price' text.\n");
        return;
    }

    SDL_Texture *priceTexture = SDL_CreateTextureFromSurface(renderer, priceSurface);
    if (!priceTexture) {
        LOG_ERROR("Failed to create texture from surface.\n");
        SDL_FreeSurface(priceSurface);
        return;
    }

    SDL_Rect priceRect = {
        xOffset,                              
        yOffset - priceSurface->h - 10,        
        priceSurface->w,                       
        priceSurface->h                        
    };
    SDL_RenderCopy(renderer, priceTexture, NULL, &priceRect);

    SDL_FreeSurface(priceSurface);
    SDL_DestroyTexture(priceTexture);

    for (int i = 0; i < NUM_BINS; i++) {
        SDL_Rect squareRect = {
            xOffset,                              
            yOffset + i * legendSpacing,          
            legendSquareSize,                     
            legendSquareSize                      
        };
        SDL_SetRenderDrawColor(renderer, binColors[i].r, binColors[i].g, binColors[i].b, binColors[i].a);
        SDL_RenderFillRect(renderer, &squareRect);

        // Render legend text
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, legendTexts[i], (SDL_Color){255, 255, 255, 255});
        if (!textSurface) {
            LOG_ERROR("Failed to render legend text.\n");
            continue;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            LOG_ERROR("Failed to create texture from surface.\n");
            SDL_FreeSurface(textSurface);
            continue;
        }

        SDL_Rect textRect = {
            xOffset + legendTextOffset,           
            yOffset + i * legendSpacing,          
            textSurface->w,                       
            textSurface->h                        
        };

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void DiagramManager_RenderPieChart(SDL_Renderer *renderer, Fonts *fonts, int *bins) {
    if(!bins){
        LOG_ERROR("Rendering bar chart is false.\n");
        return;
    }

    int totalElements = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        totalElements+=bins[i];
    }

    float startAngle = 0.0f;

    float centerX = (float)(WINDOW_WIDTH / 2);  
    float centerY = (float)(WINDOW_HEIGHT / 2); 
    float radius = (float)(WINDOW_WIDTH / 4);   

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < NUM_BINS; i++) {

        if(bins[i] == 0)
            continue;

        // Calculate the angle for the current sector
        float angle = 360.0f * ((float)bins[i] / (float)totalElements);

        float endAngle = startAngle + angle;

        // Number of triangles for the sector (more triangles = smoother curve)
        int numTriangles = (int)(angle / 2.0f);  // One triangle per 2 degrees
        if (numTriangles < 1) numTriangles = 1;

        // Allocate memory for vertices
        SDL_Vertex vertices[numTriangles+2];  // +2 for center and last point
        if (!vertices) {
            LOG_ERROR("Failed to allocate memory for vertices.\n");
            return;
        }

        int vertexCount = 0;

        // First vertex: center of the circle
        vertices[vertexCount].position.x = centerX;
        vertices[vertexCount].position.y = centerY;
        vertices[vertexCount].color = binColors[i];  
        vertexCount++;

        // Draw triangles for the sector
        for (int j = 0; j <= numTriangles; j++) {
            float currentAngle = startAngle + (endAngle - startAngle) * ((float)j / (float)numTriangles);
            float rad = currentAngle * (float)M_PI / 180.0f;

            // Vertex on the circumference
            vertices[vertexCount].position.x = centerX + radius * cosf(rad);
            vertices[vertexCount].position.y = centerY + radius * sinf(rad);
            vertices[vertexCount].color = binColors[i];  // Sector color
            vertexCount++;

            // Draw the triangle (center + two points on the circumference)
            if (vertexCount >= 3) {
                SDL_RenderGeometry(renderer, NULL, &vertices[0], vertexCount, NULL, 0);
                vertices[1] = vertices[vertexCount - 1];  // Next triangle starts from the last point
                vertexCount = 2;
            }
        }

        // Render percentage text
        float percentage = ((float)bins[i] / (float)totalElements) * 100.0f;
        char percentageText[16];
        snprintf(percentageText, sizeof(percentageText), "%.1f%%", percentage);

        float midAngle = startAngle + angle / 2.0f;
        float textRad = midAngle * (float)M_PI / 180.0f;
        int textX = (int)roundf(centerX + (radius + 20.0f) * cosf(textRad));  
        int textY = (int)roundf(centerY + (radius + 20.0f) * sinf(textRad));  

        SDL_Surface *textSurface = TTF_RenderText_Solid(fonts->smallFont, percentageText, (SDL_Color){255, 255, 255, 255});
        if (!textSurface) {
            LOG_ERROR("Failed to render text for pie chart.\n");
            continue;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            LOG_ERROR("Failed to create texture for pie chart.\n");
            SDL_FreeSurface(textSurface);
            continue;
        }

        SDL_Rect textRect = {textX - textSurface->w / 2, textY - textSurface->h / 2, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        startAngle += angle;
    }

    DiagramManager_RenderLegend(renderer, fonts->mediumFont, 25, 50);
}