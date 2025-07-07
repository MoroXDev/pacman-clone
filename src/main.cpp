#include <iostream>
#include "pacman.h"
#include "SDL_image.h"
#include "ghost.h"
#include "SDL_ttf.h"
#include "math_helper.h"
#include "SDL_timer.h"

void restart_level(Pacman &pacman, std::array<Ghost *, 4> &ghosts, bool refresh_dots)
{
    using namespace std::chrono;
    if (refresh_dots)
    {
        for (int y = 0; y < ROWS_N; y++)
        {
            for (int x = 0; x < COLS_N; x++)
            {
                map[y][x] = CONST_MAP[y][x];
            }
        }
        collected_dots = 0;
        mode_change_count = 0;
        fruit_collected = false;
        score = 0;
    }

    pacman.reset();
    for (auto &ghost : ghosts)
    {
        ghost->reset();
    }

    dot_blink_time = 0;
    ghost_blink_time = 0;
    is_game_over = false;
    ghosts_target_mode = SCATTER;
    has_game_started = false;
    game_timer.restart();
}

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

void render_fruit()
{
    if (fruit_exists())
    {
        SDL_Rect src = {(FRUIT_FRAME.x + get_level_fruit(level)) * SPRITE_S, FRUIT_FRAME.y * SPRITE_S, SPRITE_S, SPRITE_S};
        SDL_FRect dest = {START.x * CELL_S - CELL_S / 1.5f, START.y * CELL_S - CELL_S / 1.5f + get_maze_off_y(), CELL_S * 1.5f, CELL_S * 1.5f};
        SDL_RenderCopyF(renderer, sprite_sheet, &src, &dest);
    }
}

void fruit_create()
{
    if (fruit_collected)
        return;

    if (collected_dots > 70 && !has_fruit_appeared[0])
    {
        has_fruit_appeared[0] = true;
        fruit_appear_timer.restart();
    }
    if (collected_dots > 170 && !has_fruit_appeared[1])
    {
        has_fruit_appeared[1] = true;
        fruit_appear_timer.restart();
    }
}

void render_level_counter()
{
    int level_clmp = std::clamp(level, 0, INT_MAX);
    int seven_behind_level = std::clamp(level_clmp - 7, 0, INT_MAX);
    int x = 0;
    for (int i = seven_behind_level; i <= level_clmp; i++)
    {
        const int fruit = std::clamp(i, 0, 12);
        SDL_Rect src = {(FRUIT_FRAME.x + get_level_fruit(fruit)) * SPRITE_S, FRUIT_FRAME.y * SPRITE_S, SPRITE_S, SPRITE_S};
        SDL_FRect dest = {(float)(x * LEVEL_COUNTER_S), MAZE_H + get_maze_off_y(), LEVEL_COUNTER_S, LEVEL_COUNTER_S};
        SDL_RenderCopyF(renderer, sprite_sheet, &src, &dest);
        x++;
    }
}

void render_life(int life)
{
    const SDL_Rect src = {8 * SPRITE_S, SPRITE_S, SPRITE_S, SPRITE_S};
    for (int i = 0; i < life; i++)
    {
        const SDL_FRect dest = {MAZE_W - float(i + 1) * PAC_LIFE_S, MAZE_H + get_maze_off_y(), PAC_LIFE_S, PAC_LIFE_S};
        SDL_RenderCopyF(renderer, sprite_sheet, &src, &dest);
    }
}

void render(Pacman &pacman, std::array<Ghost *, 4> &ghosts)
{
    const SDL_Rect maze_src{0, 0, 224, 248};
    const SDL_FRect maze_dest{0, get_maze_off_y(), MAZE_W, MAZE_H};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopyF(renderer, maze, &maze_src, &maze_dest);

    for (int y = 0; y < ROWS_N; y++)
    {
        for (int x = 0; x < COLS_N; x++)
        {
            if (map[y][x] == DOT || map[y][x] == POWER_PELLET)
            {
                float dot_s = CELL_S / 3.f;
                if (map[y][x] == POWER_PELLET)
                {
                    dot_s *= 2.f;
                    if ((int)dot_blink_time % 2 == 0)
                    {
                        dot_s = 0;
                    }
                }

                SDL_SetRenderDrawColor(renderer, 252, 170, 88, 255);
                SDL_FRect rect{
                    .x = x * CELL_S + CELL_S / 2.f - dot_s / 2.f,
                    .y = y * CELL_S + CELL_S / 2.f - dot_s / 2.f + get_maze_off_y(),
                    .w = dot_s,
                    .h = dot_s};
                SDL_RenderFillRectF(renderer, &rect);
            }
        }
    }

    render_fruit();
    pacman.render();
    for (auto &ghost : ghosts)
    {
        ghost->render();
    }

    for (auto it = score_popups.begin(); it != score_popups.end();)
    {
        it->render();
        if (it->is_empty)
        {
            it->destroy();
            it = score_popups.erase(it); // erase zwraca nowy iterator
        }
        else
            ++it;
    }

    int window_w = 0;
    SDL_GetWindowSize(window, &window_w, NULL);
    score_label.render(0, 0);
    score_counter.render_centered(MAZE_W * 0.12f, TTF_FontHeight(font) * 1.5f);
    high_score_counter.render_centered(MAZE_W / 2.f, TTF_FontHeight(font) * 1.5f);
    render_level_counter();
    render_life(pacman.life);
    SDL_RenderPresent(renderer);
}

void set_stuff()
{
    TTF_SetFontSize(font, CELL_S);
    if ((int)one_up_blink_time % 2 == 0)
        score_label.set("   1UP        HIGH SCORE", WHITE);
    else
        score_label.set("              HIGH SCORE", WHITE);
    score_counter.set(std::to_string(score), WHITE);
    high_score_counter.set(std::to_string(high_score), WHITE);

    high_score = std::max(high_score, score);
}

void set_mode()
{
    using namespace std::chrono;

    if (target_mode_timer.get_time_elapsed_ms() > mode_periods[ghosts_target_mode] && has_game_started)
    {
        mode_change_count++;
        ghosts_target_mode = (TARGET_MODE)(mode_change_count % 2);
        target_mode_timer.restart();
    }
}

void check_for_death(std::array<Ghost *, 4> &ghosts, Pacman &pacman)
{
    int dead_ghosts_c = 0;
    if (is_game_over)
        return;

    for (auto &ghost : ghosts)
    {
        const float dist = distf(ghost->center.x * CELL_S, ghost->center.y * CELL_S, pacman.center.x * CELL_S, pacman.center.y * CELL_S);

        if (dist < CELL_S)
        {
            if (!ghost->is_dead)
            {
                if (ghost->is_frightened)
                {
                    Mix_PlayChannel(-1, eat_ghost_wav, 0);
                    score += score_for_ghost;
                    score_popups.emplace_back(score_for_ghost, renderer, font, pacman.get_world_pos());
                    score_for_ghost = std::min(score_for_ghost * 2, 1600);
                    ghost->is_dead = true;
                }
                else
                {
                    pacman.kill();
                    is_game_over = true;
                }
            }
        }
        dead_ghosts_c += ghost->is_dead;
    }

    are_any_ghosts_dead = dead_ghosts_c > 0;
}

void check_for_restart(Pacman &pacman, std::array<Ghost *, 4> &ghosts)
{
    if (pacman.is_dead())
    {
        const bool refresh_dots = pacman.life <= 0;
        restart_level(pacman, ghosts, refresh_dots);
        set_music(*siren_mus);
        if (refresh_dots)
        {
            pacman.life = 3;
            level = 0;
        }
    }

    if (collected_dots >= DOTS_N)
    {
        level++;
        restart_level(pacman, ghosts, true);
        set_music(*siren_mus);
    }
}

void change_music()
{
    if (is_game_over)
    {
        set_music(*death_mus);
        return;
    }

    static int count = 0;
    if (are_any_ghosts_dead)
    {
        set_music(*eyes_mus);
    }
    else if (is_fright_mode())
    {
        set_music(*fright_mus);
    }
    else if ((ghosts_target_mode == SCATTER || ghosts_target_mode == CHASE) && has_game_started)
    {
        set_music(*siren_mus);
    }
}

void update(Pacman &pacman, std::array<Ghost *, 4> &ghosts)
{
    const uint32_t ticks = SDL_GetTicks();
    delta = ticks - last_tick_time;
    last_tick_time = ticks;

    change_music();
    dot_blink_time += 0.005f * delta;
    ghost_blink_time += 0.005f * delta;
    one_up_blink_time += 0.002f * delta;
    check_for_restart(pacman, ghosts);
    check_for_death(ghosts, pacman);
    set_mode();
    pacman.anim();

    if (!is_fright_mode())
        score_for_ghost = 200;

    for (auto &ghost : ghosts)
    {
        if (!is_fright_mode())
            ghost->is_frightened = false;
        ghost->anim();
        if (has_game_started || is_game_over)
        {

            ghost->set_chase_target(pacman.center, pacman.dir);
            ghost->move();
        }
    }
    if (!has_game_started || is_game_over)
        return;

    fruit_create();
    pacman.collect_dots(ghosts);
    pacman.collect_fruits();
    pacman.move();
}

void init_assets()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_MasterVolume(MIX_MAX_VOLUME / 4);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // sciszenie

    TTF_Init();
    font = TTF_OpenFont("H:/Users/szcze/AppData/Local/Programs/VS Code projects/C++/pac-man/JOYSTIX.ttf", CELL_S);

    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0, &display);

    window = SDL_CreateWindow("pac-man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAZE_W, MAZE_H + get_maze_off_y() + LEVEL_COUNTER_S, SDL_WINDOW_RESIZABLE);
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
    death_mus = Mix_LoadMUS("sounds/death_0.wav");

    score_counter = Text(font, renderer);
    score_label = Text(font, renderer);
    high_score_counter = Text(font, renderer);
}

void free_assets()
{
    for (auto &popup : score_popups)
        popup.destroy();
    score_popups.clear();

    score_counter.destroy();
    score_label.destroy();
    high_score_counter.destroy();

    Mix_FreeChunk(eat_dot_wav);
    Mix_FreeChunk(eat_fruit_wav);
    Mix_FreeChunk(eat_ghost_wav);

    Mix_FreeMusic(death_mus);
    Mix_FreeMusic(eyes_mus);
    Mix_FreeMusic(fright_mus);
    Mix_FreeMusic(siren_mus);
    Mix_FreeMusic(start_mus);
    SDL_DestroyTexture(maze);
    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void start()
{
    using namespace std::chrono;
    auto start_mus_time = milliseconds((int)(Mix_MusicDuration(start_mus) * 1000) + 300);
    if (game_timer.get_time_elapsed_ms() > start_mus_time && !has_game_started)
    {
        has_game_started = true;
        target_mode_timer.restart();
    }
}

int main(int argc, char *argv[])
{
    init_assets();
    Mix_PlayMusic(start_mus, 0);
    current_mus = start_mus;
    fright_timer.start -= std::chrono::seconds(3);
    fruit_appear_timer.start -= std::chrono::seconds(11);

    Pacman pacman;
    std::array<Ghost *, 4> ghosts;
    ghosts[0] = new Blinky();
    ghosts[1] = new Pinky();
    ghosts[2] = new Inky(ghosts[0]->center);
    ghosts[3] = new Clyde();

    game_timer.restart();

    while (!is_exit)
    {

        start();
        set_stuff();
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