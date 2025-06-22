#include "ghost.h"
#include "overloaded.h"
#include "math_helper.h"
#include <array>

void Ghost::move()
{
  if (ghosts_target_mode == SCATTER)
    choose_nearest_dir(scatter_target);
  if (ghosts_target_mode == CHASE)
    choose_nearest_dir(chase_target);
  center += dir * speed;
}

void Ghost::anim()
{
  if (dir == DIR_RIGHT)
    frame.x = 0;
  if (dir == DIR_LEFT)
    frame.x = 2;
  if (dir == DIR_UP)
    frame.x = 4;
  if (dir == DIR_DOWN)
    frame.x = 6;

  anim_frames++;
  if (anim_frames > 500)
  {
    frame_off_x = (frame_off_x + 1) % 2;
    anim_frames = 0;
  }
}

void Ghost::choose_nearest_dir(const SDL_Point &target)
{
  if (turn_cell == SDL_Point{(int)center.x, (int)center.y})
    return;

  std::array<SDL_Point, 4> dirs = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
  std::pair<SDL_Point, float> dir_dist = {dir, 1000};

  for (auto &dir_v : dirs)
  {
    if (!can_move(dir_v * 0.1f))
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