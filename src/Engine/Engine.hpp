#pragma once
#include "../Suduko/Suduko.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <array>
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
  void DrawLines();
  void DrawNumber(int x, int y, int val);

private:
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  SDL_Texture *m_Texture;
  SDL_Rect m_Rect;
  TTF_Font *m_Font;

  std::array<SDL_Texture *, 81> m_Textures;

  std::unique_ptr<Suduko> m_Game;
  bool m_Running = false;
  Theme_t m_Theme;
};
