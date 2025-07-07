#pragma once
#include "entity.h"
#include <array>

struct Ghost;

struct Pacman : public Entity
{
  SDL_Point input_dir = DIR_UP;
  void input_control(const Uint8 *keystates);
  const int anim_time_dead = 600;
  int life = 3;

  Pacman()
  {
    center = START;
  }

  SDL_FPoint get_world_pos()
  {
    return center * CELL_S + SDL_FPoint{0, get_maze_off_y()};
  }

  void kill();

  void move() override;

  void collect_dots(std::array<Ghost*, 4>& ghosts);

  void collect_fruits();

  void anim() override;

  void render() override;

  bool is_dead();

  void reset();
};