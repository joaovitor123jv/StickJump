#ifndef __IMAGE__
#define __IMAGE__
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Window/Window.hpp"


class Image
{	
public:
	// Constructors
	Image(); // Create a image with their default values
	Image(std::string path); // Create a image with their default values and set path as your default path

	// Destructor
	~Image();
	
	// Setters
	void setLogs(bool showLogs); // Suppress or Permit logs on runtime
	void setPosition(int px, int py);// Define the position of the image to be printed
	void setSize(int width, int height);// Define the size of the image to be printed

	int getX();
	int getY();

	int getWidth();
	int getHeight();


	// Loaders
	bool load(std::string path, Window* window); //Load a image from path and create texture for it, getting the window render
	bool load(Window* window); // Load a image on (before defined) path, and create a texture for it, getting the window render

	// Commands
	void print(Window* window);
	void print(Window* window, int px, int py);// Prints the image at selected position x and y
	void print(void);// If the window is already set

private:

	// Variables
	Window *window;
	SDL_Texture* texture;

	SDL_Rect position;
	SDL_Rect cut;

	std::string path;

	bool showLogs;
	bool haveTransparency;

	// Setters
	void setDefaultValues(); // Used by constructors and another functions, don't edit it!

	// Defines
	bool definePNGSupport(); // Start PNG image format support

};

#endif // __IMAGE__
