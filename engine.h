#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "renderer.h"

class Engine{

  private:
    int x1;
    int y1;
    int vx1;
    int vy1;

    int x2;
    int y2;
    int vx2;
    int vy2;

    int x3;
    int y3;
    int vx3;
    int vy3;
    
    Color* col1;
    Color* col2;
    Color* col3;

    Renderer* renderer;

  public:
    Engine();
    ~Engine();

    void render();
    void update(); 
};

#endif

