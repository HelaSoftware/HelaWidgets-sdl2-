

class HW_CheckBox : public HW_Label {
public:
   bool is_selected;
   bool check_needs_updating;
   SDL_Rect check_rect;
   SDL_Texture* check_texture;
   std::string check_texture_path;
   
   HW_CheckBox() {
      is_selected = false;
      check_texture_path = "check.png";
      check_needs_updating = true;

      setText(" ");
      setOutlineThickness(5);
   }

   void setCheckTexture(SDL_Renderer* renderer) {
      SDL_Surface* surface = IMG_Load(check_texture_path.c_str());
      if (!surface) {
         std::cout << "and\n";
         return;
      }
      check_texture = SDL_CreateTextureFromSurface(renderer, surface);

      check_rect.w = surface->w;
      check_rect.h = surface->h;

      SDL_FreeSurface(surface);
      updateCheckRect();

      check_needs_updating = false;
   }

   void checkClick(int mouse_x, int mouse_y) {
      if (mouse_x > x1 && mouse_x < x2) {
         if (mouse_y > y1 && mouse_y < y2) {
            if (is_selected == true) {
               is_selected = false;
               return;
            } else {
               is_selected = true;
               return;
            }
         }
      }
   }

   void draw(SDL_Renderer* renderer) {
      SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
      SDL_RenderFillRect(renderer, &background_rect);

      SDL_SetRenderDrawColor(renderer, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
      for (int i = 0; i < outline_thickness; i++) {
         SDL_Rect outline_rect;
         outline_rect.x = x1 + i;
         outline_rect.y = y1 + i;
         outline_rect.w = width - (i * 2);
         outline_rect.h = height - (i * 2);
         SDL_RenderDrawRect(renderer, &outline_rect);
      }

      if (text_needs_editing) {
         updateText(renderer);
      }
      if (check_needs_updating) {
         setCheckTexture(renderer);
      }

      SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

      if (is_selected) {
         SDL_RenderCopy(renderer, check_texture, NULL, &check_rect);
      }
   }

   ~HW_CheckBox() {
      if (check_texture != nullptr) {
         SDL_DestroyTexture(check_texture);
      }
   }

private:
   void updateCheckRect() {
      check_rect.x = x1 + ((width - check_rect.w) / 2);
      check_rect.y = y1 + ((height - check_rect.h) / 2);
   }
};
