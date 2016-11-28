#pragma once
#include<iostream>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_thread.h>
#include"../Screen/Screen.hpp"
#include"../Image/Image.hpp"
using namespace std;

class Animation
{
private:
	int lines;
	int columns;
	int pauseSprite;
	short int up;
	short int down;
	short int left;
	short int right;

	bool showLogs;
	bool spriteSheet;
	bool lineFixed;
	bool running;
	bool paused;
	bool jumpPauseSprite;

	SDL_Thread* spriteChange;
	
	Image image;

	void setDefaultValues();
public:
	//Constructors
	Animation();
	Animation(int lines, int columns);
	Animation(string path, int lines, int columns);

	//Destructor
	~Animation();

	//Getters
	bool getRunning();
	bool getShowLogs();
	bool getLineFixed();
	bool getPaused();
	bool getSpriteSheet();
	bool getJumpPauseSprite();
	int getPauseSprite();
	int getLines();
	int getColumns();
	short int getLeft();
	short int getRight();
	short int getUp();
	short int getDown();
	Image *getImage();

	//Setters
	void setLogs(bool showLogs);
	void setScreen(Screen* screen);
	void setMultipleImages(bool spriteSheet);
	void setSpriteMatrix(int lines, int columns);
	void setLineFixed(bool lineFixed);
	void setPauseSprite(int pauseSprite);
	void setJumpPauseSprite(bool jumpPauseSprite);
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	void setSize(int w, int h);

	void setUp(short int up);//Define fixed line or column, that mean that sprite is "seeing up"
	void setDown(short int down);
	void setLeft(short int left);
	void setRight(short int right);

	void setUp(bool up);//Define if sprite is seing to up, on this moment (during sprite change)
	void setDown(bool down);
	void setLeft(bool left);
	void setRight(bool right);

	//Loaders
	bool loadSpriteSheet(string path);
	bool loadSpriteSheet(string path, int lines, int columns);

	//Commands
	void pause();
	void run();
	void print();
};
