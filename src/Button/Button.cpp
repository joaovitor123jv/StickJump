#include "Button.hpp"

// STATIC VARIABLES
unsigned int Button::defaultBorderSize = 50;

//Constructor
Button::Button()
{
	this->setDefaultValues();
}

Button::Button(std::string text)
{
	this->setDefaultValues();
	this->setText(text);
}


//Getters

int Button::getWidth()
{
	return this->rectangle.getWidth();
}

int Button::getHeight()
{
	return this->rectangle.getHeight();
}


//Setters
void Button::setDefaultValues()
{
	this->outsideColor = {144, 164, 174, 255};
	this->insideColor = {176, 190, 197, 255};
	this->clickColor = {236, 239, 241, 255};
	this->rectangle.setColor(outsideColor);
	this->text.setFont("font/default.ttf", 30);
	this->text.setColor({55,71,79, 255});
	this->text.setText("Button");
	this->borderSize = Button::defaultBorderSize;
	this->rectangle.setSize(	this->text.getWidth()  + this->borderSize, 
								this->text.getHeight() + this->borderSize);
	this->window = NULL;
	this->setPosition(0,0);
	this->showLogs = false;
}

void Button::setDefaultBorderSize(unsigned int size){ Button::defaultBorderSize = size; }

void Button::setWindow(Window* window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Button setWindow(Window* window)"<<endl;
			cout<<"\tERROR: Window* == NULL, aborting"<<endl;
		}
		return;
	}
	this->window = window;
	this->text.setWindow(this->window);
	this->text.update();
}

void Button::setText(string text) 
{ 
	this->text.setText(text); 
	this->rectangle.setSize(this->text.getWidth() + this->borderSize, 
							this->text.getHeight() + this->borderSize); 
}

void Button::setPosition(int x, int y) 
{ 
	this->text.setPosition(x,y);
	this->rectangle.setPosition(x - (this->borderSize / 2), y - (this->borderSize / 2));
	if(this->showLogs)
	{
		if( this->window != NULL )
		{
			if(x > this->window->getWidth() || (x + this->rectangle.getWidth()) < 0)
			{
				cout<<"Warning: At Button.setPosition(int x, int y)"<<endl;
				cout<<"\tAt this X position, the button will not be shown"<<endl;
			}
			if(y > this->window->getHeight() || (y + this->rectangle.getHeight()) < 0)
			{
				cout<<"Warning: At Button.setPosition(int x, int y)"<<endl;
				cout<<"\tAt this Y position, the button will not be shown"<<endl;
			}
		}
		else 
		{
			cout<<"BUTTON LOG: Position X = "<<x<<endl;
			cout<<"\t\tPosition Y = "<<y<<endl;
		}
	}
}

void Button::setSize(int size) 
{ 
	this->text.setFontSize(size); 
	this->rectangle.setSize(this->text.getWidth() 	+ this->borderSize, 
							this->text.getHeight() 	+ this->borderSize); 
}

void Button::setLogs(bool showLogs) { this->showLogs = showLogs; }

void Button::setInsideColor()
{
	this->rectangle.setColor(this->insideColor);
}
void Button::setOutsideColor()
{
	this->rectangle.setColor(this->outsideColor);
}
void Button::setClickColor()
{
	this->rectangle.setColor(this->clickColor);
}


void Button::setInsideColor(int r, int g, int b)
{
	this->insideColor.r = r;
	this->insideColor.g = g;
	this->insideColor.b = b;
}

void Button::setOutsideColor(int r, int g, int b)
{
	this->outsideColor.r = r;
	this->outsideColor.g = g;
	this->outsideColor.b = b;
}

void Button::setClickColor(int r, int g, int b)
{
	this->clickColor.r = r;
	this->clickColor.g = g;
	this->clickColor.b = b;
}

void Button::setTextColor(int r, int g, int b)
{
	this->text.setColor({ (Uint8)r, (Uint8)g, (Uint8)b});
}

void Button::setOutsideColor(SDL_Color color)
{
	this->outsideColor = color;
}

void Button::setInsideColor(SDL_Color color)
{
	this->insideColor = color;
}

void Button::setClickColor(SDL_Color color)
{
	this->clickColor = color;
}

void Button::setTextColor(SDL_Color color)
{
	this->text.setColor(color);
}



//Commands

bool Button::listener()
{


	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Button listener()"<<endl;
			cout<<"\tERROR: window to listen, not specified yet, aborting"<<endl;
		}
		return false;
	}

	if(this->rectangle.getCursorInside(this->window))//se cursor estiver dentro do retangulo
	{
		if(this->showLogs)
		{
			cout<<"Cursor inside button"<<endl;	
		}
		
		if(this->window->getMouseClick())//Se detectar clique do mouse
		{
			if(this->showLogs)
			{
				cout<<"Button Clicked"<<endl;	
			}
			this->setClickColor();//Define a cor do botão pra quando clicado
			return true;
		}
		else
		{
			
			this->setInsideColor();//Define a cor do botão pra quando cursor estiver dentro do botao
			return false;
		}
	}
	else
	{
		this->setOutsideColor();
		return false;
	}
	return false;
}









void Button::print()
{
	this->rectangle.printFilled(this->window);
	this->text.print();
}
