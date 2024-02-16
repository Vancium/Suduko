#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <cstdio>
#include <memory>

Engine::Engine() {
  // Initialize SDL
  /*
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
  */

  // Initialize game
  m_Game = std::make_unique<Suduko>();

  m_Running = true;
}

Engine::~Engine() { SDL_Quit(); }

void Engine::Render() {
  // SDL_RenderClear(m_Renderer);
  // SDL_SetRenderDrawColor(m_Renderer, 22, 22, 22, 225);

  // Draw lines

  // SDL_RenderPresent(m_Renderer);
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
  m_Game->TestCase1();
  m_Game->PrintGrid();

  printf("Valid Suduko: %d\n", m_Game->ValidSuduko());
  m_Game->Solve();
  m_Game->PrintGrid();
  printf("Valid Suduko: %d\n", m_Game->ValidSuduko());
}
