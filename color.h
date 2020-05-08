#ifndef __COLOR_H__
#define __COLOR_H__

//black->white string (10-levels) there are more detailed ones
//"@%#*+=-:. "

#include <string>

class Color{
  private:
    float r;
    float g;
    float b;

    int fg_channel;

    int bg;
    int fg;
    std::string sym;
    
    void calculate();

  public:
    Color(float _r, float _g, float _b);
    ~Color();    

    int getColorPair();
    std::string getSymbol();
};

#endif
