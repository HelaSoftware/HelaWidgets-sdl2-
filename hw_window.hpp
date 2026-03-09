#include <vector>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

void HW_INIT() {
   SDL_Init(SDL_INIT_VIDEO);
   TTF_Init();
   IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP);
}

struct HW_Color {
   unsigned char r, g, b, a;
};

#include "hw_event.hpp"
#include "hw_image.hpp"
#include "hw_label.hpp"
#include "hw_button.hpp"
#include "hw_checkbox.hpp"

class HW_Window {
public:
   bool running;
   int width, height;
   int minimum_window_width, minimum_window_height;
   std::string title;

   HW_Event events;

   HW_Window() {
      HW_INIT();

      root = SDL_CreateWindow("m",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              200, 200,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

      renderer = SDL_CreateRenderer(root, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      running = true;
      setWidthAndHeight(1280, 720);
      setMinimumWidthAndHeight(400, 400);
      setTitle("hw default");
      setFrameRate(60);

      setBackgroundColor(255, 255, 255, 255);
   }

   void setWidthAndHeight(int new_width, int new_height) {
      this->width = new_width;
      this->height = new_height;
      SDL_SetWindowSize(root, width, height);
   }

   void setMinimumWidthAndHeight(int new_minimum_width, int new_minimum_height) {
      this->minimum_window_width = new_minimum_width;
      this->minimum_window_height = new_minimum_height;
   }

   void setTitle(std::string new_title) {
      this->title = new_title;
      SDL_SetWindowTitle(root, title.c_str());
   }

   void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
      this->background_color.r = r;
      this->background_color.g = g;
      this->background_color.b = b;
      this->background_color.a = a;
   }

   void setFrameRate(float framerate) {
      this->framerate = framerate;
   }

   void update() {
      events.reset();
      for (HW_Button*& button : buttons) {
         button->was_clicked = false;
      }

      while (SDL_PollEvent(&event)) {
         events.setEvents(event);
         if (event.type == SDL_QUIT) {
            running = false;
         }
         if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
               width = event.window.data1;
               height = event.window.data2;
               if (width < minimum_window_width) {
                  setWidthAndHeight(minimum_window_width, this->height);
               }
               if (height < minimum_window_height) {
                  setWidthAndHeight(this->width, minimum_window_height);
               }
            }
         }
         if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
               for (HW_Button*& button : buttons) {
                  button->was_clicked = button->checkClick(event.button.x, event.button.y);
               }
               for (HW_CheckBox*& checkbox : checkboxes) {
                  checkbox->checkClick(event.button.x, event.button.y);
               }
            }
         }
      }
   }

   void display() {
      SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
      SDL_RenderClear(renderer);

      for (HW_Label*& label : labels) {
         label->draw(renderer);
      }
      for (HW_Button*& button : buttons) {
         button->draw(renderer);
      }
      for (HW_CheckBox*& checkbox : checkboxes) {
         checkbox->draw(renderer);
      }
      for (HW_DisplayImage*& display_image : display_images) {
         display_image->draw(renderer);
      }

      SDL_RenderPresent(renderer);
      SDL_Delay((1000.f / framerate));
   }

   void add(HW_Label& label) {
      labels.push_back(&label);
   }

   void add(HW_Button& button) {
      buttons.push_back(&button);
   }

   void add(HW_CheckBox& checkbox) {
      checkboxes.push_back(&checkbox);
   }

   void add(HW_DisplayImage& display_image) {
      display_images.push_back(&display_image);
   }

   void remove(HW_Label& label) {
      for (int i = 0; i < labels.size(); i++) {
         if (labels[i] == &label) {
            labels.erase(labels.begin() + i);
         }
      }
   }

   void remove(HW_Button& button) {
      for (int i = 0; i < buttons.size(); i++) {
         if (buttons[i] == &button) {
            buttons.erase(buttons.begin() + i);
         }
      }
   }

   void remove(HW_CheckBox& checkbox) {
      for (int i = 0; i < checkboxes.size(); i++) {
         if (checkboxes[i] == &checkbox) {
            checkboxes.erase(checkboxes.begin() + i);
         }
      }
   }

   void remove(HW_DisplayImage& display_image) {
      for (int i = 0; i < display_images.size(); i++) {
         if (display_images[i] == &display_image) {
            display_images.erase(display_images.begin() + i);
         }
      }
   }

   HW_Event getEvents() {
      HW_Event new_events = events;
      return new_events;
   }

   ~HW_Window() {
      for (HW_Label*& label : labels) {
         label->del();
      }
      for (HW_Button*& button : buttons) {
         button->del();
      }

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(root);
   }

private:
   std::vector<HW_Label*> labels;
   std::vector<HW_Button*> buttons;
   std::vector<HW_CheckBox*> checkboxes;
   std::vector<HW_DisplayImage*> display_images;
   float framerate;
   HW_Color background_color;
   SDL_Event event;
   SDL_Window* root;
   SDL_Renderer* renderer;
};
