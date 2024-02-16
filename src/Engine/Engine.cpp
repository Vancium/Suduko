#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>

Engine::Engine() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Could not initialize SDL2" << std::endl;
  }
  m_Window =
      SDL_CreateWindow("Suduko", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (m_Window == nullptr) {
    std::cout << "Could not create SDL2 window" << std::endl;
  }

  m_Renderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (m_Renderer == nullptr) {
    std::cout << "Could not create SDL2 renderer" << std::endl;
  }

  // Initialize game
  m_Game = std::make_unique<Suduko>();

  // Set theme
  m_Theme.background = {22, 22, 22, 255};
  m_Theme.line = {44, 44, 44, 255};
  m_Theme.text = {255, 255, 255, 255};

  m_Running = true;
}

Engine::~Engine() { SDL_Quit(); }

void Engine::Render() {
  SDL_RenderClear(m_Renderer);
  RendererDrawLines();

  SDL_SetRenderDrawColor(m_Renderer, m_Theme.background.r, m_Theme.background.g,
                         m_Theme.background.b, m_Theme.background.a);

  SDL_RenderPresent(m_Renderer);
}

void Engine::RendererDrawLines() {
  int cellWidth = SCREEN_WIDTH / m_Game->GRID_SIZE;
  int cellHeight = SCREEN_HEIGHT / m_Game->GRID_SIZE;
  // Horizontal Lines
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    if (y != 0) {
      SDL_SetRenderDrawColor(m_Renderer, m_Theme.line.r, m_Theme.line.g,
                             m_Theme.line.b, m_Theme.line.a);

      if ((cellWidth * y) % 3 == 0) {
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
      }

      SDL_RenderDrawLine(m_Renderer, 0, cellWidth * y, SCREEN_WIDTH,
                         cellWidth * y);
    }
  }

  for (int x = 0; x < SCREEN_WIDTH; x++) {
    if (x != 0) {
      SDL_SetRenderDrawColor(m_Renderer, m_Theme.line.r, m_Theme.line.g,
                             m_Theme.line.b, m_Theme.line.a);

      if ((cellHeight * x) % 3 == 0) {
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
      }

      SDL_RenderDrawLine(m_Renderer, cellHeight * x, 0, cellHeight * x,
                         SCREEN_HEIGHT);
    }
  }
}

void Engine::PollEvents() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT: {
      m_Running = false;
    } break;
    case SDL_KEYDOWN: {
      m_Running = false;
    } break;
    }
  }
}

void Engine::Run() {
  while (m_Running) {
    // Handle Events
    PollEvents();
    Render();
  }
}
