#include "Button.h"	
#include "Arduino.h"
#include "Esplora.h"  
#include "TFT.h"           
#include "SPI.h"


Button::Button(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY, int locX, int locY){
  init(text, textSize, id, c1, c2, c3, sizeX, sizeY, locX, locY);
}

Button::Button(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY){
  init(text, textSize, id, c1, c2, c3, sizeX, sizeY, -1, -1);
}

void Button::init(String text, int textSize, int id, int c1, int c2, int c3, int sizeX, int sizeY, int locX, int locY){
  _text = text;
  _id = id;
  _c1 = c1;
  _c2 = c2;
  _c3 = c3;
  _sizeX = sizeX;
  _sizeY  = sizeY;
  _locX = locX;
  _locY = locY;
}

void Button::setText(String text){
  _text = text;
}

String Button::getText(){
  return _text;
}

void Button::setColor(int c1, int c2, int c3){
  _c1 = c1;
  _c2 = c2;
  _c3 = c3;
}

int* Button::getColor(){
  int i[3] = {_c1, _c2, _c3};
  return &i[0];
}

void Button::setSizeX(int sizeX){
  _sizeX = sizeX;
}

int Button::getSizeX(){
  return _sizeX;
}

void Button::setSizeY(int sizeY){
  _sizeY = sizeY;
}

int Button::getSizeY(){
  return _sizeY;
}

void Button::setLocX(int locX){
  _locX = locX;
}

int Button::getLocX(){
  return _locX;
}

void Button::setLocY(int locY){
  _locY = locY;
}

int Button::getLocY(){
  return _locY;
}

void Button::setTextSize(int textSize){
	_textSize = textSize;
}

int Button::getTextSize(){
	return _textSize;
}

int Button::draw(){
	if(_locX != -1 && _locY != -1){
		if(_locX + _sizeX > EsploraTFT.width() || _locY + _sizeY > EsploraTFT.height())
			return -1; //button is outside the screen
		EsploraTFT.stroke(200,20,180);
		EsploraTFT.fill(_c1,_c2, _c3);
		EsploraTFT.rect(_locX, _locY, _sizeX, _sizeY);	
		char tempArray[_text.length() + 1];
		_text.toCharArray(tempArray, _text.length() + 1);
		EsploraTFT.text(tempArray, _locX + 2, _locY + 2); //@TODO method to change text offset within button
		return 1;
	}
	else{ //auto-placement of buttons
			
		int buttonsPerRow = EsploraTFT.width() / _sizeX;

		int offset = (EsploraTFT.width() - buttonsPerRow * _sizeX) / (buttonsPerRow + 1);
		int row = ( _id / buttonsPerRow );

		int placeOnRow = abs( _id % buttonsPerRow );

		_locX = offset * (placeOnRow + 1) + (placeOnRow) * _sizeX;
		_locY = _sizeY * row  + 8 * (row + 1);
		
		EsploraTFT.stroke(200,20,180);
		EsploraTFT.fill(_c1, _c2, _c3);
		EsploraTFT.rect(_locX, _locY, _sizeX, _sizeY);
		char tempArray[_text.length() + 1];
		_text.toCharArray(tempArray, _text.length() + 1);
		EsploraTFT.text(tempArray, _locX + 2, _locY + 2);
		return 1;
	}
}

