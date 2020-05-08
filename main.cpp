#include "renderer.h"

int main()
{
  Renderer* r = new Renderer();
  
  //Color* color = new Color(1.0, 0.0, 0.0);

  for(float x = 0; x < r->getWidth(); x++)
  {
    for(float y = 0; y < r->getHeight(); y++)
    {
      float red = x / r->getWidth();
      float green = y / r->getHeight();
      //fprintf(stderr, "%d %d\n", red, green);
      Color* c = new Color(red, green, 0.5);
      r->drawPoint(x, y, *c);
      delete c;
    }
  }  
 
  r->updateScreen();

  getch(); // wait for user input
  
  delete r;

  return 0;
}
