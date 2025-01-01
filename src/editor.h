#pragma once

#include <SDL.h>
#include<SDL_ttf.h>
#include <string>
#include <vector>
#include "line.h"
#include "cursor.h"

class Editor{

 public:
  void init();
  void event_loop();
  void cleanup();
  void add_new_line();
  void delete_line();
  void move_cursor_down();
  void move_cursor_up();
  void move_cursor_right();
  void move_cursor_left();

  Line* get_current_line();

 private:
  SDL_Surface *m_win_surface = NULL;
  SDL_Window *m_window = NULL;
  TTF_Font *m_font = nullptr;
  SDL_Surface *m_text_surface = nullptr;

  SDL_Event m_ev;
  bool m_running = true;
  SDL_Color m_text_color = {0, 0, 255};

  std::vector<Line>* m_lines;

  Line* m_current_line;
  Cursor *m_cursor;

};
