#pragma once

class Cursor {
  public :
  void setX(int);
  void setY(int);
  int getX();
  int getY();
  Cursor();
 private:
  int x;
  int y;
};
