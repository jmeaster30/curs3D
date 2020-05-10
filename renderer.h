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
    
    //helper functions for line drawing
    void drawLineLow(int x0, int y0, int x1, int y1, Color c);
    void drawLineLow(int x0, int y0, int x1, int y1, Color c0, Color c1);
    void drawLineHigh(int x0, int y0, int x1, int y1, Color c);
    void drawLineHigh(int x0, int y0, int x1, int y1, Color c0, Color c1);

  public:
    Renderer();
    ~Renderer();  

    void init();
    void destroy();
    
    int getWidth(){ return mWidth; };
    int getHeight(){ return mHeight; };

    int getColorPair(int fg, int bg);

    void drawPoint(int x, int y, Color c);
    
    void drawLine(int x0, int y0, int x1, int y1, Color c);
    void drawLine(int x0, int y0, int x1, int y1, Color c0, Color c1);

    void drawString(int x, int y, std::string s);
    void drawString(int x, int y, std::string s, ...);

    void clearScreen();    
    void updateScreen();
    
};

#endif
