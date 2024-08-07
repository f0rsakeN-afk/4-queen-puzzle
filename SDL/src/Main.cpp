#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <SDL2/SDL_image.h>

using namespace std;

enum GameState
{
    HOME,
    INSTRUCTIONS,
    ABOUT,
    PLAY,
    CONGRATULATIONS
};

const int Screen_Width = 1920;
const int Screen_Height = 1080;
const int boardSize = 6;
int cellSize = 150;

int offsetX = (Screen_Width - boardSize * cellSize) / 2;
int offsetY = (Screen_Height - boardSize * cellSize) / 2;

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *playBG;
    SDL_Texture *backgroundHome;
    SDL_Texture *solution1;
    SDL_Texture *solution2;
    SDL_Texture *whiteQueen;
    SDL_Texture *blackQueen;
    vector<pair<int, int>> queens;
    GameState state;

    void init();
    void clean();
    void handleEvents();
    void update();
    void render();
    void renderText(const char *message, int x, int y, int size, SDL_Color color);
    void drawBoard();
    void drawQueens();
    bool isSafe(int row, int col);
    void handleMouseEvent(int x, int y);
};

Game::Game()
{
    init();
    state = HOME;
}

Game::~Game()
{
    clean();
}

void Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not be initialized!!" << SDL_GetError() << endl;
        exit(1);
    }

    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("6 Queen Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cout << "Renderer could not be initialized! SDL_Error:" << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cout << "SDL_image could not be initialized! SDL_image Error:" << IMG_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    playBG = IMG_LoadTexture(renderer, "assets/playBG.jpg");
    backgroundHome = IMG_LoadTexture(renderer, "assets/bg.jpg");
    solution1 = IMG_LoadTexture(renderer, "assets/solu1.png");
    whiteQueen = IMG_LoadTexture(renderer, "assets/white.jpg");
    blackQueen = IMG_LoadTexture(renderer, "assets/black.jpg");

    if (!playBG || !backgroundHome || !solution1 || !solution2 || !whiteQueen || !blackQueen)
    {
        cout << "Failed to load images SDL_Error" << SDL_GetError() << endl;
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void Game::clean()
{
    SDL_DestroyTexture(playBG);
    SDL_DestroyTexture(backgroundHome);
    SDL_DestroyTexture(solution1);
    SDL_DestroyTexture(solution2);
    SDL_DestroyTexture(whiteQueen);
    SDL_DestroyTexture(blackQueen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

void Game::renderText(const char *message, int x, int y, int size, SDL_Color color)
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

void Game::drawBoard()
{
    for (int row = 0; row < boardSize; ++row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            SDL_Rect cell;
            cell.x = offsetX + col * cellSize;
            cell.y = offsetY + row * cellSize;
            cell.w = cellSize;
            cell.h = cellSize;

            if ((row + col) % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &cell);
        }
    }
}

void Game::drawQueens()
{
    for (const auto &queen : queens)
    {
        SDL_Rect dst;
        dst.x = offsetX + queen.second * cellSize;
        dst.y = offsetY + queen.first * cellSize;
        dst.w = cellSize;
        dst.h = cellSize;
        SDL_RenderCopy(renderer, whiteQueen, NULL, &dst);
    }
}

bool Game::isSafe(int row, int col)
{
    for (const auto &queen : queens)
    {
        int qRow = queen.first;
        int qCol = queen.second;
        if (qRow == row || qCol == col || (abs(qRow - row) == abs(qCol - col)))
        {
            return false;
        }
    }
    return true;
}

void Game::handleMouseEvent(int x, int y)
{
    int row = (y - offsetY) / cellSize;
    int col = (x - offsetX) / cellSize;

    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
    {
        auto it = find(queens.begin(), queens.end(), make_pair(row, col));
        if (it != queens.end())
        {
            queens.erase(it);
        }
        else if (isSafe(row, col))
        {
            queens.push_back(make_pair(row, col));
        }
    }
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            state = HOME;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
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
            else if (state == INSTRUCTIONS || state == ABOUT || state == CONGRATULATIONS)
            {
                if (x >= 1700 && x <= 1900 && y >= 940 && y <= 1000)
                {
                    state = HOME;
                }
            }
            else if (state == PLAY)
            {
                handleMouseEvent(x, y);
                if (x >= 1700 && x <= 1900 && y >= 940 && y <= 1000)
                {
                    state = HOME;
                }
            }
        }
    }
}

void Game::update()
{
    if (state == PLAY)
    {
        if (queens.size() == boardSize)
        {
            bool solved = true;
            for (int i = 0; i < boardSize; ++i)
            {
                for (int j = i + 1; j < boardSize; ++j)
                {
                    if (queens[i].first == queens[j].first ||
                        queens[i].second == queens[j].second ||
                        abs(queens[i].first - queens[j].first) == abs(queens[i].second - queens[j].second))
                    {
                        solved = false;
                        break;
                    }
                }
                if (!solved)
                    break;
            }
            if (solved)
            {
                state = CONGRATULATIONS;
            }
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    if (state == HOME)
    {
        SDL_RenderCopy(renderer, backgroundHome, NULL, NULL);
        renderText("Welcome to 6 Queen Puzzle", 600, 50, 55, {214, 50, 48, 255});
        renderText("PLAY", 880, 530, 45, {255, 255, 255, 255});
        renderText("INSTRUCTIONS", 780, 580, 45, {255, 255, 255, 255});
        renderText("ABOUT", 865, 630, 45, {255, 255, 255, 255});
    }
    else if (state == INSTRUCTIONS)
    {
        SDL_SetRenderDrawColor(renderer, 45, 30, 47, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect1 = {1200, 120, 300, 300};
        SDL_RenderCopy(renderer, solution1, NULL, &rect1);
        renderText("N-Queen Problem Instructions:", 400, 100, 35, {247, 44, 37, 255});
        renderText("1. Objective: Place N queens on an 6*6 chessboard.", 400, 150, 30, {255, 255, 0, 255});
        renderText("2. No two queens should share the same row.", 400, 200, 30, {255, 255, 0, 255});
        renderText("3. No two queens should share the same column.", 400, 250, 30, {255, 255, 0, 255});
        renderText("4. No two queens should be on the same diagonal.", 400, 300, 30, {255, 255, 0, 255});
        renderText("5. Click to place queens on the board.", 400, 350, 30, {255, 255, 0, 255});
        renderText("6.Win by placing all N queens correctly. ", 400, 470, 30, {255, 255, 0, 255});
        renderText("7. Explore multiple solutions and strategies. ", 400, 520, 30, {255, 255, 0, 255});
        renderText("8. Use restart or undo options if available.", 400, 570, 30, {255, 255, 0, 255});
        renderText("9. Enjoy the challenge and improve your skills.", 400, 620, 30, {255, 255, 0, 255});
        renderText("HOME", 1700, 940, 35, {19, 111, 99, 255});
    }
    else if (state == ABOUT)
    {
        SDL_SetRenderDrawColor(renderer, 45, 30, 47, 255);
        SDL_RenderClear(renderer);
        renderText("Welcome to the \"6 Queen Puzzle\" application!", 520, 20, 50, {255, 120, 90, 255});
        renderText("This software aims to challenge users with an intriguing puzzle while providing an enjoyable gaming experience.", 100, 100, 35, {255, 255, 255, 255});

        renderText("Development Team:", 100, 170, 40, {255, 0, 0, 255});
        renderText("Suraj Singh", 460, 170, 35, {227, 178, 60, 255});
        renderText("Naresh Rajbanshi", 460, 210, 35, {227, 178, 60, 255});
        renderText("Ramesh Mahato", 460, 250, 35, {227, 178, 60, 255});
        renderText("Priya Mishra", 460, 290, 35, {227, 178, 60, 255});

        renderText("Project Description", 100, 360, 40, {255, 0, 0, 255});
        renderText("The \"6 Queen Puzzle\" application is designed to stimulate logical thinking and problem-solving skills. The puzzle involves placing ", 100, 410, 30, {255, 255, 255, 255});
        renderText("four queens on a chessboard in such a way that no two queens threaten each other. With multiple combinations to explore, users ", 100, 460, 30, {255, 255, 255, 255});
        renderText("can test their strategic prowess and aim for optimal solutions.", 100, 510, 30, {255, 255, 255, 255});

        renderText("Technology Stack", 100, 570, 40, {255, 0, 0, 255});
        renderText("The application was developed using modern technologies and tools, including: Programming Languages: C++, SDL.", 100, 620, 30, {255, 255, 255, 255});
        renderText("Libraries: SDL_ttf (SDL TrueType Fonts), SDL_image", 100, 670, 30, {255, 255, 255, 255});

        renderText("Features", 100, 740, 40, {255, 0, 0, 255});
        renderText("Intuitive User Interface: Simple and user-friendly interface for easy navigation.", 100, 790, 30, {255, 255, 255, 255});
        renderText("Dynamic Puzzle Generation: Generate unique puzzles for endless gameplay.", 100, 840, 30, {255, 255, 255, 255});
        renderText("Real-Time Feedback: Receive immediate feedback on moves and puzzle solutions.", 100, 890, 30, {255, 255, 255, 255});
        renderText("Engaging Visuals: Eye-catching graphics and animations for an immersive experience.", 100, 940, 30, {255, 255, 255, 255});

        renderText("Home", 1700, 940, 40, {19, 111, 99, 255});
    }
    else if (state == PLAY)
    {
        SDL_RenderCopy(renderer, playBG, NULL, NULL);
        drawBoard();
        drawQueens();
        renderText("BACK", 1700, 940, 45, {19, 111, 99, 255});
    }
    else if (state == CONGRATULATIONS)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderText("Congratulations, you solved it!", 700, 500, 55, {0, 255, 0, 255});
        renderText("Home", 1700, 940, 40, {19, 111, 99, 255});
    }

    SDL_RenderPresent(renderer);
}

void Game::run()
{
    bool running = true;
    while (running)
    {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

int main(int argc, char *argv[])
{
    Game game;
    game.run();
    return 0;
}
