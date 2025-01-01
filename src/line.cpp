#include "line.h"
#include <iostream>

void Line::set_text(std::string _text) {
  this-> m_text = _text;
}

void Line::set_line_number(int number) {
  this->m_number= number;
}

std::string Line::get_text() {
  return this->m_text;
}

Line::Line() {
  m_text = " ";
}

int Line::get_line_number() {
  return this->m_number;
}
