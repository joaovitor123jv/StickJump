#pragma once
#include<SDL2/SDL.h>
#include"../Rectangle/Rectangle.hpp"
#include"../Screen/Screen.hpp"
#include"../Text/Text.hpp"

class Button
{
private:
	Text text;
	Rectangle rectangle;
	SDL_Color outsideColor;
	SDL_Color insideColor;
	SDL_Color clickColor;
	Screen* screen;
	bool showLogs;

	void setDefaultValues();
	void setInsideColor();
	void setOutsideColor();
	void setClickColor();
public:
	//Constructor
	Button();
	//Destructor
	~Button();

	//Setters
	void setScreen(Screen* screen);
	void setText(string text);
	void setSize(int size);
	void setPosition(int x, int y);
	void setLogs(bool showLogs);

	//Commands
	void listener();
	void print();
};
