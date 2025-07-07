#include "ghost.h"
#include "overloaded.h"
#include "math_helper.h"
#include <array>
#include <random>

void Ghost::move()
{
  if (center.x * CELL_S < 0)
    center.x = COLS_N;
  if (center.x * CELL_S > MAZE_W)
    center.x = 0;

  if (is_dead)
  {
    if (!can_pass_through_walls)
      choose_nearest_dir({(int)DEATH_GHOST_TARGET.x, (int)DEATH_GHOST_TARGET.y});

    const float dist_to_entry = distf(center.x * CELL_S, center.y * CELL_S, DEATH_GHOST_TARGET.x * CELL_S, DEATH_GHOST_TARGET.y * CELL_S);
    const float dist_to_base = distf(center.x * CELL_S, center.y * CELL_S, BASE_CENTER.x * CELL_S, BASE_CENTER.y * CELL_S);
    if (dist_to_entry < CELL_S * 0.1f)
    {
      dir = DIR_DOWN;
      can_pass_through_walls = true;
    }
    center += dir * speed * 2.f * delta;
    if (dist_to_base < CELL_S * 0.1f)
    {
      dir = DIR_UP;
      is_dead = false;
      is_frightened = false;
    }
    return;
  }
  else if (can_pass_through_walls)
  {
    center += dir * speed * 0.5f * delta;

    const float dist_to_entry = distf(center.x * CELL_S, center.y * CELL_S, DEATH_GHOST_TARGET.x * CELL_S, DEATH_GHOST_TARGET.y * CELL_S);
    if (dist_to_entry < CELL_S * 0.1f)
    {
      center = DEATH_GHOST_TARGET;
      can_pass_through_walls = false;
    }

    return;
  }
  else if (is_frightened)
  {
    choose_random_dir();
    center += dir * speed * 0.5f * delta;
    return;
  }
  else
  {
    if (ghosts_target_mode == SCATTER)
      choose_nearest_dir(scatter_target);
    if (ghosts_target_mode == CHASE)
      choose_nearest_dir(chase_target);
  }

  center += dir * speed * delta;
}

void Ghost::reset()
{
  dir = DIR_UP;
  anim_frames = 0;
  frame = default_frame;
  frame_off_x = 0;
  center = start_pos;
  turn_cell = {-1, -1};
}

void Ghost::choose_random_dir()
{
  if (turn_cell == SDL_Point{(int)center.x, (int)center.y})
    return;
  std::array<SDL_Point, 4> dirs = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 3);

  int index = dist6(rng);
  for (int i = 0; i < dirs.size(); i++)
  {
    if (can_move(dirs[index]) && dirs[index] != (dir * -1))
      break;
    index = (index + 1) % 4;
  }

  if (dirs[index] != dir)
    turn_cell = SDL_Point{(int)center.x, (int)center.y};
  dir = dirs[index];
}

void Ghost::is_inside_base()
{
}

void Ghost::anim()
{
  if (is_dead)
  {
    frame.y = 5;
    frame_off_x = 0;

    if (dir == DIR_RIGHT)
      frame.x = 8;
    if (dir == DIR_LEFT)
      frame.x = 9;
    if (dir == DIR_UP)
      frame.x = 10;
    if (dir == DIR_DOWN)
      frame.x = 11;
    return;
  }

  anim_frames++;
  if (anim_frames > anim_time)
  {
    frame_off_x = (frame_off_x + 1) % 2;
    anim_frames = 0;
  }

  if (is_frightened)
  {
    frame = {8, 4};
    if ((int)ghost_blink_time % 2 == 0 && fright_timer.get_time_elapsed_ms() > FRIGHT_PERIOD * 0.7)
      frame = {10, 4};
    return;
  }
  else
  {
    frame = default_frame;
  }

  if (dir == DIR_RIGHT)
    frame.x = 0;
  if (dir == DIR_LEFT)
    frame.x = 2;
  if (dir == DIR_UP)
    frame.x = 4;
  if (dir == DIR_DOWN)
    frame.x = 6;
}

void Ghost::choose_nearest_dir(const SDL_Point &target)
{
  if (turn_cell == SDL_Point{(int)center.x, (int)center.y})
    return;

  std::array<SDL_Point, 4> dirs = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
  std::pair<SDL_Point, float> dir_dist = {dir, 1000};

  for (auto &dir_v : dirs)
  {
    if (!can_move(dir_v))
      continue;

    if (dir_v == dir * -1)
      continue;

    float dist = distf(center.x + dir_v.x, center.y + dir_v.y, target.x, target.y);
    if (dist < dir_dist.second)
    {
      dir_dist = std::make_pair(dir_v, dist);
    }
  }

  if (dir_dist.first != dir)
    turn_cell = SDL_Point{(int)center.x, (int)center.y};

  dir = dir_dist.first;
}

void Blinky::set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir)
{
  chase_target = SDL_Point{(int)pac_center.x, (int)pac_center.y};
}

void Pinky::set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir)
{
  SDL_FPoint four_in_front = pac_center + pac_dir * 4;
  if (pac_dir == DIR_UP)
    four_in_front.x -= 4;
  chase_target = SDL_Point{(int)four_in_front.x, (int)four_in_front.y};
}

void Inky::set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir)
{
  SDL_FPoint four_in_front = pac_center + pac_dir * 4;
  if (pac_dir == DIR_UP)
    four_in_front.x -= 4;
  chase_target = SDL_Point{(int)four_in_front.x, (int)four_in_front.y};

  SDL_FPoint vel = four_in_front - blinky_center;
  chase_target += SDL_Point{(int)vel.x, (int)vel.y};
}

void Clyde::set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir)
{
  chase_target = SDL_Point{(int)pac_center.x, (int)pac_center.y};
  if (distf(pac_center.x, pac_center.y, center.x, center.y) < 8)
    chase_target = scatter_target;
}