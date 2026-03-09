

class HW_DisplayImage {
public:
   int x1, y1, x2, y2;
   int width, height;
   int center_x, center_y;
   bool texture_needs_updating;
   bool is_visible;
   SDL_Rect image_rect;
   SDL_Texture* image_texture;

   std::string image_path;

   HW_DisplayImage() {
      is_visible = true;
      setImage("err.png");
      setBounds(100, 100);
   }

   HW_DisplayImage(std::string new_image_path) {
      is_visible = true;
      setImage(new_image_path);
      setBounds(100, 100);
   }

   void setBounds(int x, int y) {
      SDL_Surface* surface = IMG_Load(image_path.c_str());
      x1 = x;
      y1 = y;
      x2 = x + surface->w;
      y2 = y + surface->h;
      width = surface->w;
      height = surface->h;
      center_x = x1 + (width / 2);
      center_y = y1 + (height / 2);
      SDL_FreeSurface(surface);
      updateTextureRect();
      texture_needs_updating = true;
   }

   void setImage(std::string image_path) {
      this->image_path = image_path;
      texture_needs_updating = true;
   }

   void draw(SDL_Renderer* renderer) {
      if (texture_needs_updating) {
         updateTexture(renderer);
      }
      if (is_visible) {
         SDL_RenderCopy(renderer, image_texture, NULL, &image_rect);
      }
   }

private:
   void updateTexture(SDL_Renderer* renderer) {
      SDL_Surface* surface = IMG_Load(image_path.c_str());
      image_texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);
      texture_needs_updating = false;
   }

   void updateTextureRect() {
      image_rect.x = x1;
      image_rect.y = y1;
      image_rect.w = width;
      image_rect.h = height;
   }
};
