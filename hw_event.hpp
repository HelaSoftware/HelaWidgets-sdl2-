
// used for pressed keys
struct HW_Event_Key {
   bool a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
   bool one, two, three, four, five, six, seven, eight, nine, zero;
   bool up, down, left, right;
};

// to be used for typed letters
struct HW_Event_Character {};

struct HW_Event_Mouse {
   bool left_button;
   bool right_button;
   bool middle_button;
};

class HW_Event {
public:
   HW_Event_Character character;
   HW_Event_Key key;
   HW_Event_Mouse mouse;

   void setEvents(SDL_Event& event) {
      if (event.type == SDL_KEYDOWN) {
         switch(event.key.keysym.sym) {
            case SDLK_a:
               key.a = true;
               break;
            case SDLK_b:
               key.b = true;
               break;
            case SDLK_c:
               key.c = true;
               break;
            case SDLK_d:
               key.d = true;
               break;
            case SDLK_e:
               key.e = true;
               break;
            case SDLK_f:
               key.f = true;
               break;
            case SDLK_g:
               key.g = true;
               break;
            case SDLK_h:
               key.h = true;
               break;
            case SDLK_i:
               key.i = true;
               break;
            case SDLK_j:
               key.j = true;
               break;
            case SDLK_k:
               key.k = true;
               break;
            case SDLK_l:
               key.l = true;
               break;
            case SDLK_m:
               key.m = true;
               break;
            case SDLK_n:
               key.n = true;
               break;
            case SDLK_o:
               key.o = true;
               break;
            case SDLK_p:
               key.p = true;
               break;
            case SDLK_q:
               key.q = true;
               break;
            case SDLK_r:
               key.r = true;
               break;
            case SDLK_s:
               key.s = true;
               break;
            case SDLK_t:
               key.t = true;
               break;
            case SDLK_u:
               key.u = true;
               break;
            case SDLK_v:
               key.v = true;
               break;
            case SDLK_w:
               key.w = true;
               break;
            case SDLK_x:
               key.x = true;
               break;
            case SDLK_y:
               key.y = true;
               break;
            case SDLK_z:
               key.z = true;
               break;
         }

         switch(event.key.keysym.sym) {
            case SDLK_1:
               key.one = true;
            case SDLK_2:
               key.two = true;
            case SDLK_3:
               key.three = true;
            case SDLK_4:
               key.four = true;
            case SDLK_5:
               key.five = true;
            case SDLK_6:
               key.six = true;
            case SDLK_7:
               key.seven = true;
            case SDLK_8:
               key.eight = true;
            case SDLK_9:
               key.nine = true;
            case SDLK_0:
               key.zero = true;
         }

         switch(event.key.keysym.sym) {
            case SDLK_LEFT:
               key.left = true;
               break;
            case SDLK_RIGHT:
               key.right = true;
               break;
         }

         switch(event.key.keysym.sym) {
            case SDLK_UP:
               key.up = true;
               break;
            case SDLK_DOWN:
               key.down = true;
               break;
         }
      }
   }

   void reset() {
      character = {};
      mouse = {};
      key = {};

      /*
      key.a = false;
      key.b = false;
      key.c = false;
      key.d = false;
      key.e = false;
      key.f = false;
      key.g = false;
      key.h = false;
      key.i = false;
      key.j = false;
      key.k = false;
      key.l = false;
      key.m = false;
      key.n = false;
      key.o = false;
      key.p = false;
      key.q = false;
      key.r = false;
      key.s = false;
      key.t = false;
      key.u = false;
      key.v = false;
      key.w = false;
      key.x = false;
      key.y = false;
      key.z = false;

      key.one = false;
      key.two = false;
      key.three = false;
      key.four = false;
      key.five = false;
      key.six = false;
      key.seven = false;
      key.eight = false;
      key.nine = false;
      key.zero = false;
      */
   }

private:
};
