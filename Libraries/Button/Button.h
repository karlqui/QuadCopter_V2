#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "Esplora.h"  
#include "TFT.h"           
#include "SPI.h"

class Button{
  public:
  
    Button(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY, int locX, int locY);
    Button(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY); //auto size and location
    void setText(String text);
    String getText();
    void setColor(int c1, int c2, int c3);
    int* getColor();
    void setSizeX(int sizeX);
    void setSizeY(int sizeY);
    int getSizeX();
    int getSizeY();
    void setLocX(int locX);
    void setLocY(int locY);
    int getLocX();
    int getLocY();
    void setTextSize(int textSize);
    int getTextSize();
    int draw();
  private:
  
    void init(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY, int locX, int locY);
    String _text;
    int _textSize;
    int _id;
    int _c1;
    int _c2;
    int _c3;
    int _sizeX;
    int _sizeY;
    int _locX;
    int _locY;
};

#endif