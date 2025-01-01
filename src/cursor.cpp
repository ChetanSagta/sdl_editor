#include "cursor.h"

Cursor::Cursor() {
  this->x = 0;
  this-> y = 0;
}
  

void Cursor::setX(int _x) {
  this->x = _x;
}
void Cursor::setY(int _y) {
  this->y = _y;
}
  
int Cursor::getX() {
  return this->x;
}
int Cursor::getY() {
  return this->y;
}
