#include "color.h"

#include <algorithm> //std::max
#include <cmath>
#include <stdlib.h>
#include <cstring>
//short grayscale
// .:-=+*#%@
//long grayscale
// .'`^",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$
//

/* COLORS */
void Color::calculate()
{   
  float tolerance = 0.3;
  //float value = (0.3 * r) + (0.59 * g) + (0.11 * b); 
  float value = std::max(r, std::max(g, b));

  const char* symscale = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
  int scale_len = strlen(symscale);
  int index = floor(value * (scale_len + 1));

  bool rb = abs(value - r) < tolerance;
  bool gb = abs(value - g) < tolerance;
  bool bb = abs(value - b) < tolerance;
  
  fg = ((((0 | bb) << 1) | gb) << 1) | rb;
  bg = 0;
   
  if(index >= scale_len)
  {
    sym = " ";
    bg = fg;
    fg = 0;
  }
  else
  {
    sym = symscale[index];
  }
  //fprintf(stderr, "fg: %i bg: %i sym: '%c'\n", fg, bg, sym);
}/**/

/* GRAYSCALE COLORS 
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
}/**/

Color::Color(float _v)
{
  r = _v;
  g = _v;
  b = _v;

  calculate();
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

Color* Color::blend(Color c0, Color c1, float factor)
{
  //fprintf(stderr, "begin blend\n");
  if(factor > 1) factor = 1;
  if(factor < 0) factor = 0;
  float inv = 1 - factor;
  //fprintf(stderr, "r %f g %f b %f <%f-%f> r %f g %f b %f\n", c0.r, c0.g, c0.b, factor, inv, c1.r, c1.g, c1.b);
  float r = (c0.r * factor) + (c1.r * inv);
  float g = (c0.g * factor) + (c1.g * inv);
  float b = (c0.b * factor) + (c1.b * inv);
  //fprintf(stderr, "end blend\n");
  return new Color(r, g, b);
}

int Color::getColorPair(){
  return fg + (bg << 3);
}

std::string Color::getSymbol(){ 
    return sym;
}
