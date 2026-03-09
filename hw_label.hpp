

class HW_Label {
public:
   std::string text;
   std::string current_font_path;
   bool text_needs_editing;
   int x1, y1, x2, y2;
   int width, height;
   int center_x, center_y;
   int text_size;
   unsigned int outline_thickness;

   SDL_Rect background_rect;
   HW_Color background_color;
   HW_Color outline_color;

   TTF_Font* font;

   HW_Color text_color;
   SDL_Rect text_rect;
   SDL_Texture* text_texture;

   HW_Label() {
      text_texture = nullptr;
      text_needs_editing = false;

      setTextSize(15);
      setFont(); // put a font path here
      setBounds(100, 100, 200, 200);
      setOutlineThickness(0);
      setOutlineColor(0, 0, 0, 255);
      setText("NULL");
      setBackgroundColor(255, 255, 0, 255);
   }

   void setBounds(int x1, int y1, int x2, int y2) {
      this->x1 = x1;
      this->y1 = y1;
      this->x2 = x2;
      this->y2 = y2;
      
      this->width = x2 - x1;
      this->height = y2 - y1;

      this->center_x = x1 + ((x2 - x1) / 2);
      this->center_y = y1 + ((y2 - y1) / 2);

      updatePosition();
   }

   void setOutlineThickness(unsigned int outline_thickness) {
      this->outline_thickness = outline_thickness;
   }

   void setTextSize(int text_size) {
      this->text_size = text_size;
   }

   void setFont(std::string font_path) {
      current_font_path = font_path;
      
      this->font = TTF_OpenFont(current_font_path.c_str(), text_size);
      if (!font) {}
   }

   void setText(std::string text) {
      this->text = text;
      this->text_needs_editing = true;
   }

   void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
      background_color.r = r;
      background_color.g = g;
      background_color.b = b;
      background_color.a = a;
      this->text_needs_editing = true;
   }

   void setOutlineColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
      outline_color.r = r;
      outline_color.g = g;
      outline_color.b = b;
      outline_color.a = a;
   }

   void setTextColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
      text_color.r = r;
      text_color.g = g;
      text_color.b = b;
      text_color.a = a;
      this->text_needs_editing = true;
   }

   virtual void draw(SDL_Renderer* renderer) {
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
      
         SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
   }

   void del() {
      if (text_texture != nullptr) {
         SDL_DestroyTexture(text_texture);
      }
   }

   void updateText(SDL_Renderer* renderer) {
      del();

      SDL_Color sdl_text_color = {text_color.r, text_color.g, text_color.b, text_color.a};
      SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), sdl_text_color);

      text_rect.x = center_x - (surface->w / 2);
      text_rect.y = center_y - (surface->h / 2);
      text_rect.w = surface->w;
      text_rect.h = surface->h;

      text_texture = SDL_CreateTextureFromSurface(renderer, surface);

      SDL_FreeSurface(surface);

      text_needs_editing = false;
   }

private:
   void updatePosition() {
      this->background_rect.x = x1;
      this->background_rect.y = y1;
      this->background_rect.w = width;
      this->background_rect.h = height;

      this->text_needs_editing = true;
   }
};
