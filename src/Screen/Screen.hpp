#pragma once
#include<SDL2/SDL.h>
#include<string>
#include<iostream>

class Screen
{
	SDL_Window* window;
	std::string title;
	SDL_Event event;
	SDL_Point cursor;
	SDL_Renderer* renderer;
	unsigned int width;
	unsigned int height;
	bool showDecoration;
	bool showWindow;
	bool showLogs;
	bool autoUpdate;
	bool fullScreen;
	SDL_Color color;


	bool mouseButtonDown;

	//Methods
	void setDefaultValues();

public:
	//Constructors
	Screen();
	Screen(int width, int height);
	Screen(std::string title, int width, int height);

	//Destructors
	~Screen();

	//Setters
	bool setSize(unsigned int width, unsigned int height);
	bool setVisible(bool showWindow);
	bool setDecoration(bool showDecoration);//working
	bool setTitle(std::string title);//working
	bool setDrawColor(SDL_Color color);
	bool setAutoUpdate(bool autoUpdate);
	bool setLogs(bool showLogs);
	bool setFullScreen(bool fullScreen);
	void setDefaultRenderColor();

	//Getters
	unsigned int getWidth();
	unsigned int getHeight();
	bool getEvent();
	bool getCursorPosition(int *x, int *y);
	bool getMouseButtonDown();
	bool getKeyDown();
	bool getKeyUp();
	SDL_Keycode getKey();
	bool getExit();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	//Commands
	bool upgrade();
	bool update();
};
