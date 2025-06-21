#include <iostream>
#include "pacman.h"
#include "SDL_image.h"
#include "ghost.h"

void input(Pacman &pacman)
{
    SDL_Event event;
    auto *keystates = SDL_GetKeyboardState(NULL);

    pacman.input_control(keystates);

    while (SDL_PollEvent(&event))
    {
        if (keystates[SDL_SCANCODE_ESCAPE])
            is_exit = true;

        if (keystates[SDL_SCANCODE_SPACE])
            Mix_HaltChannel(-1);
        switch (event.type)
        {
        case SDL_EventType::SDL_QUIT:
            is_exit = true;
            break;
        }
    }
}

void render(Pacman &pacman, std::array<Ghost *, 4> &ghosts)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect maze_src{0, 0, 224, 248};
    SDL_FRect maze_dest{0, 0, MAZE_W, MAZE_H};
    SDL_RenderCopyF(renderer, maze, &maze_src, &maze_dest);

    for (int y = 0; y < ROWS_N; y++)
    {
        for (int x = 0; x < COLS_N; x++)
        {
            if (map[y][x] == DOT)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                const int dot_s = CELL_S / 3.f;
                SDL_FRect rect{
                    .x = x * CELL_S + CELL_S / 2.f - dot_s / 2.f,
                    .y = y * CELL_S + CELL_S / 2.f - dot_s / 2.f,
                    .w = dot_s,
                    .h = dot_s};
                SDL_RenderFillRectF(renderer, &rect);
            }
        }
    }

    pacman.render();
    for (auto &ghost : ghosts)
    {
        ghost->render();
    }

    SDL_RenderPresent(renderer);
}

void update(Pacman &pacman, std::array<Ghost *, 4> &ghosts)
{
    pacman.anim();
    pacman.collect_dots();
    pacman.move();

    for (auto &ghost : ghosts)
    {
        ghost->anim();
        ghost->set_target(pacman.center, pacman.dir);
        ghost->move();
    }
}

void init_assets()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_MasterVolume(MIX_MAX_VOLUME / 4);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // sciszenie

    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0, &display);

    window = SDL_CreateWindow("pac-man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display.w * 0.75f, display.h * 0.75f, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);

    maze = IMG_LoadTexture(renderer, "maze.png");
    sprite_sheet = IMG_LoadTexture(renderer, "graphics.png");

    siren_mus = Mix_LoadMUS("sounds/siren0.wav");
    fright_mus = Mix_LoadMUS("sounds/fright.wav");
    eyes_mus = Mix_LoadMUS("sounds/eyes.wav");
    start_mus = Mix_LoadMUS("sounds/start.wav");

    eat_dot_wav = Mix_LoadWAV("sounds/eat_dot_0.wav");
    eat_fruit_wav = Mix_LoadWAV("sounds/eat_fruit.wav");
    eat_ghost_wav = Mix_LoadWAV("sounds/eat_ghost.wav");
    Mix_PlayMusic(start_mus, 1);
}

void free_assets()
{
    Mix_FreeChunk(eat_dot_wav);
    Mix_FreeChunk(eat_fruit_wav);
    Mix_FreeChunk(eat_ghost_wav);

    Mix_FreeMusic(eyes_mus);
    Mix_FreeMusic(fright_mus);
    Mix_FreeMusic(siren_mus);
    Mix_FreeMusic(start_mus);
    SDL_DestroyTexture(maze);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    init_assets();

    Pacman pacman;
    std::array<Ghost *, 4> ghosts = {new Blinky(), new Pinky(), new Inky(), new Clyde()};

    while (!is_exit)
    {
        input(pacman);
        update(pacman, ghosts);
        render(pacman, ghosts);
    }

    for (auto &ghost : ghosts)
    {
        delete ghost;
    }
    free_assets();
    return 0;
}
