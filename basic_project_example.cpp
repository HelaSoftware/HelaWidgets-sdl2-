#include "hw_window.hpp"

// compile with g++ image_viewer.cpp -o exe `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image

int main() {
   HW_Window window;

   while (window.running) {
      window.update();
      window.display();
   }
}
