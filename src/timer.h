#pragma once
#include <chrono>

struct Timer 
{
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  
  std::chrono::milliseconds get_time_elapsed_ms()
  {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now() - start);
  }

  void restart()
  {
    start = std::chrono::steady_clock::now();
  }
};