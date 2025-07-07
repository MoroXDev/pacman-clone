#include "text.h"
#include "SDL.h"
#include <iostream>

extern uint32_t delta;
extern const SDL_Color AQUA;

struct ScorePopup
{
  Text score_text;
  float height = 0;
  SDL_FPoint center;
  static constexpr float speed = 0.1f;
  static constexpr int MAX_HEIGHT = 50;
  bool is_empty = false;

  ScorePopup(int score, SDL_Renderer *renderer, TTF_Font *font, const SDL_FPoint& center) : score_text(Text(font, renderer))
  {
    std::cout << "constructor" << std::endl;
    score_text.set(std::to_string(score), AQUA);
    this->center = center;
  }

  // ScorePopup &operator=(const ScorePopup &other)
  // {
  //   std::cout << "assigment operator" << std::endl;
  //   score_text = other.score_text;
  //   height = other.height;
  //   center = other.center;
  //   is_empty = other.is_empty;
  //   return *this;
  // }

  // ScorePopup(const ScorePopup &other)
  // {
  //   std::cout << "copy constructor" << std::endl;
  //   score_text = other.score_text;
  //   height = other.height;
  //   center = other.center;
  //   is_empty = other.is_empty;
  // }

  void render()
  {
    std::cout << "height increment" << std::endl;
    height += delta * speed;
    score_text.render_centered(SDL_FPoint{center.x, center.y - height});

    if (height >= MAX_HEIGHT)
    {
      score_text.set("", AQUA);
      is_empty = true;
    }
  }

  void destroy()
  {
    score_text.destroy();
  }
};