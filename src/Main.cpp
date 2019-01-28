//This file is only to test this ... thing
#include <iostream>
#include "Window/Window.hpp"
#include "Image/Image.hpp"
#include "Text/Text.hpp"
#include "Button/Button.hpp"
#include "TextBox/TextBox.hpp"
#include "Controller/RectangleController.hpp"

#include "./Map.hpp"

using namespace std;

void startGame(Window *window);

int maximumPlayerY = 150;
int playerSpeed=0;
bool updatingPlayerSpeed = false;

int main()
{
	bool close = false;

	Window tela("Jump the thing", 800, 600);
	tela.setFPSLimit(30);
	tela.setResizable(false);

	tela.setDrawColor({33,33,33,255});

	Image image = Image("img/start-background.jpg");
	image.setSize(800,600);
	image.load(&tela);


	Text txtLogo = Text();
	txtLogo.setWindow(&tela);
	txtLogo.setFontSize(40);
	txtLogo.setColor({255,255,255});
	txtLogo.setText("This is a simple JUMP the OBSTACLE game");
	txtLogo.update();
	txtLogo.setPosition((tela.getWidth()-txtLogo.getWidth())/2, 200);

	Button btSair = Button();
	btSair.setWindow(&tela);
	btSair.setText("Exit");
	btSair.setPosition(tela.getWidth()-btSair.getWidth()-100, tela.getHeight()-(btSair.getHeight()+210));

	Button btComando = Button();
	btComando.setWindow(&tela);
	btComando.setText("Play !");
	btComando.setPosition(100 , tela.getHeight() - (btComando.getHeight() + 210));

	TextBox tbPlayerName = TextBox();
	tbPlayerName.setSize(500,50);
	tbPlayerName.setPosition((tela.getWidth() - btComando.getWidth())/2, 200);
	tbPlayerName.setColor(244,244,244);
	tbPlayerName.setTextColor(3,3,3);

	while(!close)
	{
		while(tela.getEvent())
		{
			if(tela.getClose())
			{
				close = true;
				break;
			}
			if( tela.getKeyDown() )
			{
				if( tela.getKey() == SDLK_ESCAPE )
				{
					close = true;
				}
				else if(tela.getKey() == SDLK_RETURN)
				{
					cout<<"Play Button Pressed"<<endl;
					startGame(&tela);
					tela.setAutoClear(true);
					tela.setDrawColor({33,33,33,255});
				}
			}
			if(btSair.listener())
			{
				close = true;
				break;
			}

			tbPlayerName.listener(&tela);

			if( btComando.listener() )
			{
				cout<<"Play Button Pressed"<<endl;
				startGame(&tela);
				tela.setDrawColor({33,33,33,255});
				tela.setFPSLimit(30);
			}
		}
		//Background
		image.print(&tela);

		btComando.print();
		btSair.print();
		txtLogo.print();

		tela.update();
	}
	
	Window::finalize();
	return 0;
}


void jumpMotion(Image *player)
{
	if(player == NULL)
	{
		return;
	}
	else
	{
		playerSpeed -=20;
		bool updateSpeed = false;
		do
		{
			player->setPosition(player->getX(), player->getY()+playerSpeed);
			cout<<"SPEED == "<<playerSpeed<<endl;
			if(!updatingPlayerSpeed || updateSpeed)
			{
				updatingPlayerSpeed = true;
				updateSpeed = true;
				playerSpeed+= 2;
			}
			SDL_Delay(30);
		}while(player->getY() < maximumPlayerY);
		player->setPosition(player->getX(), maximumPlayerY);
		updateSpeed = false;
		updatingPlayerSpeed = false;
		playerSpeed = 0;
		cout<<"End of jump motion"<<endl;
	}
}


void startGame(Window *window)
{
	if( window == NULL )
	{
		cout<<"ERROR: Window received is NULL"<<endl;
		return;
	}
	window->setAutoClear(false);
	window->setFPSLimit(30);// 30 FPS
	window->setDrawColor({255,255,255,255});

	Image background = Image("img/background.png");
	background.setSize(800,600);
	background.load(window);


	Image player = Image("img/player.png");
	player.load(window);
	player.setPosition(50,150);
	player.setSize(50,100);

	Map map = Map();
	map.setSpeed(7);

	Button btReturn = Button();
	btReturn.setWindow(window);
	btReturn.setText("Go Back!");
	btReturn.setPosition(0,500);

	Rectangle floor = Rectangle(window->getWidth(), 10);
	floor.setColor({100,100,100,255});
	floor.setPosition(0, player.getY()+player.getHeight()-5);

	bool close = false;
	bool lose = false;

	while(!(close || lose))
	{
		while(window->getEvent())
		{
			// cout<<"2";
			if(window->getExit())
			{
				cout<<"Exiting"<<endl;
				exit(0);
			}
			// testPlayer.listener();
			if(btReturn.listener())
			{
				cout<<"Returning to main window"<<endl;
				return;
			}
			if(window->getKeyDown())
			{
				cout<<"Key pressed"<<endl;
				if(window->getKey() == SDLK_SPACE)
				{
					cout<<"SPACE PRESSED"<<endl;
					thread t(jumpMotion, &player);
					t.detach();
				}
				else if(window->getKey() == SDLK_ESCAPE)
				{
					cout<<"Returning to main window (escape)"<<endl;
					return;
				}
				// else if(window->getKey() == SDLK_RIGHT)
				// {
				// 	cout<<"Updating MAP"<<endl;
				// 	map.update(window);
				// }
			}
		}
		window->clear();
		background.print();
		floor.printFilled(window);
		player.print(window);
		btReturn.print();
		map.print(window);
		map.update(window);
		

		window->update();

		if( map.collided(&player) )
		{
			cout<<"COLIDIU COM O MAPA";
			lose = true;
			Window::wait(3000);
			// return;
		}
	}

	return;
}


