#include <iostream>
#include "window.hpp"

int main() {
   HW_Window window;

   HW_DisplayImage display_image;
   window.add(display_image);

   while (window.running) {
      window.update();
      window.display();
   }
}
