#include "color.h"

#include <cmath>
#include <stdlib.h>

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7

void Color::calculate()
{  
  float fg_value = (fg_channel == 0) ? r : ((fg_channel == 1) ? g : b);
  
  //color calculation
  std::string fg_percent[11] = {" ", ".", ":", "-", "=", "+", "*", "#", "%", "@", ""};
  int fg_index = (int)floor(11 * fg_value);

  sym = fg_percent[fg_index];

  float bg_val1 = (fg_channel == 0) ? g : ((fg_channel == 1) ? b : r);
  float bg_val2 = (fg_channel == 0) ? b : ((fg_channel == 1) ? r : g);

  bool fg_flag = fg_value >= 0.5;
  bool bg_flag1 = bg_val1 >= 0.5;
  bool bg_flag2 = bg_val2 >= 0.5;

  if(fg_channel == 0)
  {
    fg = (int)fg_flag;
    bg = ((((0 | (int)bg_flag2) << 1) | (int)bg_flag1) << 1) & 0;
  }
  else if(fg_channel == 1)
  {
    fg = (int)fg_flag << 1;
    bg = ((((0 | (int)bg_flag1) << 1) & 0) << 1) | (int)bg_flag2;
  }
  else if(fg_channel == 2)
  {
    fg = (int)fg_flag << 2;
    bg = (((0 << 1) | (int) bg_flag2) << 1) | (int) bg_flag1;
  }

  if(sym.compare("") == 0)
  {
    bg |= fg;
    fg = COLOR_WHITE;
    sym = " ";
  }
}

Color::Color(float _r, float _g, float _b)
{
  r = _r;
  g = _g;
  b = _b;
  
  fg_channel = rand() % 3;
  
  calculate();

  //fprintf(stderr, "herejjj\n");
}

Color::~Color(){}

int Color::getColorPair(){
  return fg + (8 * bg);
}

std::string Color::getSymbol(){ 
    return sym;
}

