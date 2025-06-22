#pragma once
#include "entity.h"

struct Pacman : public Entity
{
  SDL_Point input_dir = DIR_UP;
  void input_control(const Uint8 * keystates);

  Pacman()
  {
    center = START;
    
  }

  void move() override;

  void collect_dots();

  void anim() override;
};