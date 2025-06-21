#include "ghost.h"
#include "overloaded.h"
#include "math_helper.h"
#include <array>

void Ghost::move()
{
  choose_nearest_dir();
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

void Ghost::choose_nearest_dir()
{
  std::array<SDL_FPoint, 4> dirs = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
  std::pair<SDL_FPoint, float> dir_dist = {SDL_FPoint{0, 0}, 1000};

  for (auto &dir_v : dirs)
  {
    if (!can_move(dir_v * 0.1f)) // tutaj był problem
      continue;

    if (dir_v == (dir * -1.f))
      continue;

    float dist = distf(center.x + dir_v.x, center.y + dir_v.y, target.x, target.y);
    if (dist < dir_dist.second)
    {
      dir_dist = std::make_pair(dir_v, dist);
    }
  }

  // if (ghost_type == "blinky")
  //   std::cout << (dir * -1).x << " : " << (dir * -1).y << std::endl;
  if (ghost_type == "blinky" && (int)(dir * -1).x == (int)dir_dist.first.x && (int)(dir * -1).y == (int)dir_dist.first.y)
    SDL_assert(0);
  dir = dir_dist.first;
}

void Blinky::set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir)
{
  target = SDL_Point{(int)pac_center.x, (int)pac_center.y};
}

void Pinky::set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir)
{
  SDL_FPoint four_in_front = pac_center + pac_dir * 4;
  if (pac_dir == DIR_UP)
    four_in_front.x -= 4;
  target = SDL_Point{(int)four_in_front.x, (int)four_in_front.y};
}

void Inky::set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir)
{
}

void Clyde::set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir)
{
}