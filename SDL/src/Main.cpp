#include <iostream>
#include "Queen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

enum GameState
{
    HOME,
    INSTRUCTIONS,
    ABOUT,
    PLAY
};

int main()
{

    if (SDL_Init(SDL_INIT_VIDEO < 0))
    {
        cout << "SDL could not be initialized!!" << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("4 Queen Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 786, SDL_WINDOW_SHOWN);

    if (!window)
    {
        cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cout << "Renderer could not be initialized! SDL_image Error:" << IMG_GetError() << endl;
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

    SDL_Texture *frontbg1 = IMG_LoadTexture(renderer, "");
    SDL_Texture *frontbg2 = IMG_LoadTexture(renderer, "");
    SDL_Texture *instruction = IMG_LoadTexture(renderer, "");
    SDL_Texture *solution1 = IMG_LoadTexture(renderer, "");
    SDL_Texture *solution2 = IMG_LoadTexture(renderer, "");
    SDL_Texture *about = IMG_LoadTexture(renderer, "");
    SDL_Texture *finalbg = IMG_LoadTexture(renderer, "");
    SDL_Texture *whiteQueen = IMG_LoadTexture(renderer, "");
    SDL_Texture *blackQueen = IMG_LoadTexture(renderer, "");

    if (!frontbg1 || !frontbg2 || !instruction || !solution1 || !solution2 || !about || !finalbg || !whiteQueen || !blackQueen)
    {
        cout << "Failed to load images SDL_Error" << SDL_GetError() << endl;
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GameState state = HOME;
    ~bool quit = false;
    SDL_Event e;
    Queen s;

    int **arr = new int *[4];
    for (int i = 0; i < 4; i++)
    {
        arr[i] = new int[4]();
    }

    SDL_DestroyTexture(frontbg1);
    SDL_DestroyTexture(frontbg2);
    SDL_DestroyTexture(instruction);
    SDL_DestroyTexture(solution1);
    SDL_DestroyTexture(solution2);
    SDL_DestroyTexture(about);
    SDL_DestroyTexture(finalbg);
    SDL_DestroyTexture(whiteQueen);
    SDL_DestroyTexture(blackQueen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}