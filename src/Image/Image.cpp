#include"Image.hpp"

//Constructors
Image::Image()
{
	IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
	this->setDefaultValues();
}

Image::Image(string path)
{
	IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
	this->setDefaultValues();
	this->path = path;
}

//Destructor
Image::~Image()
{
	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	if(this->screen != NULL)
	{
		this->screen = NULL;
	}
}



//Getters
void Image::getImageDimensions(SDL_Surface* surface)
{
	this->position.w = surface->w;
	this->position.h = surface->h;
	this->resized.w = surface->w;
	this->resized.h = surface->h;
	this->crop.w = surface->w;
	this->crop.h = surface->h;
}

int Image::getX() { return this->position.x; }
int Image::getY() { return this->position.y; }
int Image::getWidth() { return this->resized.w; }
int Image::getHeight() { return this->resized.h; }


//Setters

void Image::setDefaultValues()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.w = 0;
	this->position.h = 0;
	this->texture = NULL;
	this->path = "";
	this->screen = NULL;
	this->resized.x = 0;
	this->resized.y = 0;
	this->resized.w = 0;
	this->resized.h = 0;
	this->crop.x = 0;
	this->crop.y = 0;
	this->crop.w = 0;
	this->crop.h = 0;
}

void Image::setLogs(bool showLogs) { this->showLogs = showLogs; }
void Image::setPosition(int x, int y) 
{
	this->position.x = x;
	this->position.y = y; 
	this->resized.x=x; 
	this->resized.y=y;
//	this->crop.x = x;
//	this->crop.y = y;
}
void Image::setSize(int w, int h)
{
	this->resized.w = w;
	this->resized.h = h;
}
void Image::setCrop(int x, int y, int w, int h)
{
	this->crop.x = x;
	this->crop.y = y;
	this->crop.w = w;
	this->crop.h = h;
}
void Image::setScreen(Screen* screen) { this->screen = screen; }

//Loaders
bool Image::loadImage(string path)
{
	this->path = path;
	if(this->screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image loadImage(string path)"<<endl;
			cout<<"\tERROR: Failed to load image, screen not defined, aborting"<<endl;
		}
		return false;
	}
	if(this->path.empty())
	{
		if(this->showLogs)
		{
			cout<<"On: Image loadImage(string path)"<<endl;
			cout<<"\tERROR: Failed to load image, no valid path"<<endl;
		}
		return false;
	}
	SDL_Surface* standardSurface = NULL;
	SDL_Surface* optimizedSurface = NULL;
	standardSurface = IMG_Load(this->path.c_str());
	if(standardSurface == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image loadImage(string path)"<<endl;
			cout<<"\tERROR: Image can't be loaded, file not found, or internal error, aborting"<<endl;
		}
		return false;
	}
	optimizedSurface = SDL_ConvertSurface(standardSurface, SDL_GetWindowSurface(this->screen->getWindow())->format, 0);
	if(optimizedSurface == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image loadImage(string path)"<<endl;
			cout<<"\tWarning: Failed to optimize surface"<<endl;
		}
		this->getImageDimensions(standardSurface);
		if(this->texture != NULL)
		{
			SDL_DestroyTexture(this->texture);
			this->texture = NULL;
		}
		this->texture = SDL_CreateTextureFromSurface(this->screen->getRenderer(), standardSurface);
		if(this->texture == NULL)
		{
			if(this->showLogs)
			{
				cout<<"On: Image loadImage(string path)"<<endl;
				cout<<"\tERROR: Failed to create texture from standardSurface, aborting"<<endl;
			}
			SDL_FreeSurface(standardSurface);
			standardSurface = NULL;
			return false;
		}
	}

	this->getImageDimensions(optimizedSurface);
	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
	this->texture = SDL_CreateTextureFromSurface(this->screen->getRenderer(), optimizedSurface);
	if(this->texture == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image loadImage(string path)"<<endl;
			cout<<"\tERROR: Failed to create texture from optimizedSurface, aborting"<<endl;
		}
		SDL_FreeSurface(optimizedSurface);
		SDL_FreeSurface(standardSurface);
		standardSurface = NULL;
		optimizedSurface = NULL;
		return false;
	}
	return true;
}

//Commands
void Image::print()
{
	if(this->screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image print()"<<endl;
			cout<<"\tERROR: Screen to print, not defined yet, aborting"<<endl;
		}
		return;
	}
	if(this->texture == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Image print()"<<endl;
			cout<<"\tERROR: Image not loaded yet, aborting"<<endl;
		}
		return;
	}
	SDL_RenderCopy(this->screen->getRenderer(), this->texture, &this->crop, &this->resized);
}

void Image::toString()
{
	cout<<"Image:"<<endl;
	cout<<"\t X = "<<this->getX()<<endl;
	cout<<"\t Y = "<<this->getY()<<endl;
	cout<<"\t Width = "<<this->getWidth()<<endl;
	cout<<"\t Height = "<<this->getHeight()<<endl;
	cout<<"\t Crop X = "<<this->crop.x<<endl;
	cout<<"\t Crop Y = "<<this->crop.y<<endl;
	cout<<"\t Crop Width = "<<this->crop.w<<endl;
	cout<<"\t Crop Height = "<<this->crop.h<<endl;
}
