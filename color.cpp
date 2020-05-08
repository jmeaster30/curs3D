#include "color.h"

#include <cmath>
#include <stdlib.h>
#include <cstring>

//short grayscale
// .:-=+*#%@
//long grayscale
// .'`^",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$

/*
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
}*/

void Color::calculate()
{
  float grayscale = (0.3 * r) + (0.59 * g) + (0.11 * b);

  const char* symscale = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
  int scale_len = strlen(symscale);

  int index = floor(grayscale * (scale_len + 1));

  if(index >= scale_len)
  {
    sym = " ";
    bg = 2;
  }
  else
  {
    sym = symscale[index];
    bg = 1;
  }
}

Color::Color(float _r, float _g, float _b)
{
  r = _r;
  g = _g;
  b = _b;
  
  /*if(r < g)
  {
    if(r < b)
    {
      fg_channel = 0;
    }
    else
    {
      fg_channel = 2;
    }
  }
  else
  {
    if(g < b)
    {
      fg_channel = 1;
    }
    else
    {
      fg_channel = 2;
    }
  }*/
  
  calculate();

  //fprintf(stderr, "herejjj\n");
}

Color::~Color(){}

int Color::getColorPair(){
  return bg;
}

std::string Color::getSymbol(){ 
    return sym;
}
