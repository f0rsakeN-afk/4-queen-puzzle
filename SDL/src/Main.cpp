#include <iostream>
#include "Queen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

using namespace std;

enum GameState
{
    HOME,
    INSTRUCTIONS,
    ABOUT,
    PLAY
};

void renderText(SDL_Renderer *renderer, const char *message, int x, int y, int size, SDL_Color color)
{
    TTF_Font *font = TTF_OpenFont("assets/nunito.ttf", size);
    if (!font)
    {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, message, color);
    if (!surface)
    {
        cout << "Failed to create surface: " << TTF_GetError() << endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        cout << "Failed to create texture: " << SDL_GetError() << endl;
    }

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not be initialized!!" << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("4 Queen Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (!window)
    {
        cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cout << "Renderer could not be initialized! SDL_Error:" << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cout << "SDL_image could not be initialized! SDL_image Error:" << IMG_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *playBG = IMG_LoadTexture(renderer, "assets/playBG.jpg");
    SDL_Texture *backgroundHome = IMG_LoadTexture(renderer, "assets/bg.jpg");
    SDL_Texture *solution1 = IMG_LoadTexture(renderer, "assets/solu1.jpg");
    SDL_Texture *solution2 = IMG_LoadTexture(renderer, "assets/solu2.jpg");
    SDL_Texture *whiteQueen = IMG_LoadTexture(renderer, "assets/white.jpg");
    SDL_Texture *blackQueen = IMG_LoadTexture(renderer, "assets/black.jpg");

    if (!playBG || !backgroundHome || !solution1 || !solution2 || !whiteQueen || !blackQueen)
    {
        cout << "Failed to load images SDL_Error" << SDL_GetError() << endl;
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GameState state = HOME;
    bool quit = false;
    SDL_Event e;
    Queen s;

    int **arr = new int *[4];
    for (int i = 0; i < 4; i++)
    {
        arr[i] = new int[4]();
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                cout << "Mouse clicked at (" << x << "," << y << ")";
                if (state == HOME)
                {
                    if (x > 880 && x <= 970 && y > 530 && y <= 580)
                    {
                        state = PLAY;
                    }
                    else if (x >= 780 && x <= 1200 && y >= 581 && y <= 630)
                    {
                        state = INSTRUCTIONS;
                    }
                    else if (x >= 865 && x <= 1000 && y >= 631 && y <= 680)
                    {
                        state = ABOUT;
                    }
                }
                else if (state == INSTRUCTIONS || state == ABOUT || state == PLAY)
                {
                    if (x >= 1700 && x <= 1900 && y >= 940 && y <= 1000)
                    {
                        state = HOME;
                    }
                }
                else if (state == PLAY)
                {
                    if (e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT)
                    {
                        s = s.getTheCell(x, y);
                        if (s.x != 0 && s.y != 0)
                        {
                            int a = (s.x - 300) / 100;
                            int b = (s.y - 100) / 100;

                            if (arr[a][b] == 0)
                            {
                                arr[a][b] = 1;
                                SDL_Texture *queen = e.button.button == SDL_BUTTON_LEFT ? whiteQueen : blackQueen;
                                SDL_Rect dstrect = {s.x, s.y, 95, 95};
                                SDL_RenderCopy(renderer, queen, NULL, &dstrect);
                            }
                            else
                            {
                                cout << "Invalid move!!" << endl;
                            }
                        }
                    }
                    if (s.nQueen(arr, 0, 4))
                    {
                        renderText(renderer, "Congratulations", 950, 50, 5, {255, 0, 0, 255});
                    }
                }
            }
        }

        SDL_RenderClear(renderer);

        if (state == HOME)
        {
            SDL_RenderCopy(renderer, backgroundHome, NULL, NULL);
            renderText(renderer, "Welcome to 4 Queen Puzzle", 600, 50, 55, {214, 50, 48, 255});
            renderText(renderer, "PLAY", 880, 530, 45, {255, 255, 255, 255});
            renderText(renderer, "INSTRUCTIONS", 780, 580, 45, {255, 255, 255, 255});
            renderText(renderer, "ABOUT", 865, 630, 45, {255, 255, 255, 255});
        }
        else if (state == INSTRUCTIONS)
        {
            SDL_SetRenderDrawColor(renderer, 45, 30, 47, 255);
            SDL_RenderClear(renderer);
            SDL_Rect rect1 = {1200, 120, 300, 300};
            SDL_Rect rect2 = {400, 450, 300, 300};
            SDL_RenderCopy(renderer, solution1, NULL, &rect1);
            SDL_RenderCopy(renderer, solution2, NULL, &rect2);
            renderText(renderer, "N-Queen Problem Instructions:", 400, 100, 35, {247, 44, 37, 255});
            renderText(renderer, "1. Objective: Place N queens on an 4*4 chessboard.", 400, 150, 30, {255, 255, 0, 255});
            renderText(renderer, "2. No two queens should share the same row.", 400, 200, 30, {255, 255, 0, 255});
            renderText(renderer, "3. No two queens should share the same column.", 400, 250, 30, {255, 255, 0, 255});
            renderText(renderer, "4. No two queens should be on the same diagonal.", 400, 300, 30, {255, 255, 0, 255});
            renderText(renderer, "5. Click to place queens on the board.", 400, 350, 30, {255, 255, 0, 255});
            renderText(renderer, "6. Right-click to toggle between black and white queens.", 720, 470, 30, {255, 255, 0, 255});
            renderText(renderer, "7. Win by placing all N queens correctly.", 720, 520, 30, {255, 255, 0, 255});
            renderText(renderer, "8. Explore multiple solutions and strategies.", 720, 570, 30, {255, 255, 0, 255});
            renderText(renderer, "9. Use restart or undo options if available.", 720, 620, 30, {255, 255, 0, 255});
            renderText(renderer, "10. Enjoy the challenge and improve your skills.", 720, 670, 30, {255, 255, 0, 255});
            renderText(renderer, "Home", 1700, 940, 35, {19, 111, 99, 255});
        }

        else if (state == ABOUT)
        {
            // ABOUT Section
            SDL_SetRenderDrawColor(renderer, 39, 35, 58, 1);
            SDL_RenderClear(renderer);

            // Introduction
            renderText(renderer, "Welcome to the \"4 Queen Puzzle\" application!", 520, 20, 50, {255, 120, 90, 255});
            renderText(renderer, "This software aims to challenge users with an intriguing puzzle while providing an enjoyable gaming experience.", 100, 100, 35, {255, 255, 255, 255});

            // Development Team
            renderText(renderer, "Development Team:", 100, 170, 40, {255, 0, 0, 255});
            renderText(renderer, "Suraj Singh", 460, 170, 35, {227, 178, 60, 255});
            renderText(renderer, "Naresh Rajbanshi", 460, 210, 35, {227, 178, 60, 255});
            renderText(renderer, "Ramesh Mahato", 460, 250, 35, {227, 178, 60, 255});
            renderText(renderer, "Priya Mishra", 460, 290, 35, {227, 178, 60, 255});

            // Project Description
            renderText(renderer, "Project Description", 100, 360, 40, {255, 0, 0, 255});
            renderText(renderer, "The \"4 Queen Puzzle\" application is designed to stimulate logical thinking and problem-solving skills. The puzzle involves placing ", 100, 410, 30, {255, 255, 255, 255});
            renderText(renderer, "four queens on a chessboard in such a way that no two queens threaten each other. With multiple combinations to explore, users ", 100, 460, 30, {255, 255, 255, 255});
            renderText(renderer, "can test their strategic prowess and aim for optimal solutions.", 100, 510, 30, {255, 255, 255, 255});

            // Technology Stack
            renderText(renderer, "Technology Stack", 100, 570, 40, {255, 0, 0, 255});
            renderText(renderer, "The application was developed using modern technologies and tools, including:Programming Languages: C++,SDL.", 100, 620, 30, {255, 255, 255, 255});
            renderText(renderer, "Libraries: SDL_ttf (SDL TrueType Fonts), SDL_image", 100, 670, 30, {255, 255, 255, 255});

            // Features
            renderText(renderer, "Features", 100, 740, 40, {255, 0, 0, 255});
            renderText(renderer, "Intuitive User Interface: Simple and user-friendly interface for easy navigation.", 100, 790, 30, {255, 255, 255, 255});
            renderText(renderer, "Dynamic Puzzle Generation: Generate unique puzzles for endless gameplay.", 100, 840, 30, {255, 255, 255, 255});
            renderText(renderer, "Real-Time Feedback: Receive immediate feedback on moves and puzzle solutions.", 100, 890, 30, {255, 255, 255, 255});
            renderText(renderer, "Engaging Visuals: Eye-catching graphics and animations for an immersive experience.", 100, 940, 30, {255, 255, 255, 255});

            renderText(renderer, "Home", 1700, 940, 40, {19, 111, 99, 255});
        }
        else if (state == PLAY)
        {

            SDL_RenderCopy(renderer, playBG, NULL, NULL);

            SDL_Rect boardRect = {300, 100, 600, 600};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &boardRect);

            renderText(renderer, "Home", 1700, 940, 40, {19, 111, 99, 255});

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    SDL_Rect cellRect = {300 + i * 150, 100 + j * 150, 150, 150};

                    if ((i + j) % 2 == 0)
                    {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    }

                    SDL_RenderFillRect(renderer, &cellRect);

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &cellRect);

                    if (arr[i][j] == 1)
                    {
                        SDL_Texture *queen = (i + j) % 2 == 0 ? whiteQueen : blackQueen;
                        if (queen == NULL)
                        {
                            printf("Error: Queen texture is null\n");
                            continue;
                        }
                        SDL_Rect dstrect = {300 + i * 150 + 2, 100 + j * 150 + 2, 146, 146};
                        SDL_RenderCopy(renderer, queen, NULL, &dstrect);
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < 4; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    SDL_DestroyTexture(playBG);
    SDL_DestroyTexture(backgroundHome);
    SDL_DestroyTexture(solution1);
    SDL_DestroyTexture(solution2);
    SDL_DestroyTexture(whiteQueen);
    SDL_DestroyTexture(blackQueen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
