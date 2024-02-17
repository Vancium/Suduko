#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sys/syslimits.h>

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

  TTF_Init();

  m_Font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 24);

  if (m_Font == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
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
  DrawLines();
  SDL_SetRenderDrawColor(m_Renderer, m_Theme.background.r, m_Theme.background.g,
                         m_Theme.background.b, m_Theme.background.a);
  // DrawNumber(0, 0, 1);
  // SDL_RenderCopy(m_Renderer, m_Texture, NULL, &m_Rect);

  int cellHeight = SCREEN_HEIGHT / m_Game->GRID_SIZE;
  int cellWidth = SCREEN_WIDTH / m_Game->GRID_SIZE;

  for (int x = 0; x < m_Game->GRID_SIZE; x++) {
    for (int y = 0; y < m_Game->GRID_SIZE; y++) {
      DrawNumber(x * cellWidth, y * cellHeight, m_Game->GetCellValue(x, y));
      SDL_RenderCopy(m_Renderer, m_Texture, NULL, &m_Rect);
    }
  }

  SDL_RenderPresent(m_Renderer);
}

void Engine::DrawNumber(int x, int y, int val) {
  SDL_Surface *surface;
  char *num;

  SDL_Color textColor = {m_Theme.text.r, m_Theme.text.g, m_Theme.text.b,
                         m_Theme.text.a};

  switch (val) {
  case 1: {
    num = "1";
  } break;
  case 2: {
    num = "2";
  } break;
  case 3: {
    num = "3";
  } break;
  case 4: {
    num = "4";
  } break;
  case 5: {
    num = "5";
  } break;
  case 6: {
    num = "6";
  } break;
  case 7: {
    num = "7";
  } break;
  case 8: {
    num = "8";
  } break;
  case 9: {
    num = "9";
  } break;
  default:
    num = "0";
    break;
  }

  surface = TTF_RenderText_Solid(m_Font, num, textColor);

  m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
  SDL_FreeSurface(surface);

  m_Rect.x = x;
  m_Rect.y = y;
  m_Rect.w = SCREEN_WIDTH / m_Game->GRID_SIZE;
  m_Rect.h = SCREEN_HEIGHT / m_Game->GRID_SIZE;
}

void Engine::DrawLines() {
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
      m_Game->Solve();
    } break;
    }
  }
}

void Engine::Run() {
  m_Game->TestCase1();
  while (m_Running) {
    // Handle Events
    PollEvents();
    Render();
  }
}
