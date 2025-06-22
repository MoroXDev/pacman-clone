#pragma once
#include "entity.h"

struct Ghost : public Entity
{
  SDL_Point chase_target = {0, 0};
  SDL_Point scatter_target = {0, 0};
  SDL_Point turn_cell = {-1, -1};

  void anim() override;
  void move() override;
  virtual void set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir) = 0;
  void choose_nearest_dir(const SDL_Point &target);
  virtual ~Ghost() = default;
};

struct Blinky : public Ghost
{
  Blinky()
  {
    frame = {0, 4};
    center = SDL_FPoint{14.f, 11.5f};
    scatter_target = UPPER_RIGHT_CORNER;
  }

  void set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir) override;
};

struct Pinky : public Ghost
{
  Pinky()
  {
    frame = {0, 5};
    center = SDL_FPoint{15.f, 11.5f};
    scatter_target = UPPER_LEFT_CORNER;
  }
  void set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir) override;
};

struct Inky : public Ghost
{
  SDL_FPoint &blinky_center;

  Inky(SDL_FPoint &blinky_center) : blinky_center(blinky_center)
  {
    frame = {0, 6};
    center = SDL_FPoint{16.f, 11.5f};
    scatter_target = LOWER_RIGHT_CORNER;
  }
  void set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir) override;
};

struct Clyde : public Ghost
{
  Clyde()
  {
    frame = {0, 7};
    center = SDL_FPoint{13.f, 11.5f};
    scatter_target = LOWER_LEFT_CORNER;
  }
  void set_chase_target(const SDL_FPoint &pac_center, const SDL_Point &pac_dir) override;
};
