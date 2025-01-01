#pragma once

#include <string>

class Line {
  std::string m_text;
  int m_number;

public:
  void set_text(std::string _text);
  std::string get_text();
  int get_line_number();
  void set_line_number(int);

  Line();
};
