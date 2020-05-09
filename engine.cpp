#include "engine.h"

Engine::Engine()
{
  renderer = new Renderer();
  
  x1 = 20;
  y1 = 10;
  vx1 = 1;
  vy1 = -1;

  x2 = 30;
  y2 = 20;
  vx2 = 1;
  vy2 = -1;
  col = new Color(1.0, 1.0, 1.0);
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

  x1 += vx1;
  y1 += vy1;

  x2 += vx2;
  y2 += vy2;
}

void Engine::render()
{
  //renderer->clearScreen();

  renderer->drawLine(x1, y1, x2, y2, *col);
  
  renderer->updateScreen();
}
