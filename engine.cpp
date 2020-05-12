#include "engine.h"

Engine::Engine()
{
  renderer = new Renderer();
    
  if(renderer == NULL)
  {
    fprintf(stderr, "renderer null\n");
  }
    
  x1 = 20;
  y1 = 10;
  vx1 = 1;
  vy1 = -1;

  x2 = 30;
  y2 = 20;
  vx2 = 1;
  vy2 = -1;

  x3 = 15;
  y3 = 15;
  vx3 = -1;
  vy3 = 1;

  col1 = new Color(1.0, 1.0, 0.0);
  col2 = new Color(0.5, 0.0, 0.5);
  col3 = new Color(0.0, 1.0, 1.0);
}

Engine::~Engine()
{
  delete renderer;
}

void Engine::update()
{
  if(x1 <= 0 || x1 >= renderer->getWidth() - 1)
  {
    vx1 *= -1;
  }
  if(y1 <= 0 || y1 >= renderer->getHeight() - 1)
  {
    vy1 *= -1;
  }

  if(x2 <= 0 || x2 >= renderer->getWidth() - 1)
  {
    vx2 *= -1;
  }
  if(y2 <= 0 || y2 >= renderer->getHeight() - 1)
  {
    vy2 *= -1;
  }
  
  if(x3 <= 0 || x3 >= renderer->getWidth() - 1)
  {
    vx3 *= -1;
  }
  if(y3 <= 0 || y3 >= renderer->getHeight() - 1)
  {
    vy3 *= -1;
  }
  
  x1 += vx1;
  y1 += vy1;

  x2 += vx2;
  y2 += vy2;

  x3 += vx3;
  y3 += vy3;
}

void Engine::render()
{
  renderer->clearScreen();
  
  //renderer->drawTriangleOutline(x1, y1, x2, y2, x3, y3, *col3);

  renderer->drawTriangle(x1, y1, x2, y2, x3, y3, *col1, *col2, *col3);
  
  //renderer->drawTriangleOutline(x1 + 15, y1, x2 + 15, y2, x3 + 15, y3, *col1, *col2, *col3);

  renderer->updateScreen();
}
