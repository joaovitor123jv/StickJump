#include "../Window/Window.hpp"
#include "../Rectangle/Rectangle.hpp"

class RectangleController
{
private:
	bool showLogs;
	bool checkCollisions;
	bool followCursor;
	
	bool draggable;
	int distanceX;
	int distanceY;
	bool dragging;

	bool gravityEnabled;
	int gravityValue;
	int velocityX;
	int velocityY;


	Window *window;
	Rectangle *rectangle;

	void setDefaultValues();

public:
	//Constructor
	RectangleController(Rectangle *);//Working
	RectangleController(Rectangle *, Window *);//Working

	//Destructor
	~RectangleController();
	//Getters

	//Setters
	bool setWindow(Window *window);//working
	void setCollisionCheck(bool variable);//working
	void setLogs(bool value);//working
	void setFollowCursor(bool value);//working
	void setDraggable(bool value);//working
	void setDragging(bool value);//working
	void setGravityValue(int gravityValue);
	
	//Enablers
	void enableGravity(bool value);

	int getDistanceX();//working
	int getDistanceY();//working
	bool getDragging();//working

	//Commands
	void simulateGravity();
	void calcDistance();//working
	bool listener();//working
	void execute();
};
