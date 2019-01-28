#pragma once
#include <iostream>
#include <string>
#include "../Text/Text.hpp"
#include "../Rectangle/Rectangle.hpp"
#include "../Window/Window.hpp"

// bool textInputEnabled = false;

class TextBox
{
public:
		//Constructors
	TextBox();
		TextBox(string path);//Create a TextBox with the font defined on path
		TextBox(string path, int fontSize);//Create a TextBox with the font defined on path, with the size of fontSize
		TextBox(int width, int height);//Create a TextBox with width and height defined

		//Destructor
		~TextBox();//Called automatically


		//Getters
		void getSize(int* width, int* height);// Turn "width" and "height", the width and height of the TextBox
		void getPosition(int* x, int* y); //Turn  "x" and "y", the position of the TextBox

		int getWidth();//Return the Width of the TextBox
		int getHeight();//Return the Height of the TextBox
		int getX();//Return the X position of the TextBox
		int getY();//Return the Y position of the TextBox

		bool getVisible();

		string getText();//Return the Text (printable) inside the TextBox


		//Setters
		void setTextColor(int r, int g, int b);//Define the Text color
		void setTextColor(SDL_Color color);//Other way to define Text color
		void setColor(int r, int g, int b);//Define the Rectangle color (background color)
		void setColor(SDL_Color color);//Other way to define the background color

		void setSize(int width, int height);
		void setWidth(int width);
		void setHeight(int height);

		void setPosition(int x, int y);
		void setX(int x);
		void setY(int y);

		void setEnterAsCommand(bool x);

		void setShowLogs(bool showLogs);//If it receive true, the logs will appear
		void setLogs(bool showLogs);// A shorter name to setShowLogs(bool showLogs);

		void setVisible(bool option);// If receives true, the TextBox will show, if( false ), it'll not be shown

		//Commands
		bool listener(Window* window);// Return true if something happens
		void print(Window* window);//Print the TextBox on window

	private:
		//Variables
		Text text;
		Rectangle rectangle;

		string inputText;

		bool showLogs;
		bool editingText;
		bool textEdited;
		bool enterEnabledAsCommand;
		bool visible;

		//Setters
		void setDefaultValues();//Don't thouch here !!! , method to define the default values, used by TextBox.
	};
