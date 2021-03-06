#include "Text.hpp"

string Text::defaultFontPath = "./font/default.ttf";

//Constructors
Text::Text()
{
	if(TTF_Init() == -1)
	{
		cout<<"On: Text Constructor"<<endl;
		cout<<"\tFailed to init TTF support, aborting"<<endl;
		return;
	}
	this->setDefaultValues();
}


Text::Text(string path)
{
	if(TTF_Init() == -1)
	{
		cout<<"On: Text Constructor"<<endl;
		cout<<"\tFailed to init TTF support, aborting"<<endl;
		return;
	}
	this->setDefaultValues();
	this->path = path;
}

//Destructor
Text::~Text()
{
	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
	}
	if(this->font != NULL)
	{
		TTF_CloseFont(this->font);
	}
}

//Getters
//int Text::getMaxSize() { return this->maxSize; }
string Text::getText() { return this->text; }
int Text::getX() { return this->position.x; }
int Text::getY() { return this->position.y; }
int Text::getWidth() { return this->position.w; }
int Text::getHeight() { return this->position.h; }

void Text::getValuesFromSurface(SDL_Surface* surface)
{
	if(surface == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text getValuesFromSurface(SDL_Surface*)"<<endl;
			cout<<"\tINTERNAL ERROR: Please send a mail for the lib developer"<<endl;
		}
		return;
	}
	this->position.w = surface->w;
	this->position.h = surface->h;
	return;
}

bool Text::getWindowDefined()
{
	if(this->window == NULL)
	{
		return false;
	}
	return true;
}

//Setters
void Text::setDefaultValues()
{
	this->text = "Text";
	// this->path = "font/default.ttf";
	this->path = Text::defaultFontPath;
	this->color.r = 0;
	this->color.g = 0;
	this->color.b = 0;
	this->color.a = 0xFF;
//	this->maxSize=32;
	this->position.x = 0;
	this->position.y = 0;
	this->position.w = 0;
	this->position.h = 0;
	this->texture = NULL;
	this->font = NULL;
	this->fontSize = 32;
	this->window = NULL;
	this->showLogs = false;
	this->visible = true;
}

void Text::setDefaultFontPath(string path) { if(! path.empty()) Text::defaultFontPath = path; }

//void Text::setMaxSize(int maxSize) { this->maxSize = maxSize; }
void Text::setText(string text) 
{
	this->text = text;
	if(this->window != NULL) this->update();
}
void Text::setLogs(bool showLogs){ this->showLogs = showLogs; }
void Text::setColor(SDL_Color color) 
{ 
	this->color = color; 
	if(this->window != NULL) this->update();
}


void Text::setVisible(bool option)
{
	this->visible = option;
}

void Text::setFont(string path, int fontSize)
{
	if(this->font != NULL)
	{
		TTF_CloseFont(this->font);
	}
	this->font = TTF_OpenFont(path.c_str(), fontSize);
	if(this->font != NULL)
	{
		this->path = path;
		this->fontSize = fontSize;
		return;
	}
	if(this->showLogs)
	{
		cout<<"On: Text setFont(string path, int fontSize)"<<endl;
		cout<<"\tERROR: Couldn't load font"<<endl;
	}
	if(this->window != NULL) this->update();
	return;
}


void Text::setFont(string path)
{
	if(this->font != NULL)
	{
		TTF_CloseFont(this->font);
	}
	this->font = TTF_OpenFont(path.c_str(), this->fontSize);
	if(this->font != NULL)
	{
		this->path = path;
		return;
	}
	if(this->showLogs)
	{
		cout<<"On: Text setFont(string path)"<<endl;
		cout<<"\tERROR: Couldn't load font"<<endl;
	}
	if(this->window != NULL) this->update();
	return;
}


void Text::setFontSize(int fontSize)
{
	if(this->font != NULL)
	{
		TTF_CloseFont(this->font);
	}
	this->font = TTF_OpenFont(this->path.c_str(), fontSize);
	if(this->font != NULL)
	{
		this->fontSize = fontSize;
		return;
	}
	if(this->showLogs)
	{
		cout<<"On: Text setFontSize(int fontSize)"<<endl;
		cout<<"\tERROR: Couldn't load font"<<endl;
	}
	if(this->window != NULL) this->update();
	return;
}



void Text::setWindow(Window *window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text setWindow(Window*)"<<endl;
			cout<<"\tERROR: Window* == NULL\n, aborting"<<endl;
		}
		return;
	}
	this->window = window;
}

void Text::setPosition(int x, int y) { this->position.x = x; this->position.y = y; }
void Text::setX(int x) { this->position.x = x; }
void Text::setY(int y) { this->position.y = y; }

//Commands
void Text::update()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text update()"<<endl;
			cout<<"\tERROR: Window to render text isn't defined yet, aborting"<<endl;
		}
		return;
	}
	if(this->font == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text update()"<<endl;
			cout<<"\tERROR: Font to render text isn't specified yet, aborting"<<endl;
		}
		return;
	}
	SDL_Surface* surface;
	surface = TTF_RenderUTF8_Solid(this->font, this->text.c_str(), this->color);
	if(surface == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text update()"<<endl;
			cout<<"\tERROR: Failed to render text, aborting"<<endl;
		}
		return;
	}
	this->getValuesFromSurface(surface);

	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	this->texture = SDL_CreateTextureFromSurface(this->window->getRenderer(), surface);
	if(this->texture == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text update()"<<endl;
			cout<<"\t ERROR: Can't Create texture, aborting"<<endl;
		}
		SDL_FreeSurface(surface);
		surface = NULL;
		return;
	}
	SDL_QueryTexture(this->texture, NULL, NULL, &this->position.w, &this->position.h);
	SDL_FreeSurface(surface);
	surface = NULL;
	return;
}

void Text::print()
{
	if(this->window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Text print()"<<endl;
			cout<<"\tERROR: Window to print text not defined yet"<<endl;
		}
		return;
	}
	if( !this->visible )
	{
		return;
	}
	SDL_RenderCopy(this->window->getRenderer(), this->texture, NULL, &this->position);
	return;
}
