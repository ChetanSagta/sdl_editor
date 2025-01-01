#include <SDL.h>
#include <iostream>
#include <string.h>
#include"editor.h"

int main() {

  Editor sdl;
  sdl.init();
  sdl.event_loop();
  sdl.cleanup();
  return 0;
}
