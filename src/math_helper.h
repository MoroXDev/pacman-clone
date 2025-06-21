#pragma once
#include "math.h"

static float distf(float x, float y, float x2, float y2)
{
  return sqrt(powf(x2 - x, 2) + powf(y2 - y, 2));
}