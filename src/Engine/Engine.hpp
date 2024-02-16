#pragma once
#include "../Suduko/Suduko.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <memory>

typedef struct Theme {
  SDL_Color background;
  SDL_Color line;
  SDL_Color text;
} Theme_t;

class Engine {
public:
  Engine();
  ~Engine();
  void Run();
  static constexpr int SCREEN_WIDTH = 720;
  static constexpr int SCREEN_HEIGHT = 720;

private:
  void Render();
  void PollEvents();
  void RendererDrawLines();

private:
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;

  std::unique_ptr<Suduko> m_Game;
  bool m_Running = false;
  Theme_t m_Theme;
};
