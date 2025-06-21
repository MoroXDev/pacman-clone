#include "pacman.h"
#include "math_helper.h"
#include "overloaded.h"

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

  // if (keystates[SDL_SCANCODE_W])
  //   dir = DIR_UP;
  // if (keystates[SDL_SCANCODE_S])
  //   dir = DIR_DOWN;
  // if (keystates[SDL_SCANCODE_A])
  //   dir = DIR_LEFT;
  // if (keystates[SDL_SCANCODE_D])
  //   dir = DIR_RIGHT;
}

void Pacman::collect_dots()
{
  if (map[(int)center.y][(int)center.x] == DOT)
  {
    points++;
    map[(int)center.y][(int)center.x] = EMPTY;
    Mix_PlayChannel(-1, eat_dot_wav, 1);
  }
}

void Pacman::anim()
{
  if (dir == DIR_RIGHT)
    frame.y = 0;
  if (dir == DIR_LEFT)
    frame.y = 1;
  if (dir == DIR_UP)
    frame.y = 2;
  if (dir == DIR_DOWN)
    frame.y = 3;

  anim_frames++;
  if (anim_frames > 500)
  {
    frame_off_x = (frame_off_x + 1) % 2;
    anim_frames = 0;
  }
}

void Pacman::move()
{
  const SDL_FPoint cell_center = SDL_FPoint{(float)(int)center.x + 0.5f, (float)(int)center.y + 0.5f};
  // const float dist = distf(center.x, center.y, cell_center.x, cell_center.y);
  if (can_move(input_dir * 0.5f))
  {
    dir = input_dir;
  }
  Entity::move();
}
