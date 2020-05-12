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

    void drawTriangleOutline(int x0, int y0, int x1, int y1, int x2, int y2, Color c0);
    void drawTriangleOutline(int x0, int y0, int x1, int y1, int x2, int y2, Color c0, Color c1, Color c2);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c0);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c0, Color c1, Color c2);

    void drawRectangleOutline(int x0, int y0, int width, int height, Color c0);
    void drawRectangleOutline(int x0, int y0, int width, int height, Color c0, Color c1, Color c2, Color c3);

    void drawString(int x, int y, std::string s);
    void drawString(int x, int y, std::string s, ...);

    void clearScreen();    
    void updateScreen();
    
};

#endif
