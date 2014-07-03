#ifndef Menu_h
#define Menu_h

#include "Arduino.h"
#include "Esplora.h"  
#include "TFT.h"           
#include "SPI.h"
#include "Button.h"

class Menu{

  public:
	
	Menu(Button buttons[], int numberOfButtons, int colSel1, int colSel2, int colSel3);
	
	void checkMenu();
	void menuAction(int switch_nr, int currentButton);
	void setColor(int colSel1, int colSel2, int colSel3);
	int* getColor();
	void addButton(Button b);
	int removeButton(Button b);
	int getCurrentButton();
	void drawMenu();
	
  private:
	int _colSel1;
	int _colSel2;
	int _colSel3;
	Button * _buttons;
	int _numberOfButtons;
	int _currentButton;
	void setCurrentButton(int i);
	
};

#endif