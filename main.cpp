#include "engine.h"
#include <chrono>

int main()
{
  //fprintf(stderr, "starting\n");
  Engine* e = new Engine();
  
  double ups = 30.0;
  long ustep = (long)((1 / ups) * 1000000);

  auto old_time = std::chrono::high_resolution_clock::now();
  long accum = 0;
  while(true)
  {
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto delta = curr_time - old_time;
    old_time = curr_time;
    accum += std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
    //fprintf(stderr, "%i accum - %i ustep\n", accum, ustep);

    while(accum >= ustep)
    {
      //fprintf(stderr, "update\n");
      e->update();
      accum -= ustep;
    }

    //fprintf(stderr, "render\n"); 
    e->render();
  }
  //fprintf(stderr, "done\n");
  //getch(); // wait for user input
  
  delete e;

  return 0;
}
