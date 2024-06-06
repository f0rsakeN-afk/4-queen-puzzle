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
    SDL_Texture *backgroundHome = IMG_LoadTexture(renderer, "assets/bg.jpg");
    SDL_Texture *solution1 = IMG_LoadTexture(renderer, "assets/solu1.jpg");
    SDL_Texture *solution2 = IMG_LoadTexture(renderer, "assets/solu2.jpg");
    SDL_Texture *whiteQueen = IMG_LoadTexture(renderer, "assets/white.jpg");
    SDL_Texture *blackQueen = IMG_LoadTexture(renderer, "assets/black.jpg");

    if (!backgroundHome || !solution1 || !solution2 || !whiteQueen || !blackQueen)
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
                    if (x > 870 && x <= 970 && y > 550 && y <= 600)
                    {
                        state = PLAY;
                    }
                    else if (x >= 820 && x <= 1000 && y >= 610 && y <= 653)
                    {
                        state = INSTRUCTIONS;
                    }
                    else if (x >= 865 && x <= 1000 && y >= 690 && y <= 743)
                    {
                        state = ABOUT;
                    }
                }
                else if (state == INSTRUCTIONS || state == ABOUT)
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
            /*   SDL_SetRenderDrawColor(renderer, 8, 76, 97, 255);
              SDL_RenderClear(renderer); */
            SDL_RenderCopy(renderer, backgroundHome, NULL, NULL);
            renderText(renderer, "Welcome to 4 Queen Puzzle", 600, 50, 55, {214, 50, 48, 255});
            renderText(renderer, "Play", 870, 550, 45, {255, 255, 255, 255});
            renderText(renderer, "Instructions", 820, 620, 45, {255, 255, 255, 255});
            renderText(renderer, "About", 865, 690, 45, {255, 255, 255, 255});
        }
        else if (state == INSTRUCTIONS)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 129, 255);
            SDL_RenderClear(renderer);
            SDL_Rect rect1 = {1000, 120, 300, 300};
            SDL_Rect rect2 = {50, 400, 300, 300};
            SDL_RenderCopy(renderer, solution1, NULL, &rect1);
            SDL_RenderCopy(renderer, solution2, NULL, &rect2);
            renderText(renderer, "1. No Two Queens Should Present In The Same Row.", 200, 200, 3, {255, 255, 0, 255});
            renderText(renderer, "2. No Two Queens Should Present In The Same Column.", 200, 250, 3, {255, 255, 0, 255});
            renderText(renderer, "3. No Two Queens Should Be Diagonally Attacked.", 200, 300, 3, {255, 255, 0, 255});
            renderText(renderer, "4. There Might Be two Combinations, So, for one combination", 380, 450, 3, {255, 255, 0, 255});
            renderText(renderer, "Black Queen Which Appears On the Right-click of Mouse,", 380, 500, 3, {255, 255, 0, 255});
            renderText(renderer, "And For Another Their occurs the White Queen on Left-click of Mouse", 380, 550, 3, {255, 255, 0, 255});
            renderText(renderer, "While Clicking on the Right Position's combination On The Chess Board.", 380, 600, 3, {255, 255, 0, 255});
            renderText(renderer, "HOME", 1135, 655, 5, {255, 255, 255, 255});
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 245, 255);
            SDL_RenderClear(renderer);
            SDL_Rect boardRect = {300, 100, 400, 400};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &boardRect);
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    SDL_Rect cellRect = {300 + i * 100, 100 + j * 100, 100, 100};
                    SDL_RenderDrawRect(renderer, &cellRect);
                    if (arr[i][j] == 1)
                    {
                        SDL_Texture *queen = (i + j) % 2 == 0 ? whiteQueen : blackQueen;
                        SDL_Rect dstrect = {300 + i * 100 + 2, 100 + j * 100 + 2, 96, 96};
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
