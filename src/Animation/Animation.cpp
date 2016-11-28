#include"Animation.hpp"

//Constructors
Animation::Animation()
{
	this->setDefaultValues();
}

Animation::Animation(int lines, int columns)
{
	this->setDefaultValues();
	if(lines >=1 && columns >=1)
	{
		this->lines = lines;
		this->columns = columns;
	}
	else
	{
		cout<<"On: Animation Constructor (int lines, int columns)"<<endl;
		cout<<"\tERROR: Lines and columns must be greater than 0 (1 or more)"<<endl;
		return;
	}
}

Animation::Animation(string path, int lines, int columns)
{
	this->setDefaultValues();
	if(lines >=1 && columns >=1)
	{
		this->lines = lines;
		this->columns = columns;
	}
	else
	{
		cout<<"On: Animation Constructor (string path, int lines, int columns)"<<endl;
		cout<<"\tERROR: Lines and columns must be greater than 0 (1 or more)"<<endl;
		return;
	}
	this->image.setLogs(true);
	if(!this->image.loadImage(path))
	{
		cout<<"On: Animation Constructor (string path, int lines, int columns)"<<endl;
		cout<<"\tERROR: Failed to loadImage"<<endl;
		return;
	}
	this->image.setLogs(false);
}

//Destructors
Animation::~Animation()
{
	int retorno;
	if(this->running)
	{
		this->running = false;
	}
	if(this->showLogs)
	{
		cout<<"Waitint to finish thread"<<endl;	
	}
	SDL_WaitThread(this->spriteChange, &retorno);
	if(retorno == 0)
	{
		if(this->showLogs)
		{
			cout<<"Animation Destructed successfull"<<endl;
		}
	}
	else
	{
		cout<<"ERROR: Failed to destruct the spriteChange Thread (Animation)"<<endl;
	}
}

//Getters
bool Animation::getRunning(){return this->running;}
bool Animation::getShowLogs(){return this->showLogs;}
bool Animation::getPaused(){return this->paused;}
bool Animation::getSpriteSheet(){return this->spriteSheet;}
bool Animation::getLineFixed(){return this->lineFixed;}
bool Animation::getJumpPauseSprite(){return this->jumpPauseSprite;}
int Animation::getLines(){return this->lines;}
int Animation::getColumns(){return this->columns;}
int Animation::getPauseSprite(){return this->pauseSprite;}
short int Animation::getUp(){return this->up;}
short int Animation::getDown(){return this->down;}
short int Animation::getRight(){return this->right;}
short int Animation::getLeft(){return this->left;}
Image *Animation::getImage(){return &this->image;}

//Setters
void Animation::setPosition(int x, int y){this->image.setPosition(x, y);}
void Animation::setX(int x){this->image.setPosition(x, this->image.getY());}
void Animation::setY(int y){this->image.setPosition(this->image.getX(),(y));}
void Animation::setJumpPauseSprite(bool jumpPauseSprite){this->jumpPauseSprite = jumpPauseSprite;}
void Animation::setUp(short int up)
{
	if(up < 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setUp(short int up)"<<endl;
			cout<<"\tERROR: Argument must be positive, aborting"<<endl;
		}
		return;
	}
	this->up = up;
}
void Animation::setUp(bool up)
{
	if(up)
	{
		if(this->up > 0)
		{
			return;
		}
		this->up = this->up*-1;
	}
	else
	{
		if(this->up < 0)
		{
			return;
		}
		this->up = this->up*-1;	
	}
}
void Animation::setDown(short int down)
{
	if(down < 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setDown(short int down)"<<endl;
			cout<<"\tERROR: Argument must be positive, aborting"<<endl;
		}
		return;
	}
	this->down = down;
}
void Animation::setDown(bool down)
{
	if(down)
	{
		if(this->down > 0)
		{
			return;
		}
		this->down = this->down*-1;
	}
	else
	{
		if(this->down < 0)
		{
			return;
		}
		this->down = this->down*-1;	
	}
}

void Animation::setLeft(short int left)
{
if(left < 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setLeft(short int left)"<<endl;
			cout<<"\tERROR: Argument must be positive, aborting"<<endl;
		}
		return;
	}
	this->left = left;
}
void Animation::setLeft(bool left)
{
	if(left)
	{
		if(this->left > 0)
		{
			return;
		}
		this->left = this->left*-1;
	}
	else
	{
		if(this->left < 0)
		{
			return;
		}
		this->left = this->left*-1;	
	}
}
void Animation::setRight(short int right)
{
if(right < 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setUp(short int right)"<<endl;
			cout<<"\tERROR: Argument must be positive, aborting"<<endl;
		}
		return;
	}
	this->right = right;
}
void Animation::setRight(bool right)
{
	if(right)
	{
		if(this->right > 0)
		{
			return;
		}
		this->right = this->right*-1;
	}
	else
	{
		if(this->right < 0)
		{
			return;
		}
		this->right = this->right*-1;	
	}
}
void Animation::setLineFixed(bool lineFixed) { this->lineFixed = lineFixed; }
void Animation::setScreen(Screen* screen)
{
	if(screen == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Animatio setScreen(Screen*)"<<endl;
			cout<<"\tERROR: Screen* == NULL, aborting "<<endl;
		}
		return;
	}
	this->image.setScreen(screen);
}

void Animation::setDefaultValues()
{
	this->lines = 0;
	this->columns = 0;
	this->image.setLogs(false);
	this->image.setSize(0,0);
	this->spriteSheet = true;
	this->lineFixed = true;
	this->pauseSprite = 2;
	this->running = false;
	this->spriteChange = NULL;//PAY ATTEMPTION HERE
	this->showLogs = false;
}

void Animation::setPauseSprite(int pauseSprite) 
{
	if(pauseSprite <= 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setPauseSprite(int pauseSprite)"<<endl;
			cout<<"\tERROR: the pauseSprite number must be greater than 0 (1 or more), aborting"<<endl;
		}
		return;
	}
	this->pauseSprite = pauseSprite;
}

void Animation::setLogs(bool showLogs) { this->showLogs = showLogs; this->image.setLogs(showLogs); }
void Animation::setMultipleImages(bool spriteSheet) { if(!spriteSheet)cout<<"Warning: No support for multiple images yet, please use a spritesheet"<<endl; this->spriteSheet = !spriteSheet; }

void Animation::setSpriteMatrix(int lines, int columns)
{
	if(lines <= 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setSpriteMatrix(int lines, int columns)"<<endl;
			cout<<"\tERROR: Lines number, must be greater than 0  (at least 1), aborting"<<endl;
		}
		return;
	}
	if(columns <= 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation setSpriteMatrix(int lines, int columns)"<<endl;
			cout<<"\tERROR: Columns number, must be greater than 0  (at least 1), aborting"<<endl;
		}
		return; 
	}
	this->lines = lines;
	this->columns = columns;
	return;
}

//Loaders
bool Animation::loadSpriteSheet(string path, int lines, int columns)
{
	if(lines <= 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path, int lines, int columns)"<<endl;
			cout<<"\tERROR: The number of Lines, must be 1, or higher, aborting"<<endl;
		}
		return false;
	}
	if(columns <= 0)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path, int lines, int columns)"<<endl;
			cout<<"\tERROR: The number of Columns, must be 1, or higher, aborting"<<endl;
		}
		return false;
	}
	if(!this->spriteSheet)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path, int x, int y)"<<endl;
			cout<<"\tERROR: Animation configured to use multiple images(not spritesheet), aborting"<<endl;
		}
		return false;
	}
	this->columns = columns;
	this->lines = lines;
	if(!this->image.loadImage(path))
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path, int lines, int columns)"<<endl;
			cout<<"\tWarning: The Screen to print images isn't setted yet"<<endl;
			cout<<"\tSetting variables only"<<endl;
		}
	}
	return true;
}

bool Animation::loadSpriteSheet(string path)
{
	if(!this->spriteSheet)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path)"<<endl;
			cout<<"\tERROR: Animation configured to use multiple images(not spritesheet), aborting"<<endl;
		}
		return false;
	}
	if(!this->image.loadImage(path))
	{
		if(this->showLogs)
		{
			cout<<"On: Animation loadSpriteSheet(string path)"<<endl;
			cout<<"\tWarning: The Screen to print images isn't setted yet"<<endl;
			cout<<"\tSetting variables only"<<endl;
		}
	}
	return true;
}

//Commands
SDL_ThreadFunction changeSprites(void *ptr)//Working  Criar uma forma de ele poder usar This
{
	Animation *animation=(Animation*)ptr;
	if(animation == NULL)
	{
		cout<<"On: Animation changeSprites(void*)"<<endl;
		cout<<"\tERROR: Unable to get Animation stats (void*) == NULL"<<endl;
		cout<<"\tAborting"<<endl;
		return (SDL_ThreadFunction)1;
	}
	Image *image=animation->getImage();

	if(image == NULL)
	{
		if(animation->getShowLogs())
		{
			cout<<"On: Animation changeSprites(void *ptr)"<<endl;
			cout<<"\tERROR: Couldn't get image stats, aborting"<<endl;
		}
		return (SDL_ThreadFunction)1;
	}
	int width = image->getWidth()/animation->getColumns();//The 1 block width size
	int height = image->getHeight()/animation->getLines();//The 1 block height size
	int max=0;
	if(animation->getLineFixed())
	{
		if(animation->getShowLogs())
		{
			cout<<"On: Animation changeSprites()"<<endl;
			cout<<"\tLine fixed, this will change columns"<<endl;
		}
		while(animation->getRunning())
		{

			if(animation->getPaused())
			{
				if(animation->getShowLogs()){cout<<"On: Animation changeSprites()"<<endl; cout<<"\tAnimation paused"<<endl;}
				if(animation->getUp() > 0 )
				{
					image->setCrop(width*(animation->getPauseSprite()-1), height*(animation->getUp()-1), width, height);
				}
				if(animation->getDown() > 0)
				{
					image->setCrop(width*(animation->getPauseSprite()-1), height*(animation->getDown()-1), width, height);
				}
				if(animation->getLeft() > 0)
				{
					image->setCrop(width*(animation->getPauseSprite()-1), height*(animation->getLeft()-1), width, height);
				}
				if(animation->getRight() > 0)
				{
					image->setCrop(width*(animation->getPauseSprite()-1), height*(animation->getRight()-1), width, height);
				}
			}
			else
			{
				if(animation->getShowLogs()){cout<<"On: Animation changeSprites()"<<endl;cout<<"\tAnimation Running"<<endl;}
				SDL_Delay(500);
				max++;
				if(max == animation->getColumns())
				{
					max = 0;
				}
				if(!animation->getJumpPauseSprite())
				{
					if(max == (animation->getPauseSprite()))
					{
						max++;
						if(max == animation->getColumns())
						{
							max = 0;
						}
					}
				}
				if(animation->getUp() > 0)
				{		
					image->setCrop(width*max, height*(animation->getUp()-1), width, height);
				}
				if(animation->getDown() > 0)
				{
					cout<<"TESTE"<<endl;
					image->setCrop(width*max, height*(animation->getDown()-1), width, height);
				}
				if(animation->getLeft() > 0)
				{
					image->setCrop(width*max, height*(animation->getLeft()-1), width, height);
				}
				if(animation->getRight() > 0)
				{
					image->setCrop(width*max, height*(animation->getRight()-1), width, height);
				}
			}
		}
	}
	else
	{
		while(animation->getRunning())
		{
			if(animation->getShowLogs())
			{
				cout<<"Thread Running"<<endl;
			}
			if(animation->getPaused())
			{
				if(animation->getShowLogs()){cout<<"On: Animation changeSprites()"<<endl; cout<<"\tAnimation paused"<<endl;}
				if(animation->getUp() > 0)
				{
					image->setCrop(width*(animation->getUp()-1), height*(animation->getPauseSprite()-1), width, height);
				}
				else if(animation->getDown() > 0)
				{
					image->setCrop(width*(animation->getDown()-1), height*(animation->getPauseSprite()-1), width, height);
				}
				else if(animation->getLeft() > 0)
				{
					image->setCrop(width*(animation->getLeft()-1), height*(animation->getPauseSprite()-1), width, height);
				}
				else if(animation->getRight() > 0)
				{
					image->setCrop(width*(animation->getRight()-1), height*(animation->getPauseSprite()-1), width, height);
				}
			}
			else
			{
				if(animation->getShowLogs()){cout<<"On: Animation changeSprites()"<<endl;cout<<"\tAnimation Running"<<endl;}
				//TODO

				SDL_Delay(500);
				

				max++;
				if(max == animation->getLines())
				{
					max = 0;
				}
				if(!animation->getJumpPauseSprite())
				{
					if(max == (animation->getPauseSprite()))
					{
						max++;
						if(max == animation->getLines())
						{
							max = 0;
						}
					}
				}



				if(animation->getUp() > 0)
				{		
					image->setCrop(width*(animation->getUp()-1), height*max, width, height);
				}
				if(animation->getDown() > 0)
				{
					image->setCrop(width*(animation->getDown()-1), height*max, width, height);
				}
				if(animation->getLeft() > 0)
				{
					image->setCrop(width*(animation->getLeft()-1), height*max, width, height);
				}
				if(animation->getRight() > 0)
				{
					image->setCrop(width*(animation->getRight()-1), height*max, width, height);
				}
			}
		}
	}
	
	return 0;
}


void Animation::pause() { this->paused = true; }
void Animation::run() 
{ 
	if(this->spriteChange == NULL)
	{
		if(this->showLogs)
		{
			cout<<"On: Animation run()"<<endl;
			cout<<"\tCreating Sprite change Thread"<<endl;
		}
		this->running = true;
		this->spriteChange = SDL_CreateThread((SDL_ThreadFunction)changeSprites, "SpriteChange", (void*)this);
		if(this->spriteChange == NULL)
		{
			if(this->showLogs)
			{
				cout<<"On: Animation run()"<<endl;
				cout<<"\tERROR: Failed to creat Thread"<<endl;
			}
			this->running = false;
			return;
		}
		else
		{
			if(this->showLogs)
			{
				cout<<"On: Animation run()"<<endl;
				cout<<"\tThread Created with success"<<endl;
			}
		}
	}
	this->paused = false; 
}

void Animation::print()
{
	// if(this->image == NULL)
	// {
	// 	if(this->showLogs)
	// 	{
	// 		cout<<"On: Animation print"<<endl;
	// 		cout<<"\tERROR: Sprites (image) not loaded yet, aborting"<<endl;
	// 	}
	// 	return;
	// }
	this->image.print();
}