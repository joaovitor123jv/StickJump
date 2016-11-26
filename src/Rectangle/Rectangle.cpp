#include<SDL2/SDL.h>
#include<iostream>
#include"Rectangle.hpp"
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

//Setters
void Rectangle::setColor(SDL_Color color)
{
	this->color = color;
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
void Rectangle::print(Screen *screen)
{
	if(screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Rectangle print(Screen* )"<<endl;
			cout<<"\tERROR: Screen* == NULL"<<endl;
		}
		return;
	}
	SDL_SetRenderDrawColor(screen->getRenderer(), this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderDrawRect(screen->getRenderer(), &this->position);
	screen->setDefaultRenderColor();
}

void Rectangle::printFilled(Screen *screen)
{
	if(screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Rectangle printFilled(Screen* )"<<endl;
			cout<<"\tERROR: Screen* == NULL"<<endl;
		}
		return;
	}
	SDL_SetRenderDrawColor(screen->getRenderer(), this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(screen->getRenderer(), &this->position);
	screen->setDefaultRenderColor();
}
