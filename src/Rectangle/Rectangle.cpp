#include <SDL2/SDL.h>
#include <iostream>
#include "Rectangle.hpp"
using namespace std;

//Constructors
Rectangle::Rectangle()
{
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = 0;

	this->position.x = 0;
	this->position.y = 0;
	this->position.w = 0;
	this->position.h = 0;
}

Rectangle::Rectangle(int w, int h)
{
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = 0;

	this->position.x = 0;
	this->position.y = 0;
	this->position.w = w;
	this->position.h = h;
}

//Destructor
Rectangle::~Rectangle()
{
}

//Getters
void Rectangle::getSize(int *w, int *h) { *w = this->position.w; *h = this->position.h; }
void Rectangle::getPosition(int *x, int *y) { *x = this->position.x; *y = this->position.y; }
int Rectangle::getX(){ return this->position.x; }
int Rectangle::getY(){ return this->position.y; }
int Rectangle::getWidth(){ return this->position.w; }
int Rectangle::getHeight(){ return this->position.h; }

bool Rectangle::getClicked(Window* window)
{
	if(window->getMouseClick())
	{
		if(this->getCursorInside(window))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool Rectangle::getReleased(Window* window)
{
	if(window->getMouseRelease())
	{
		return true;
	}
	return false;
}

bool Rectangle::getMouseInside(Window* window)
{
	return this->getCursorInside(window);
}

bool Rectangle::getCursorInside(Window* window)
{
	int x, y;
	window->getCursorPosition(&x, &y);
	if(x <= (this->position.x+this->position.w) && x >= this->position.x)
	{
		if(y <= (this->position.y + this->position.h) && y>= this->position.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else {return false;}
}

bool Rectangle::getVisible()
{
	return this->visible;
}

//Setters

void Rectangle::setVisible(bool option)
{
	this->visible = option;
}

void Rectangle::setColor(SDL_Color color)
{
	this->color = color;
}

void Rectangle::setColor(int r,int g, int b)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
}

void Rectangle::setSize(int w, int h)
{
	if(w <0)
	{
		if(showLogs)
		{
			cout<<"On: Rectangle setSize(int, int)"<<endl;
			cout<<"\tInvalid negative values, aborting"<<endl;
		}
		return;
	}
	this->position.w = w;
	this->position.h = h;
	return;
}

void Rectangle::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Rectangle::setX(int x)
{
	this->position.x = x;
}


void Rectangle::setY(int y)
{
	this->position.y = y;
}


void Rectangle::setWidth(int w)
{
	this->position.w = w;
}


void Rectangle::setHeight(int h)
{
	this->position.h = h;
}

void Rectangle::setLogs(bool showLogs) { this->showLogs = showLogs; }

//Commands
void Rectangle::print(Window *window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Rectangle print(Window* )"<<endl;
			cout<<"\tERROR: Window* == NULL"<<endl;
		}
		return;
	}
	if( this->visible )
	{
		SDL_SetRenderDrawColor(window->getRenderer(), this->color.r, this->color.g, this->color.b, this->color.a);
		SDL_RenderDrawRect(window->getRenderer(), &this->position);
		window->setDefaultRenderColor();
		return;
	}
}

void Rectangle::printFilled(Window *window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Rectangle printFilled(Window* )"<<endl;
			cout<<"\tERROR: Window* == NULL"<<endl;
		}
		return;
	}
	SDL_SetRenderDrawColor(window->getRenderer(), this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(window->getRenderer(), &this->position);
	window->setDefaultRenderColor();
}
