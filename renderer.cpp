#include "renderer.h"

#include <cstdlib> // for abs()

Renderer::Renderer()
{
  init();
}

Renderer::~Renderer()
{
  destroy();
}

void Renderer::init(){
  initscr();
  getmaxyx(stdscr, mHeight, mWidth);
  noecho();
  curs_set(0); //hides the cursor
  //when we do input use
  //raw(); //- for full control
  cbreak(); // - to allow control characters to still send a signal
  //keypad(stdscr, TRUE) - allows reading function keys, arrow key, etc
  
  //initialize colors
  if(has_colors() == FALSE) {
    endwin();
    puts("color not available\n");
    exit(1); 
  }
  //initialize color pairs
  if(start_color() != OK)
  {
    puts("START COLOR ERROR\n");
    exit(1);
  }
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  clear();
}

void Renderer::destroy(){
  endwin();
}

void Renderer::drawPoint(int x, int y, Color c)
{
  if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    return;
  
  int color_pair = c.getColorPair();
  std::string sym = c.getSymbol();
  
  //mvprintw(0, 0, "%i %s", color_pair, sym.c_str());

  attron(COLOR_PAIR(color_pair));  
  mvprintw(y, x, sym.c_str());
  attroff(COLOR_PAIR(color_pair));
}

void Renderer::drawLine(int x0, int y0, int x1, int y1, Color c)
{
  int ydiff = abs(y1 - y0);
  int xdiff = abs(x1 - x0);
  if(ydiff < xdiff){
    if(x0 > x1){
      drawLineLow(x1, y1, x0, y0, c);
    } else {
      drawLineLow(x0, y0, x1, y1, c);
    }
  } else {
    if(y0 > y1){
      drawLineHigh(x1, y1, x0, y0, c);
    } else {
      drawLineHigh(x0, y0, x1, y1, c);
    }
  }
}

void Renderer::drawLineLow(int x0, int y0, int x1, int y1, Color c)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if(dy < 0)
  {
    yi = -1;
    dy = -dy;
  }
  int D = 2 * dy - dx;

  int x = x0;
  int y = y0;
  for(; x <= x1; x++)
  {
    drawPoint(x, y, c);
    if(D > 0)
    {
      y = y + yi;
      D = D - 2 * dx;
    }
    D = D + 2 * dy;
  }
}

void Renderer::drawLineHigh(int x0, int y0, int x1, int y1, Color c)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1; 
  if(dx < 0)
  {
    xi = -1;
    dx = -dx;
  }
  int D = 2 * dx - dy;
  
  int x = x0;
  int y = y0;
  for(; y <= y1; y++)
  {
    drawPoint(x, y, c);
    if(D > 0)
    {
      x = x + xi;
      D = D - 2 * dy;
    }
    D = D + 2 * dx;
  }
}

void Renderer::drawString(int x, int y, std::string s)
{
  if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    return;
  //mvprintw(0, 0, "%i %i", COLOR_BLACK, COLOR_WHITE);
  mvprintw(y, x, s.c_str());
}

void Renderer::drawString(int x, int y, std::string s, ...)
{
  va_list args;
  va_start(args, s);

  if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    return;
  //mvprintw(0, 0, "%i %i", COLOR_BLACK, COLOR_WHITE);
  move(y, x);
  vprintf(s.c_str(), args);
  va_end(args);
}

void Renderer::clearScreen(){
  erase(); //clear waits until the next refresh to clear the screen so we need to use erase
}

void Renderer::updateScreen(){
  refresh();
}
