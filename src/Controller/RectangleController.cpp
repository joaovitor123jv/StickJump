#include "RectangleController.hpp"
using std::cout;
using std::endl;
using std::string;

// EXTRA FUNCTIONS
void movementFollowCursor(Window* window, Rectangle *rectangle);
void movementDraggable(Window *window, Rectangle *rectangle, RectangleController *rectangleController);
void movementGravity(Window *window, Rectangle *rectangle, RectangleController *rectangleController);

//Constructors
RectangleController::RectangleController(Rectangle *rectangle)
{
	if(rectangle == NULL)
	{
		cout<<"ERROR: At RectangleController Constructor"<<endl;
		cout<<"\tPointer to rectangle == NULL, aborting"<<endl;
		return;
	}
	this->rectangle = rectangle;
	setDefaultValues();
}

RectangleController::RectangleController(Rectangle *rectangle, Window *window)
{
	if(rectangle == NULL)
	{
		cout<<"ERROR: At RectangleController Constructor"<<endl;
		cout<<"\tPointer to rectangle == NULL, aborting"<<endl;
		return;
	}
	if(window == NULL)
	{
		cout<<"ERROR: At RectangleController Constructor"<<endl;
		cout<<"\tPointer to rectangle == NULL, aborting"<<endl;
		return;
	}
	this->rectangle = rectangle;
	this->window = window;
	setDefaultValues();	
}

// Destructors
RectangleController::~RectangleController()
{
	// Faz nada
}

//Setters
void RectangleController::setDefaultValues()
{
	this->checkCollisions = false;
	this->followCursor = false;
	this->draggable = false;
	this->dragging = false;
	this->distanceX = 0;
	this->distanceY = 0;
	this->gravityEnabled = false;
	this->gravityValue = 1;
	this->velocityX = 0;
	this->velocityY = 0;
}

void RectangleController::setLogs(bool value) {this->showLogs = value; }

bool RectangleController::setWindow(Window* window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"ERROR: At RectangleController.setWindow(Window*)"<<endl;
			cout<<"\tPointer to window == NULL"<<endl;
		}		
		return false;
	}
	this->window = window;
	return true;
}

void RectangleController::setCollisionCheck(bool variable) {this->checkCollisions = variable; }

void RectangleController::setFollowCursor(bool value) {this->followCursor = value; }

void RectangleController::setDraggable(bool value)
{
	
	if(this->followCursor)
	{
		if(this->showLogs)
		{
			cout<<"Warning: At RectangleController.setDraggable(bool)"<<endl;
			cout<<"\tThis controller already make the defined Rectangle to follow the cursor"<<endl;
			cout<<"\tSo, this change will not to take effect"<<endl;
		}
		return;
	}
	this->draggable = value;
}

void RectangleController::setGravityValue(int value)
{
	this->gravityValue = value;
}

void RectangleController::setDragging(bool value) {this->dragging = value; }








//Getters

int RectangleController::getDistanceX() {return this->distanceX; }

int RectangleController::getDistanceY() {return this->distanceY; }
bool RectangleController::getDragging() { return this->dragging; }





//Enablers
void RectangleController::enableGravity(bool value)
{
	this->gravityEnabled = value;
}









//Commands
void RectangleController::calcDistance()
{
	this->distanceX = this->window->getCursorXPosition() - this->rectangle->getX();
	this->distanceY = this->window->getCursorYPosition() - this->rectangle->getY();
	return;
}


bool RectangleController::listener()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"ERROR: At RectangleController.listener()"<<endl;
			cout<<"\tWindow not defined"<<endl;
		}
		return false;
	}
	if(this->rectangle == NULL)
	{
		if(this->showLogs)
		{
			cout<<"ERROR: At RectangleController.listener()"<<endl;
			cout<<"\tRectangle to be controlled not defined"<<endl;
		}
		return false;
	}

	if(this->followCursor)
	{
		movementFollowCursor(this->window, this->rectangle);
		return true;
	}
	else if(this->draggable)
	{
		movementDraggable(this->window, this->rectangle, this);
		return true;
	}
	return false;
}

void RectangleController::execute()
{
	if(!this->dragging)
	{
		if(this->gravityEnabled)
		{
			this->simulateGravity();
		}	
	}
}

void RectangleController::simulateGravity()
{
	// this->velocityX = this->velocityX + this->gravityValue;
	if( this->rectangle->getY() + this->rectangle->getHeight() < this->window->getHeight())//temporario
	{
		this->velocityY = this->velocityY + this->gravityValue;
	}
	else
	{
		this->velocityY = 0;
		this->rectangle->setY(this->window->getHeight() - this->rectangle->getHeight());
	}
	this->rectangle->setY( this->rectangle->getY() + this->velocityY );
}

//Movements

void movementDraggable(Window *window, Rectangle *rectangle, RectangleController *rectangleController)
{
	if(rectangleController->getDragging())
	{
		if(window->getMouseButtonUp())
		{
			rectangleController->setDragging(false);
			return;
		}
		else
		{
			rectangle->setX(window->getCursorXPosition() - rectangleController->getDistanceX());
			rectangle->setY(window->getCursorYPosition() - rectangleController->getDistanceY());
		}
	}
	if(window->getMouseClick())
	{
		if(rectangle->getCursorInside(window))
		{
			rectangleController->setDragging(true);
			rectangleController->calcDistance();
		}
		return;
	}
	return;
}

void movementFollowCursor(Window* window, Rectangle *rectangle)
{
	rectangle->setX( window->getCursorXPosition() - rectangle->getWidth()/2) ;
	rectangle->setY( window->getCursorYPosition() - rectangle->getHeight()/2) ;
}
