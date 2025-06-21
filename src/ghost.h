#pragma once
#include "entity.h"

struct Ghost : public Entity
{
  SDL_Point target = {0, 0};
  std::string ghost_type = "";

  void anim();
  void move();
  virtual void set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir) = 0;
  void choose_nearest_dir();
  virtual ~Ghost() = default;
};

struct Blinky : public Ghost
{
  Blinky()
  {
    frame = {0, 4};
    center = SDL_FPoint{14.f, 11.5f};
    ghost_type = "blinky";
  }

  void set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir) override;
};

struct Pinky : public Ghost
{
  Pinky()
  {
    frame = {0, 5};
    center = SDL_FPoint{15.f, 11.5f};
  }
  void set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir) override;
};

struct Inky : public Ghost
{
  Inky()
  {
    frame = {0, 6};
    center = SDL_FPoint{16.f, 11.5f};
  }
  void set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir) override;
};

struct Clyde : public Ghost
{
  Clyde()
  {
    frame = {0, 7};
    center = SDL_FPoint{13.f, 11.5f};
  }
  void set_target(const SDL_FPoint &pac_center, const SDL_FPoint &pac_dir) override;
};
