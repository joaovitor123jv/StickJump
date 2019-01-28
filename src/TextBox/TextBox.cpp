#include "TextBox.hpp"

bool textInputEnabled = false;

//Constructors
TextBox::TextBox()
{
	this->setDefaultValues();
}

TextBox::TextBox(string path)//Create a TextBox with a predefined font
{
	this->setDefaultValues();
	this->text.setFont(path);
}

TextBox::TextBox(string path, int fontSize)//Create a TextBox with a defined font, with the size of this font defined
{
	this->setDefaultValues();
	this->text.setFont(path, fontSize);
}

TextBox::TextBox(int width, int height)//Create a TexBox with width and height limits defined
{
	this->setDefaultValues();
	this->rectangle.setSize(width, height);
	this->text.setFontSize(height-5);
}

//Destructor
TextBox::~TextBox()
{
	//Do nothing(All automatized already)
}

//Getters
void TextBox::getSize(int* width, int* height) {this->rectangle.getSize(width, height); }
void TextBox::getPosition(int* x, int* y) {this->rectangle.getPosition(x, y); }

int TextBox::getWidth() {return this->rectangle.getWidth(); }
int TextBox::getHeight() {return this->rectangle.getHeight(); }
int TextBox::getX() {return this->rectangle.getX(); }
int TextBox::getY() {return this->rectangle.getY(); }

bool TextBox::getVisible() { return this->rectangle.getVisible(); }

string TextBox::getText() {return this->text.getText(); }





//Setters

void TextBox::setShowLogs(bool showLogs)
{
	this->showLogs = showLogs;
}

void TextBox::setLogs(bool showLogs)
{
	this->showLogs = showLogs;
}

void TextBox::setDefaultValues()
{
	this->rectangle = Rectangle();
	this->text = Text();
	this->inputText = "";
	this->showLogs = false;
	this->editingText = false;
	this->textEdited = false;
	this->setVisible(true);
}


void TextBox::setTextColor(int r, int g, int b)
{
	if(r > 255 || g>255 || b>255)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->setTextColor(int r, int g, int b)"<<endl;
			cout<<"\tERROR: arguments must be behind 0 and 255 inclusive"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;
	}
	this->text.setColor({ (Uint8)r , (Uint8)g , (Uint8)b });
}

void TextBox::setTextColor(SDL_Color color)
{
	this->text.setColor(color);
}

void TextBox::setColor(int r, int g, int b)
{
	if(r > 255 || g>255 || b>255)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->setColor(int r, int g, int b)"<<endl;
			cout<<"\tERROR: arguments must be behind 0 and 255 inclusive"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;
	}
	this->rectangle.setColor(r, g, b);
}

void TextBox::setColor(SDL_Color color)
{
	this->rectangle.setColor(color);
}


void TextBox::setSize(int width, int height)
{
	if(width < 0 || height <0)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->setSize(int width, int height)"<<endl;
			cout<<"\tERROR: Width and Height, must greater than 0 (zero)"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;
	}
	this->rectangle.setSize(width, height);
	this->text.setFontSize(height-5);
}

void TextBox::setWidth(int width)
{
	if(width < 0)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->setWidth(int width)"<<endl;
			cout<<"\tERROR: Width , must greater than 0 (zero)"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;	
	}
	this->rectangle.setWidth(width);
}


void TextBox::setHeight(int height)
{
	if(height < 0)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->setHeight(int height)"<<endl;
			cout<<"\tERROR: Height , must greater than 0 (zero)"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;	
	}
	this->rectangle.setHeight(height);
	if(height <=5)
	{
		this->text.setFontSize(height);
	}
	else
	{
		this->text.setFontSize(height - 5);
	}
}

void TextBox::setPosition(int x, int y)
{
	this->rectangle.setPosition(x, y);
	this->text.setPosition(x, y);
}

void TextBox::setX(int x)
{
	this->rectangle.setX(x);
	this->text.setX(x);
}

void TextBox::setY(int y)
{
	this->rectangle.setY(y);
	this->text.setY(y);
}

void TextBox::setEnterAsCommand(bool x) 
{
	this->enterEnabledAsCommand = x;
}

void TextBox::setVisible(bool option)
{
	this->rectangle.setVisible(option);
	this->text.setVisible(option);
	this->visible = option;
}


//Commands
void TextBox::print(Window* window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"At: TextBox->print(Window* window)"<<endl;
			cout<<"\tERROR: window == NULL"<<endl;
			cout<<"\t\tAborting"<<endl;
		}
		return;
	}
	if( !this->getVisible() )
	{
		return;
	}
	if(this->text.getWindowDefined())
	{
		this->rectangle.printFilled(window);
		this->text.print();	
	}
	else
	{
		this->text.setWindow(window);
	}
}




bool TextBox::listener(Window* window)
{
	if(window == NULL)
	{
		if(this->showLogs)
		{
			cout<<"ERROR: At TextBox.listener(Window*)"<<endl;
			cout<<"\tWindow* == NULL, aborting"<<endl;
		}
		return false;
	}
	if( !this->visible )
	{
		return false;
	}

	if(window->getMouseClick())
	{
		if(this->rectangle.getCursorInside(window))
		{
			this->editingText = true;
			// return true;
		}	
		else
		{
			if(textInputEnabled)
			{
				//SDL_StopTextInput();// POSSIBLE ERROR HERE
				// cout<<"SDL_StopTextInput"<<endl;
			}
			textInputEnabled = false;
			this->editingText =  false;
			return false;
		}
	}

	//Special Characters
	if(this->editingText)  // AQUI TÁ OK
	{
		textInputEnabled = true;

		if(window->getKeyDown())
		{
			if(window->getKey() == SDLK_BACKSPACE && this->inputText.length() > 0)
			{
				this->inputText.pop_back();
				this->textEdited = true;
				if(this->showLogs)
				{
					cout<<"At: TextBox ->  Backspace identified"<<endl;
				}
			}
			else
			{
				if(window->getKey() == SDLK_RETURN)
				{
					if(this->showLogs)
					{
						cout<<"At: TextBox ->  Return Identified"<<endl;
					}
					if(this->enterEnabledAsCommand)
					{
						return true;
					}
					return false;
				}
			}
		}
		else
		{
			if(window->getRawEvent().type == SDL_TEXTINPUT)
			{
				if(this->showLogs)
				{
					cout<<"At: TextBox ->  TextInput Identified"<<endl;
				}
				if(!(SDL_GetModState() & KMOD_CTRL))
				{
					this->inputText += window->getRawEvent().text.text;
					this->textEdited = true;
				}
			}
		}


		if(this->textEdited)
		{
			if(this->showLogs)
			{
				cout<<"At: TextBox ->  Updating Text"<<endl;
			}

			if(!this->text.getWindowDefined())
			{			
				this->text.setWindow(window);
			}
			if(this->inputText != "")
			{
				this->text.setText(this->inputText);
				this->text.update();	
			}
			else
			{
				this->text.setText(" ");
				this->text.update();
			}
			this->textEdited = false;
		}
	}
	return false;
}
