#include <SDL2/SDL.h>
#include "../Window/Window.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#ifndef __TEXT__
#define __TEXT__

using namespace std;

class Text
{
private:
	string text;
	string path;
	static string defaultFontPath;
//	int maxSize;
//
	int fontSize;
	bool showLogs;
	bool visible;

	SDL_Color color;
	SDL_Rect position;
	SDL_Texture* texture;
	TTF_Font* font;
	Window* window;


	void setDefaultValues();//Don't touch here !!!, set the default values of the Text
	void getValuesFromSurface(SDL_Surface* surface);//Don't touch here!!!, obtain the x, y, width and height from loaded surface

public:
	//Constructors
	Text();//Create the Text, using the Default Values
	Text(string path);//Create the Text, loading a .ttf font file as default font
	//Destructors
	~Text();
	//Getters
//	int getMaxSize();
	string getText();//Return the current text inside it;
	int getX();//Return the X Position of the text
	int getY();//Return the Y Position of the text
	int getWidth();//Return the Total text Width Value
	int getHeight();//Return the Total text Height value

	bool getWindowDefined();//Return true if window already setted

	//Setters
	void setWindow(Window *window);//Define the Window that will be used to render the text
//	void setMaxSize(int maxSize);
	void setPosition(int x, int y);//Define the X and Y position to show the text
	void setX(int x);//Define the X position to show the text
	void setY(int y);//Define the Y position to show the text
	void setText(string text);//Define the text to be rendered
	void setLogs(bool showLogs);//If receive true as parameter, this will show all logs (great for debug)
	void setFont(string path, int fontSize);//Define the .ttf font to be loaded, and define a font size for it
	void setFont(string path);//Define the .ttf font to be loaded
	void setFontSize(int fontSize);//Define the Font Size
	void setColor(SDL_Color color);//Define the Color of the Text

	void setVisible(bool option);

	void setDefaultFontPath(string path);// defines the default font

	//Commands
	void update();//Update (Render again) the text
	void print();//Show the text on Screen
};

#endif // __TEXT__
