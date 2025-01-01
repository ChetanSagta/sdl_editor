#include "editor.h"
#include "SDL_keycode.h"
#include <iostream>
#include <vector>

void Editor::init() {

  // m_current_line = get_current_line();
  m_lines = new std::vector<Line>();
  m_current_line = new Line();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return;
  }

  if (TTF_Init() < 0) {
    std::cout << "Error Initialiazing SDL TTF" << TTF_GetError() << std::endl;
    return;
  }

  m_font = TTF_OpenFont("resources/InconsolataNerdFont-Regular.ttf", 24);
  if (!m_font) {
    std::cout << "Could not load font. Error: " << TTF_GetError() << std::endl;
    return;
  }

  m_text_surface = TTF_RenderText_Solid(
      m_font, m_current_line->get_text().c_str(), m_text_color);
  if (!m_text_surface) {
    std::cout << "Couldn't render text: " << TTF_GetError() << std::endl;
    return;
  }

  m_window =
      SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

  if (!m_window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return;
  }

  m_win_surface = SDL_GetWindowSurface(m_window);

  if (!m_win_surface) {
    std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
    return;
  }
}

void Editor::event_loop() {

  while (m_running) {

    std::string text = m_current_line->get_text();

    while (SDL_PollEvent(&m_ev) != 0) {
      switch (m_ev.type) {
      case SDL_QUIT:
        m_running = false;
      case SDL_KEYDOWN: {
        switch (m_ev.key.keysym.sym) {
        case SDLK_ESCAPE:
          m_running = false;
          break;
        case SDLK_BACKSPACE:
          m_current_line->set_text(text.substr(0, text.length() - 1));
          break;
        case SDLK_RETURN:
          add_new_line();
          break;
        }
      } break;
      case SDL_TEXTINPUT:
        text.append(m_ev.text.text);
        m_current_line->set_text(text);
        break;
      }
      m_current_line = get_current_line();
    }
        m_text_surface =
            TTF_RenderText_Solid(m_font, m_current_line->get_text().c_str(), m_text_color);
      SDL_Rect text_rect = {0, 0, m_text_surface->w, m_text_surface->h};
      SDL_Rect dest_rect = {0, m_current_line->get_line_number() * m_text_surface->h,
                              m_text_surface->h, m_text_surface->w};
      SDL_BlitSurface(m_text_surface, &text_rect, m_win_surface,&dest_rect);
      for (Line line : *m_lines) {
        m_text_surface =
            TTF_RenderText_Solid(m_font, line.get_text().c_str(), m_text_color);
        text_rect = {0, 0, m_text_surface->w, m_text_surface->h};
        dest_rect = {0, line.get_line_number() * m_text_surface->h,
                              m_text_surface->h, m_text_surface->w};
        SDL_BlitSurface(m_text_surface, &text_rect, m_win_surface, &dest_rect);
      }
    SDL_UpdateWindowSurface(m_window);
    SDL_FillRect(m_win_surface, nullptr, 0);
  }
}

void Editor::cleanup() {
  SDL_FreeSurface(m_win_surface);
  SDL_DestroyWindow(m_window);

  SDL_Quit();
}

void Editor::move_cursor_down() {
  this->m_cursor->setY(this->m_cursor->getY() + 1);
}

void Editor::move_cursor_up() {
  this->m_cursor->setY(this->m_cursor->getY() - 1);
}

void Editor::move_cursor_right() {
  this->m_cursor->setX(this->m_cursor->getX() + 1);
}

void Editor::move_cursor_left() {
  this->m_cursor->setX(this->m_cursor->getX() - 1);
}

Line *Editor::get_current_line() { return m_current_line; }

void Editor::add_new_line() {
  m_lines->push_back(*m_current_line);
  m_current_line = new Line();
  m_current_line->set_line_number(m_lines->size());
}
