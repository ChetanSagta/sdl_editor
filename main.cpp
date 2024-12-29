#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include <SDL.h>
#include <iostream>
#include <string.h>

class _SDL {

public:
  void init();
  void eventLoop();
  void cleanup();

private:
  SDL_Surface *winSurface = NULL;
  SDL_Window *window = NULL;
  TTF_Font *font = nullptr;
  SDL_Surface *text_surface = nullptr;

  std::string text = " ";
  SDL_Event ev;
  bool running = true;
  SDL_Color text_color = {0, 0, 255};
};

void _SDL::init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return;
  }

  if (TTF_Init() < 0) {
    std::cout << "Error Initialiazing SDL TTF" << TTF_GetError() << std::endl;
    return;
  }

  font = TTF_OpenFont("resources/InconsolataNerdFont-Regular.ttf", 24);
  if (!font) {
    std::cout << "Could not load font. Error: " << TTF_GetError() << std::endl;
    return;
  }

  text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
  if (!text_surface) {
    std::cout << "Couldn't render text: " << TTF_GetError() << std::endl;
    return;
  }

  window =
      SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return;
  }

  winSurface = SDL_GetWindowSurface(window);

  if (!winSurface) {
    std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
    return;
  }
}

void _SDL::eventLoop() {

  SDL_Rect text_rect = {0, 0, text_surface->w, text_surface->h};

  SDL_BlitSurface(text_surface, &text_rect, winSurface, nullptr);

  while (running) {

    while (SDL_PollEvent(&ev) != 0) {
      switch (ev.type) {
      case SDL_QUIT:
        running = false;
      case SDL_KEYDOWN: {
        switch (ev.key.keysym.sym) {
        case SDLK_ESCAPE:
		  running = false;
          break;
		case SDLK_BACKSPACE:
		  text = text.substr(0, text.length() - 1);
		  break;
		}
	  } break;
	  case SDL_TEXTINPUT:
		text.append(ev.text.text);
		break;
	  }
	}

    text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    text_rect = {0, 0, text_surface->w, text_surface->h};
    SDL_BlitSurface(text_surface, &text_rect, winSurface, nullptr);
    SDL_UpdateWindowSurface(window);
	SDL_FillRect(winSurface, nullptr, 0);
  }
}

void _SDL::cleanup() {
  SDL_FreeSurface(winSurface);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

int main() {

  _SDL sdl;
  sdl.init();
  sdl.eventLoop();
  sdl.cleanup();
  return 0;
}
