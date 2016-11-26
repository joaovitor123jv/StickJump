#pragma once
#include<SDL2/SDL.h>
#include"../Screen/Screen.hpp"
#include<iostream>

class Rectangle
{
private:
	SDL_Color color;
	SDL_Rect position;
	bool showLogs;
public:
	//Constructors
	Rectangle();
	//Destructors
	~Rectangle();

	//Getters
	void getSize(int *w, int *h);
	void getPosition(int *x, int *y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();


	//Setters
	void setSize(int w, int h);
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);
	void setLogs(bool showLogs);
	void setColor(SDL_Color color);

	//Commands
	void print(Screen *screen);
	void printFilled(Screen *screen);
};
