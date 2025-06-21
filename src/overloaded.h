#pragma once
#include "SDL.h"

inline SDL_Point operator+(const SDL_Point &point_a, const SDL_Point &point_b)
{
  return SDL_Point{
      .x = point_a.x + point_b.x,
      .y = point_a.y + point_b.y};
}

inline SDL_Point &operator+=(SDL_Point &point_a, const SDL_Point &point_b)
{
  point_a.x += point_b.x;
  point_a.y += point_b.y;
  return point_a;
}

inline SDL_Point &operator*=(SDL_Point &point_a, const SDL_Point &point_b)
{
  point_a.x *= point_b.x;
  point_a.y *= point_b.y;
  return point_a;
}

inline SDL_Point operator*(const SDL_Point &point_a, const SDL_Point &point_b)
{
  return SDL_Point{
      .x = point_a.x * point_b.x,
      .y = point_a.y * point_b.y};
}

// for floats + ints

inline SDL_FPoint operator+(const SDL_FPoint &point_a, const SDL_Point &point_b)
{
  return SDL_FPoint{
      .x = point_a.x + point_b.x,
      .y = point_a.y + point_b.y};
}

inline SDL_FPoint &operator+=(SDL_FPoint &point_a, const SDL_Point &point_b)
{
  point_a.x += point_b.x;
  point_a.y += point_b.y;
  return point_a;
}

inline SDL_FPoint &operator*=(SDL_FPoint &point_a, const SDL_Point &point_b)
{
  point_a.x *= point_b.x;
  point_a.y *= point_b.y;
  return point_a;
}

inline SDL_FPoint operator*(const SDL_FPoint &point_a, const SDL_Point &point_b)
{
  return SDL_FPoint{
      .x = point_a.x * point_b.x,
      .y = point_a.y * point_b.y};
}

// mnozenie

inline SDL_FPoint operator*(const SDL_Point &point_a, const float mult)
{
  return SDL_FPoint{
      .x = point_a.x * mult,
      .y = point_a.y * mult};
}

inline SDL_FPoint operator*(const SDL_FPoint &point_a, const float mult)
{
  return SDL_FPoint{
      .x = point_a.x * mult,
      .y = point_a.y * mult};
}

inline SDL_Point operator*(const SDL_Point &point_a, const int mult)
{
  return SDL_Point{
      .x = point_a.x * mult,
      .y = point_a.y * mult};
}

inline SDL_Point &operator*=(SDL_Point &point_a, const int mult)
{
  point_a.x *= mult;
  point_a.y *= mult;
  return point_a;
}

inline SDL_FPoint &operator*=(SDL_FPoint &point_a, const float mult)
{
  point_a.x *= mult;
  point_a.y *= mult;
  return point_a;
}

inline SDL_FPoint operator+(const SDL_FPoint &point_a, const SDL_FPoint &point_b)
{
  return SDL_FPoint{
      .x = point_a.x + point_b.x,
      .y = point_a.y + point_b.y};
}

inline SDL_FPoint &operator+=(SDL_FPoint &point_a, const SDL_FPoint &point_b)
{
  point_a.x += point_b.x;
  point_a.y += point_b.y;
  return point_a;
}

inline bool operator==(const SDL_FPoint &point_a, const SDL_FPoint &point_b)
{
  return (point_a.x == point_b.x) && (point_a.y == point_b.y);
}

//minus

inline SDL_Point operator-(const SDL_Point &point_a, const SDL_Point &point_b)
{
  return SDL_Point{
      .x = point_a.x - point_b.x,
      .y = point_a.y - point_b.y};
}

inline SDL_Point &operator-=(SDL_Point &point_a, const SDL_Point &point_b)
{
  point_a.x -= point_b.x;
  point_a.y -= point_b.y;
  return point_a;
}

inline SDL_FPoint operator-(const SDL_FPoint &point_a, const SDL_Point &point_b)
{
  return SDL_FPoint{
      .x = point_a.x - point_b.x,
      .y = point_a.y - point_b.y};
}

inline SDL_FPoint &operator-=(SDL_FPoint &point_a, const SDL_Point &point_b)
{
  point_a.x -= point_b.x;
  point_a.y -= point_b.y;
  return point_a;
}

inline SDL_FPoint operator-(const SDL_FPoint &point_a, const SDL_FPoint &point_b)
{
  return SDL_FPoint{
      .x = point_a.x - point_b.x,
      .y = point_a.y - point_b.y};
}

inline SDL_FPoint &operator-=(SDL_FPoint &point_a, const SDL_FPoint &point_b)
{
  point_a.x -= point_b.x;
  point_a.y -= point_b.y;
  return point_a;
}