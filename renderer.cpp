#include "renderer.h"

#include <cstdlib> // for abs()
#include <cmath>

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
    endwin();
    puts("START COLOR ERROR\n");
    exit(1);
  }

  if(can_change_color())
  {
    init_color(COLOR_BLACK,   0,    0,    0);
    init_color(COLOR_RED,     1000, 0,    0);
    init_color(COLOR_GREEN,   0,    1000, 0);
    init_color(COLOR_YELLOW,  1000, 1000, 0);
    init_color(COLOR_BLUE,    0,    0,    1000);
    init_color(COLOR_MAGENTA, 1000, 0,    1000);
    init_color(COLOR_CYAN,    0,    1000, 1000);
    init_color(COLOR_WHITE,   1000, 1000, 1000);
  }

  for(int fg = 0; fg < 8; fg++)
  {
    for(int bg = 0; bg < 8; bg++)
    {
      init_pair(fg + (bg << 3), fg, bg); // pair = fg + bg * 8;
    }
  }
  clear();
}

void Renderer::destroy(){
  endwin();
}


// draw a point on the screen
void Renderer::drawPoint(int x, int y, Color c)
{
  if(x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    return;
  
  int color_pair = c.getColorPair();
  std::string sym = c.getSymbol();
  
  attron(COLOR_PAIR(color_pair));  
  mvprintw(y, x, sym.c_str());
  attroff(COLOR_PAIR(color_pair));
}


// draw lines on the screen
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

void Renderer::drawLine(int x0, int y0, int x1, int y1, Color c0, Color c1)
{
  int ydiff = abs(y1 - y0);
  int xdiff = abs(x1 - x0);
  if(ydiff < xdiff){
    if(x0 > x1){
      drawLineLow(x1, y1, x0, y0, c1, c0);
    } else {
      drawLineLow(x0, y0, x1, y1, c0, c1);
    }
  } else {
    if(y0 > y1){
      drawLineHigh(x1, y1, x0, y0, c1, c0);
    } else {
      drawLineHigh(x0, y0, x1, y1, c0, c1);
    }
  }
}

void Renderer::drawLineLow(int x0, int y0, int x1, int y1, Color c0, Color c1)
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
  float b = 0;
  for(; x <= x1; x++)
  {
    float factor = (dx != 0) ? b / abs(dx) : 0.5;
    b++;
    Color* c = Color::blend(c1, c0, factor);
    drawPoint(x, y, *c);
    if(D > 0)
    {
      y = y + yi;
      D = D - 2 * dx;
    }
    D = D + 2 * dy;
  }
}

void Renderer::drawLineHigh(int x0, int y0, int x1, int y1, Color c0, Color c1)
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
  float b = 0;
  for(; y <= y1; y++)
  {
    float factor = (dy != 0) ? b / abs(dy) : 0.5;
    b++;
    Color* c = Color::blend(c1, c0, factor);
    drawPoint(x, y, *c);
    if(D > 0)
    {
      x = x + xi;
      D = D - 2 * dy;
    }
    D = D + 2 * dx;
  }
}

// function that draws triangles

void Renderer::drawTriangleOutline(int x0, int y0, int x1, int y1, int x2, int y2, Color c0)
{
  drawLine(x0, y0, x1, y1, c0);
  drawLine(x1, y1, x2, y2, c0);
  drawLine(x2, y2, x0, y0, c0);
}

void Renderer::drawTriangleOutline(int x0, int y0, int x1, int y1, int x2, int y2, Color c0, Color c1, Color c2)
{
  drawLine(x0, y0, x1, y1, c0, c1);
  drawLine(x1, y1, x2, y2, c1, c2);
  drawLine(x2, y2, x0, y0, c2, c0);
}

void Renderer::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c0)
{
  //helps make the triangle drawing more consistent
  Renderer::drawTriangleOutline(x0, y0, x1, y1, x2, y2, c0);

  //sort points
  int vx0 = x0;
  int vy0 = y0;
  int vx1 = x1;
  int vy1 = y1;
  int vx2 = x2;
  int vy2 = y2;

  if(vy0 > vy1){
    int tempx = vx0;
    int tempy = vy0;
    vx0 = vx1;
    vy0 = vy1;
    vx1 = tempx;
    vy1 = tempy;
  }
  if(vy0 > vy2){
    int tempx = vx0;
    int tempy = vy0;
    vx0 = vx2;
    vy0 = vy2;
    vx2 = tempx;
    vy2 = tempy;
  }
  if(vy1 > vy2){
    int tempx = vx1;
    int tempy = vy1;
    vx1 = vx2;
    vy1 = vy2;
    vx2 = tempx;
    vy2 = tempy;
  }

  if(vy0 == vy2) return; //dont draw zero height triangle
  
  //get slopes
  float s02 = (float)(vx2 - vx0) / (vy2 - vy0);
  float s12 = (float)(vx2 - vx1) / (vy2 - vy1);
  float s01 = (float)(vx1 - vx0) / (vy1 - vy0);

  float t = (float)(vy1 - vy0) / (vy2 - vy0);
  int vx3 = vx0 + std::round(t * (vx2 - vx0));
  int vy3 = vy1;
  int distance = vx3 - vx1;

  float left_slope = 0;
  float right_slope = 0;

  if(distance >= 0)
  {
    left_slope = s01;
    right_slope = s02;
  }
  else
  {
    left_slope = s02;
    right_slope = s01;
  }

  //draw top
  for(int y = vy0; y < vy1; y++)
  {
    int lx = std::round(left_slope * (y - vy0) + vx0);
    int rx = std::round(right_slope * (y - vy0) + vx0);
    drawLine(lx, y, rx, y, c0);
  }

  int left_start = vx1;
  int right_start = vx3;

  if(distance >= 0){
    left_slope = s12;
  } else {
    right_slope = s12;
    left_start = vx3;
    right_start = vx1;
  }

  //draw bottom
  for(int y = vy1; y < vy2; y++)
  {
    int lx = std::round(left_slope * (y - vy1) + left_start);
    int rx = std::round(right_slope * (y - vy1) + right_start);
    drawLine(lx, y, rx, y, c0);
  }
}

void Renderer::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c0, Color c1, Color c2)
{
  //fprintf(stderr, "start draw triangle\n");
  //helps make the drawing of triangles more consistent
  drawTriangleOutline(x0, y0, x1, y1, x2, y2, c0, c1, c2);
  
  //fprintf(stderr, "sort points\n");
  //sort points
  int vx0 = x0;
  int vy0 = y0;
  Color vc0 = c0;
  int vx1 = x1;
  int vy1 = y1;
  Color vc1 = c1;
  int vx2 = x2;
  int vy2 = y2;
  Color vc2 = c2;

  if(vy0 > vy1){
    int tempx = vx0;
    int tempy = vy0;
    Color tempc = vc0;
    vx0 = vx1;
    vy0 = vy1;
    vc0 = vc1;
    vx1 = tempx;
    vy1 = tempy;
    vc1 = tempc;
  }
  if(vy0 > vy2){
    int tempx = vx0;
    int tempy = vy0;
    Color tempc = vc0;
    vx0 = vx2;
    vy0 = vy2;
    vc0 = vc2;
    vx2 = tempx;
    vy2 = tempy;
    vc2 = tempc; 
  }
  if(vy1 > vy2){
    int tempx = vx1;
    int tempy = vy1;
    Color tempc = vc1;
    vx1 = vx2;
    vy1 = vy2;
    vc1 = vc2;
    vx2 = tempx;
    vy2 = tempy;
    vc2 = tempc;
  }

  if(vy0 == vy2) return; //dont draw zero height triangle
  
  //fprintf(stderr, "get slopes\n");
  //get slopes
  float s02 = (float)(vx2 - vx0) / (vy2 - vy0);
  float s12 = (float)(vx2 - vx1) / (vy2 - vy1);
  float s01 = (float)(vx1 - vx0) / (vy1 - vy0);

  //fprintf(stderr, "get vx3\n");
  float t = (float)(vy1 - vy0) / (vy2 - vy0);
  int vx3 = vx0 + std::round(t * (vx2 - vx0));
  int vy3 = vy1;
  Color* vc3 = Color::blend(vc0, vc2, t);
  int distance = vx3 - vx1;

  float left_slope = 0;
  float right_slope = 0;
  Color left_end_color = vc0;
  Color right_end_color = vc0;

  if(distance >= 0)
  {
    left_slope = s01;
    right_slope = s02;
    left_end_color = vc1;
    right_end_color = *vc3;
  }
  else
  {
    left_slope = s02;
    right_slope = s01;
    left_end_color = *vc3;
    right_end_color = vc1;
  }

  //fprintf(stderr, "draw top\n");
  //draw top
  for(int y = vy0; y < vy1; y++)
  {
    float weight_num = y - vy0;
    float weight_denom = vy1 - vy0;
    float weight = weight_num / weight_denom;

    //fprintf(stderr, "left color w_n: %f w_d: %f\n", weight_num, weight_denom);
    Color* lc = Color::blend(vc0, left_end_color, weight);
    int lx = std::round(left_slope * (y - vy0) + vx0);
    //fprintf(stderr, "lc: %f %f %f\n", lc->red(), lc->green(), lc->blue());

    //fprintf(stderr, "right color\n");
    Color* rc = Color::blend(vc0, right_end_color, weight);
    int rx = std::round(right_slope * (y - vy0) + vx0);
    //fprintf(stderr, "rc: %f %f %f\n", rc->red(), rc->green(), rc->blue());

    //fprintf(stderr, "draw the line\n");
    drawLine(lx, y, rx, y, *lc, *rc);

    //fprintf(stderr, "cleanup\n");
    delete lc;
    delete rc;
  }
  //fprintf(stderr, "end draw top\n");

  int left_start = vx1;
  int right_start = vx3;

  if(distance >= 0){
    left_slope = s12;
  } else {
    right_slope = s12;
    left_start = vx3;
    right_start = vx1;
  }

  //fprintf(stderr, "draw bottom\n");
  //draw bottom
  for(int y = vy1; y < vy2; y++)
  {
    float weight = (float)(y - vy1) / (vy2 - vy1);

    Color* lc = Color::blend(left_end_color, vc2, weight);
    int lx = std::round(left_slope * (y - vy1) + left_start);
    
    Color* rc = Color::blend(right_end_color, vc2, weight);
    int rx = std::round(right_slope * (y - vy1) + right_start);
    
    drawLine(lx, y, rx, y, *lc, *rc);

    delete lc;
    delete rc;
  }

  delete vc3; //clean up color
  //fprintf(stderr, "end draw triangle\n");
}

// functions that draw rectangles
void Renderer::drawRectangleOutline(int x0, int y0, int width, int height, Color c0)
{
}

void Renderer::drawRectangleOutline(int x0, int y0, int width, int height, Color c0, Color c1, Color c2, Color c3)
{
}

// functions that draw a string to the screen
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
