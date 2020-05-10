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
    Color(float _v);
    Color(float _r, float _g, float _b);
    ~Color();    
    
    static Color* blend(Color c0, Color c1, float factor);

    float red(){ return r; }
    float green(){ return g; }
    float blue(){ return b; }

    int getColorPair();
    std::string getSymbol();
};

#endif
