#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

struct Text
{
private:
  SDL_Texture *texture = nullptr;
  std::string value = "";
  SDL_Renderer *renderer = nullptr;
  TTF_Font *font = nullptr;

public:
  void set(std::string text, SDL_Color color)
  {
    if (text == value || font == nullptr || renderer == nullptr)
      return;
    value = text;
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if (texture != nullptr)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    
    SDL_FreeSurface(surf);
  }
  
  SDL_Point get_bounds()
  {
    if (texture == nullptr)
      return {0, 0};

    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return {w, h};
  }

  void render(float x, float y)
  {
    if (texture == nullptr || font == nullptr || renderer == nullptr)
      return;

    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_FRect dest = {x, y, (float)w, (float)h};
    SDL_RenderCopyF(renderer, texture, &src, &dest);
  }

  void render(const SDL_FPoint &pos)
  {
    if (texture == nullptr || font == nullptr || renderer == nullptr)
    return;

    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_FRect dest = {pos.x, pos.y, (float)w, (float)h};
    SDL_RenderCopyF(renderer, texture, &src, &dest);
  }

  void render_centered(float x, float y)
  {
    if (texture == nullptr || font == nullptr || renderer == nullptr)
      return;

    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_FRect dest = {x - get_bounds().x / 2.f, y - get_bounds().y / 2.f, (float)w, (float)h};
    SDL_RenderCopyF(renderer, texture, &src, &dest);
  }

  void render_centered(const SDL_FPoint &pos)
  {
    if (texture == nullptr || font == nullptr || renderer == nullptr)
      return;

    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect src = {0, 0, w, h};
    SDL_FRect dest = {pos.x - get_bounds().x / 2.f, pos.y - get_bounds().y / 2.f, (float)w, (float)h};
    SDL_RenderCopyF(renderer, texture, &src, &dest);
  }


  Text(TTF_Font *font, SDL_Renderer *renderer) : font(font), renderer(renderer)
  {
  }

  Text() {}

  void destroy()
  {
    renderer = nullptr;
    font = nullptr;
    if (texture != nullptr)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }
};