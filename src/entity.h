#pragma once
#include "globals.h"
#include "overloaded.h"
#include <iostream>

struct Entity
{
  SDL_FPoint center = {0, 0};
  SDL_Point dir = DIR_UP;

  float speed = 0.005f;
  int anim_frames = 0;
  SDL_Point frame = {0, 0};
  int frame_off_x = 0;
  int anim_time = 300;

  virtual void move()
  {
    SDL_FPoint new_center = center + dir * speed;
    if (can_move(dir))
      center += dir * speed * delta;
  }

  virtual void render()
  {
    const SDL_Rect src{(frame.x + frame_off_x) * SPRITE_S, frame.y * SPRITE_S, SPRITE_S, SPRITE_S};
    const SDL_FRect dest{(center.x - 0.5f * 1.5f) * CELL_S, (center.y - 0.5f * 1.5f) * CELL_S + get_maze_off_y(), CELL_S * 1.5f, CELL_S * 1.5f};
    SDL_RenderCopyF(renderer, sprite_sheet, &src, &dest);
  }

  virtual void anim() = 0;

  bool can_move(const SDL_Point &dir)
  {
    const float offset = 0.45f;
    const SDL_FPoint top_left = center + dir * 0.1f + SDL_FPoint{-offset, -offset};
    const SDL_FPoint top_right = center + dir * 0.1f + SDL_FPoint{+offset, -offset};
    const SDL_FPoint bottom_left = center + dir * 0.1f + SDL_FPoint{-offset, +offset};
    const SDL_FPoint bottom_right = center + dir * 0.1f + SDL_FPoint{+offset, +offset};
    return (map_at((int)top_left.y, (int)top_left.x) != WALL) && (map_at((int)top_right.y, (int)top_right.x) != WALL) && (map_at((int)bottom_left.y, (int)bottom_left.x) != WALL) && (map_at((int)bottom_right.y, (int)bottom_right.x) != WALL);
  }
};