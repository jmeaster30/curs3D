#include "engine.h"
#include <chrono>

int main()
{
  //fprintf(stderr, "starting\n");
  Engine* e = new Engine();
  
  double ups = 10.0;
  std::chrono::milliseconds ustep = std::chrono::milliseconds((long)((1 / ups) * 1000));

  auto old_time = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds accum = std::chrono::milliseconds(0);
  while(true)
  {
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto delta = curr_time - old_time;
    old_time = curr_time;
    accum += std::chrono::duration_cast<std::chrono::milliseconds>(delta);

    while(accum > ustep)
    {
      fprintf(stderr, "update\n");
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
