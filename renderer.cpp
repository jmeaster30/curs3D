#include "renderer.h"

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
  raw(); //- for full control
  //cbreak() - to allow control characters to still send a signal
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

void Renderer::drawString(int x, int y, std::string s)
{
  if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    return;
  //mvprintw(0, 0, "%i %i", COLOR_BLACK, COLOR_WHITE);
  mvprintw(y, x, s.c_str());
}

void Renderer::updateScreen(){
  refresh();
}
