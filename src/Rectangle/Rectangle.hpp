#pragma once
#include <SDL2/SDL.h>
#include "../Window/Window.hpp"
#include <iostream>

class Rectangle
{
private:
	SDL_Color color;
	SDL_Rect position;
	bool showLogs;
	bool visible;
public:
	//Constructors
	Rectangle();
	Rectangle(int w, int h);
	//Destructors
	~Rectangle();

	//Getters
	void getSize(int *w, int *h);
	void getPosition(int *x, int *y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool getClicked(Window* window); //If clicked, returns true
	bool getReleased(Window* window); // If mouse button is released, return true
	bool getCursorInside(Window* window);//Return true if cursor position is behind x and x+width, and y and y+height
	bool getMouseInside(Window* window);//Another name to "getMouseInside(Window* window);"
	bool getVisible();


	//Setters
	void setSize(int w, int h);
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);
	void setLogs(bool showLogs);
	void setColor(SDL_Color color);
	void setColor(int r, int g, int b);

	void setVisible(bool option);


	//Commands
	void print(Window *window);
	void printFilled(Window *window);
};
