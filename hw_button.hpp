

class HW_Button : public HW_Label {
public:
   bool was_clicked;

   bool checkClick(int mouse_x, int mouse_y) {
      if (mouse_x > x1 && mouse_x < x2) {
         if (mouse_y > y1 && mouse_y < y2) {
            return true;
         }
      }
      return false;
   }
};
