#pragma once
#include<string>
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"../Screen/Screen.hpp"
using namespace std;

class Image
{
private:
	Screen* screen;
	SDL_Rect position;
	SDL_Rect resized;
	SDL_Rect crop;
	SDL_Texture* texture;
	string path;
	bool showLogs;

	void setDefaultValues();
	void getImageDimensions(SDL_Surface* surface);

public:
	Image();
	Image(string path);
	
	~Image();
	//Getters
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	//Setters
	void setLogs(bool showLogs);
	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setScreen(Screen* screen);
	void setCrop(int x, int y, int w, int h);
	//Loaders
	bool loadImage(string path);
	//Commands
	void print();
	void toString();
};
