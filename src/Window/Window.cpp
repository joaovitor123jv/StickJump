#include "Window.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;


//Constructors
Window::Window(void)
{
	
	this->runningOnTty = false;
	//if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	if( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}

	SDL_GetDesktopDisplayMode(0, &this->displayMode);

	this->setDefaultValues();
	if(this->upgrade())
	{
		cout<<"Window created with success"<<endl;
	}
	else
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

Window::Window(bool runningOnTty)
{
	this->runningOnTty = runningOnTty;
	//if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	if( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}

	SDL_GetDesktopDisplayMode(0, &this->displayMode);
	this->setDefaultValues();
	this->showWindow = true;

	cout<<"Width = "<<this->width<<endl;
	cout<<"Height = "<<this->height<<endl;
	if(this->upgrade())
	{
		cout<<"Window created with success"<<endl;
	}
	else
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

Window::Window(int width, int height)
{
	this->runningOnTty = false;
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}
	SDL_GetDesktopDisplayMode(0, &this->displayMode);
	this->setDefaultValues();
	this->width = width;
	this->height = height;
	this->showWindow = true;
	if(this->upgrade())
	{
		cout<<"Window created with success"<<endl;
	}
	else
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

Window::Window(std::string title, int width, int height)
{
	this->runningOnTty = false;
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to init video"<<endl;
		return;
	}
	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1"))
	{
		cout<<"Warning: Linear texture filtering not enabled!"<<endl;
	}
	SDL_GetDesktopDisplayMode(0, &this->displayMode);
	this->setDefaultValues();
	this->width = width;
	this->height = height;
	this->title = title;
	this->showWindow = true;
	if(!this->upgrade())
	{
		cout<<"On: Screen constructor"<<endl;
		cout<<"\tERROR: Failed to initialize window"<<endl;
		return;
	}
	this->update();
}

//Destructor
Window::~Window(void)
{
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
		this->renderer = NULL;
	}
	if(this->window != NULL)
	{
		SDL_DestroyWindow(this->window);
		this->window= NULL;
	}
	// SDL_Quit();
}

void Window::finalize(void)
{
	#ifdef __IMAGE__
		IMG_Quit();
	#endif //__IMAGE__
	SDL_Quit();
}


//Commands

bool Window::upgrade()
{
	if(this->window != NULL)
	{
		SDL_DestroyWindow(this->window);
		this->window=NULL;
	}

	if(this->showWindow)
	{
		if( this->runningOnTty )
		{
			cout<<"Upgrading Window - Running on TTY"<<endl;
			this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_INPUT_FOCUS);
			if( this->window == NULL )
			{
				cout<<"ERROR: failed to create window, aborting program"<<endl;
				exit(-2);
			}
		}
		else
		{
			if(this->showDecoration)
			{
				this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
			}
			else
			{
				this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_BORDERLESS);
			}
		}
	}
	else
	{
		this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_HIDDEN);
	}

	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Window upgrade"<<endl;
			cout<<"\tFailed to init Window"<<endl;
		}
		return false;
	}
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Window upgrade"<<endl;
			cout<<"\tFailed to create renderer"<<endl;
		}
		SDL_DestroyWindow(this->window);
		return false;
	}
	SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	return true;
}

bool Window::update()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Window update"<<endl;
			cout<<"\tERROR: Window doesn't exists"<<endl;
		}
		return false;
	}
	SDL_RenderPresent(this->renderer);
	SDL_Delay(this->waitTime);
	// SDL_RenderClear(this->renderer);
	return true;
}

void Window::clear(void)
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Window clear"<<endl;
			cout<<"\t\"EROOR\": Window doesn't exist"<<endl;
		}
		return;
	}
	SDL_RenderClear(this->renderer);
}

bool Window::render()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: Window render"<<endl;
			cout<<"\tERROR: Window doesn't wxists"<<endl;
		}
		return false;
	}
	SDL_RenderPresent(this->renderer);
	return true;
}


void Window::wait(int time)// STATIC !!!
{
	SDL_Delay(time);
}

//Setters
void Window::setDefaultValues()
{
	this->title="";
	this->waitTime = 30;
	this->color.r= 0xFF;
	this->color.g= 0xFF;
	this->color.b= 0xFF;
	this->color.a= 0xFF;
	this->autoClearScreen = true;
	this->window= NULL;
	this->renderer=NULL;
	this->cursor.x=0;
	this->cursor.y=0;
	this->showDecoration = true;
	this->showWindow = false;
	this->setLogs(false);
	this->click = false;
	this->width = this->displayMode.w;
	this->height = this->displayMode.h;
	// this->textInputEnabled = false;
}

void Window::setDefaultRenderColor()
{
	this->setDrawColor(this->color);
}

void Window::setAutoClear(bool option){	this->autoClearScreen = option;}

void Window::setResizable(bool resizable)
{
	if(resizable)
	{
		SDL_SetWindowResizable(this->window, SDL_TRUE);	
	}
	else
	{
		SDL_SetWindowResizable(this->window, SDL_FALSE);		
	}
	return;//Não Tem isso no Mint (não sei porque, mas ok)
}


bool Window::setSize(unsigned int width, unsigned int height)
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: Screen->setSize(unsigned int,unsigned int)"<<endl;
			cout<<"\tERROR: Window now initialized yet, aborting"<<endl;
		}
		return false;
	}
	if(width <0 || height <0 )
	{
		if(this->showLogs)
		{
			cout<<"At: Screen->setSize(unsigned int, unsigned int)"<<endl;
			cout<<"\tERROR: The values must be greater than zero, aborting"<<endl;
		}
		return false;
	}
	this->width = width;
	this->height = height;
	SDL_SetWindowSize(this->window, this->width, this->height);
	if(this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->autoUpdate)
	{
		this->update();
	}
	return true;
}

bool Window::setVisible(bool showWindow) { this->showWindow = showWindow; return this->showWindow; }

bool Window::setDecoration(bool showDecoration) 
{
	this->showDecoration = showDecoration; 
	if(this->autoUpdate)
	{
		if(this->showDecoration)
		{
			SDL_SetWindowBordered(this->window, SDL_TRUE);
			return true;
		}
		else
		{
			SDL_SetWindowBordered(this->window, SDL_FALSE);
			return true;
		}
	}
	return false;
}

bool Window::setBorderLess(bool showDecoration) { return this->setDecoration(!showDecoration); }//Only a easifier

bool Window::setTitle(std::string title) 
{
	this->title = title; 
	if(this->window != NULL)
	{
		SDL_SetWindowTitle(this->window, title.c_str());
		return true;
	}
	return true;
}

bool Window::setDrawColor(SDL_Color color)
{
	this->color = color;
	if(this->window != NULL)
	{
		SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	}
	return true;
}

bool Window::setAutoUpdate(bool autoUpdate) { this->autoUpdate = autoUpdate; return true; }

bool Window::setFullScreen(bool fullScreen)
{
	this->fullScreen = fullScreen;
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Screen setFullScreen(bool)"<<endl;
			cout<<"\t ERROR: Window not initialized, aborting"<<endl;
		}
		return false;
	}
	if(fullScreen)
	{
		SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
		return true;
	}
	else
	{
		this->setSize(this->width, this->height);
		return true;
	}
}

bool Window::setLogs(bool showLogs) { return this->showLogs = showLogs; }

void Window::setShowCursor(bool option)
{
	SDL_ShowCursor(option);
}

void Window::setFPSLimit(int number)
{
	// int number = ((int)(100/6*number));
	int x = (int) 1000/number;
	this->waitTime = (x > 0  ? x : x * -1);// get the number in FPS (approximately)
}

//Getters
unsigned int Window::getWidth() { return this->width; }
unsigned int Window::getHeight() { return this->height; }

int Window::getCursorXPosition() { return this->cursor.x; }
int Window::getCursorYPosition() { return this->cursor.y; }

SDL_Renderer* Window::getRenderer() { return this->renderer; }

bool Window::getEvent()
{
	if(this->window == NULL) return false;
	if(!SDL_PollEvent(&this->event))
	{
		if(this->autoClearScreen) 
		{
			SDL_RenderClear(this->renderer);
		}
		return false;
	}
	if(this->event.type == SDL_MOUSEMOTION)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Motion"<<endl;
		}
		this->click = false;
		SDL_GetMouseState(&this->cursor.x, &this->cursor.y);//This way, improve many buttons on screen
	}
	else if(this->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Button Down"<<endl;
		}
		this->mouseButtonDown = true;
		this->click = true;
	}
	else if(this->event.type == SDL_MOUSEBUTTONUP)
	{
		if(this->showLogs)
		{
			cout<<"Event: Mouse Button Up"<<endl;
		}
		this->mouseButtonDown = false;
		this->click = false;
	}
	if(this->autoClearScreen)
	{
		SDL_RenderClear(this->renderer);
	}
	return true;
}

bool Window::getCursorPosition(int *x, int *y)
{
	if(this->window == NULL) 
	{
		return false;
	}
	*x = this->cursor.x;
	*y = this->cursor.y;
	return true;
}


bool Window::getMouseButtonDown()
{
	return this->mouseButtonDown;
}

bool Window::getMouseButtonUp()
{
	return !this->mouseButtonDown;
}

bool Window::getMouseClick()
{
	if(this->mouseButtonDown && this->click)
	{
		this->click = true;
		return true;
	}
	return false;
}

bool Window::getMouseRelease()
{
	return !this->mouseButtonDown;
}

bool Window::getKeyDown()
{
	if(this->event.type == SDL_KEYDOWN) return true;
	return false;
}

bool Window::getKeyUp()
{
	if(this->event.type == SDL_KEYUP) return true;
	return false;
}

SDL_Keycode Window::getKey() { return this->event.key.keysym.sym; }

bool Window::getExit(){ if(this->event.type == SDL_QUIT){ return true;} return false; }
bool Window::getClose() { return this->getExit(); }

SDL_Window* Window::getWindow()
{
	return this->window;
}

SDL_Event Window::getRawEvent()
{
	return this->event;
}

