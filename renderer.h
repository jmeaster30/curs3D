#ifndef __RENDERER_HPP__
#define __RENDERER_HPP___

#include <ncurses.h>
#include "color.h"
#include <string>

class Renderer
{
  private:
    int mWidth;
    int mHeight;
        
    bool color;

  public:
    Renderer();
    ~Renderer();  

    void init();
    void destroy();
    
    int getWidth(){ return mWidth; };
    int getHeight(){ return mHeight; };

    int getColorPair(int fg, int bg);

    void drawPoint(int x, int y, Color s);
    void drawString(int x, int y, std::string string);
    
    void updateScreen();
    
};

#endif
