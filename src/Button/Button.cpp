#include"Button.hpp"

//Constructor
Button::Button()
{
	this->setDefaultValues();
}


//Destructor
Button::~Button()
{
	if(this->screen != NULL)
	{
		this->screen = NULL;
	}
}

//Setters
void Button::setDefaultValues()
{
	this->outsideColor = {0, 255, 255, 255};
	this->insideColor = {255, 0, 255, 255};
	this->clickColor = {255, 255, 0, 255};
	this->rectangle.setColor(outsideColor);
	this->text.setFont("font/default.ttf", 30);
	this->text.setText("Button");
	this->rectangle.setSize(this->text.getWidth(), this->text.getHeight());
	this->screen == NULL;
	this->showLogs = false;
}


void Button::setScreen(Screen* screen)
{
	if(screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Button setScreen(Screen8)"<<endl;
			cout<<"\tERROR: Screen * == NULL, aborting"<<endl;
		}
		return;
	}
	this->screen = screen;
	this->text.setScreen(this->screen);
	this->text.update();
}

void Button::setText(string text) { this->text.setText(text); this->rectangle.setSize(this->text.getWidth(), this->text.getHeight()); }

void Button::setPosition(int x, int y) { this->text.setPosition(x, y); this->rectangle.setPosition(x,y); }

void Button::setSize(int size) { this->text.setFontSize(size); this->rectangle.setSize(this->text.getWidth(), this->text.getHeight()); }

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

//Commands
bool Button::listener()
{
	if(this->screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Button listener()"<<endl;
			cout<<"\tERROR: screen to listen, not specified yet, aborting"<<endl;
		}
		return false;
	}
	int x, y;
	this->screen->getCursorPosition(&x,&y);
	if(x < this->rectangle.getX())
	{
		this->setOutsideColor();
		return false;
	}
	if(x > this->rectangle.getX()+this->rectangle.getWidth())
	{
		this->setOutsideColor();
		return false;
	}
	if(y < this->rectangle.getY())
	{
		this->setOutsideColor();
		return false;
	}
	if(y > this->rectangle.getY()+this->rectangle.getHeight())
	{
		this->setOutsideColor();
		return false;
	}
	if(!this->screen->getMouseButtonDown())
	{
		this->setInsideColor();
		return false;
	}
	if(this->screen->getMouseButtonDown())
	{
		this->setClickColor();
		return true;
	}
	return false;
}

void Button::print()
{
	this->rectangle.printFilled(this->screen);
	this->text.print();
}
