#include "pacman.h"
#include "math_helper.h"
#include "overloaded.h"
#include "ghost.h"

void Pacman::input_control(const Uint8 *keystates)
{
  if (keystates[SDL_SCANCODE_W])
    input_dir = DIR_UP;
  if (keystates[SDL_SCANCODE_S])
    input_dir = DIR_DOWN;
  if (keystates[SDL_SCANCODE_A])
    input_dir = DIR_LEFT;
  if (keystates[SDL_SCANCODE_D])
    input_dir = DIR_RIGHT;
}

void Pacman::collect_dots(std::array<Ghost *, 4> &ghosts)
{
  if (map_at((int)center.y, (int)center.x) == DOT)
  {
    score += 10;
    collected_dots++;
    map[(int)center.y][(int)center.x] = EMPTY;
    Mix_PlayChannel(-1, eat_dot_wav, 0);
  }

  if (map_at((int)center.y, (int)center.x) == POWER_PELLET)
  {
    fright_timer.restart();
    score += 50;
    collected_dots++;
    map[(int)center.y][(int)center.x] = EMPTY;
    Mix_PlayChannel(-1, eat_dot_wav, 0);

    for (auto &ghost : ghosts)
    {
      ghost->is_frightened = true;
    }
  }
}

void Pacman::collect_fruits()
{
  const float dist = distf(START.x * CELL_S, START.y * CELL_S, center.x * CELL_S, center.y * CELL_S);

  if (fruit_exists() && dist < CELL_S)
  {
    Mix_PlayChannel(-1, eat_fruit_wav, 0);
    fruit_collected = true;
    score += score_for_fruit[get_level_fruit(level)];
    score_popups.emplace_back(score_for_fruit[get_level_fruit(level)], renderer, font, START * CELL_S + SDL_FPoint{0, get_maze_off_y()});
  }
}

void Pacman::anim()
{
  anim_frames++;

  if (is_game_over && anim_frames > anim_time_dead)
  {
    anim_frames = 0;
    frame_off_x = std::clamp(frame_off_x + 1, 0, 12);
  }

  if (anim_frames > anim_time && !is_game_over)
  {
    anim_frames = 0;
    frame_off_x = (frame_off_x + 1) % 2;
  }

  if (is_game_over)
    return;
  if (dir == DIR_RIGHT)
    frame.y = 0;
  if (dir == DIR_LEFT)
    frame.y = 1;
  if (dir == DIR_UP)
    frame.y = 2;
  if (dir == DIR_DOWN)
    frame.y = 3;
}

void Pacman::kill()
{
  frame = {2, 0};
  frame_off_x = 0;
  life--;
}

void Pacman::move()
{
  if (center.x * CELL_S < 0)
    center.x = COLS_N;
  if (center.x * CELL_S > MAZE_W)
    center.x = 0;

  const SDL_FPoint cell_center = SDL_FPoint{(float)(int)center.x + 0.5f, (float)(int)center.y + 0.5f};
  // const float dist = distf(center.x, center.y, cell_center.x, cell_center.y);
  if (can_move(input_dir))
  {
    dir = input_dir;
  }
  Entity::move();
}

void Pacman::render()
{
  if (is_dead())
    return;
  Entity::render();
}

bool Pacman::is_dead()
{
  return is_game_over && frame_off_x > 11;
}

void Pacman::reset()
{
  frame = {0, 0};
  dir = DIR_UP;
  input_dir = DIR_UP;
  center = START;
}