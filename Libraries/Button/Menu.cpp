#include "Button.h"	
#include "Menu.h"
#include "Arduino.h"
#include "Esplora.h"  
#include "TFT.h"           
#include "SPI.h"


Menu::Menu(Button buttons[], int numberOfButtons, int colSel1, int colSel2, int colSel3){
  _buttons = buttons;
  _numberOfButtons = numberOfButtons;
  _colSel1 = colSel1;
  _colSel2 = colSel2;
  _colSel3 = colSel3;
  _currentButton = 0;

}

void Menu::drawMenu(){
  for(int i = 0; i < _numberOfButtons; i++){
	_buttons[i].draw();
  }
  setCurrentButton(_currentButton);
}

void Menu::checkMenu(){

  int xValue = Esplora.readJoystickX();        
  int yValue = Esplora.readJoystickY();        
  int button = Esplora.readJoystickSwitch();   
  
  int x = map(xValue, -512, 512, 10, -10); 
  int y = map(yValue, -512, 512, -10, 10);
  
  if(x > 4){
    if(_currentButton + 1 > (_numberOfButtons - 1))
      setCurrentButton(0);
    else
      setCurrentButton(_currentButton + 1);
    delay(100);
  }
  else if(x < -4){
    if(_currentButton -1 < 0)
      setCurrentButton(_numberOfButtons - 1);
    else
      setCurrentButton(_currentButton - 1);
    delay(100);
  }
  
  else if(y > 4){
    if(_currentButton + 2 > (_numberOfButtons - 1))
      setCurrentButton(0);
    else
      setCurrentButton(_currentButton + EsploraTFT.width() / _buttons[0].getSizeX());
    delay(100);
  }
  else if(y < -4){
    if(_currentButton -2 < 0)
      setCurrentButton(_numberOfButtons - 1);
    else
      setCurrentButton(_currentButton - EsploraTFT.width() / _buttons[0].getSizeX());
    delay(100);
  }
  if(Esplora.readButton(SWITCH_DOWN) == 0)
    menuAction(SWITCH_DOWN, _currentButton);
  if(Esplora.readButton(SWITCH_UP) == 0)
    menuAction(SWITCH_UP, _currentButton); 
  if(Esplora.readButton(SWITCH_RIGHT) == 0)
    menuAction(SWITCH_RIGHT, _currentButton);
  if(Esplora.readButton(SWITCH_LEFT) == 0)
    menuAction(SWITCH_LEFT, _currentButton);
}

void Menu::setCurrentButton(int i){
  int* prevColors ;
  prevColors = _buttons[_currentButton].getColor();
  _buttons[_currentButton].setColor(prevColors[0],prevColors[1],prevColors[2]);
  _buttons[_currentButton].draw();
  _currentButton = i;
  _buttons[_currentButton].setColor(_colSel1,_colSel2,_colSel3);
  _buttons[_currentButton].draw();
}

void Menu::setColor(int colSel1, int colSel2, int colSel3){
   _colSel1 = colSel1;
   _colSel2 = colSel2;
   _colSel3 = colSel3;
}

int* Menu::getColor(){
  int i[3] = {_colSel1, _colSel2, _colSel3};
  return &i[0];
}

void Menu::addButton(Button b){ //@TODO
 
}

int Menu::removeButton(Button b){ //@TODO
 return 1;  
}
int Menu::getCurrentButton(){
  return _currentButton;
}