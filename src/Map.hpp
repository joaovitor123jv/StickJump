#include "Rectangle/Rectangle.hpp"
#include <random>
#include <thread>

class Map
{
public:
	Rectangle obstacles[10];
	int speed;

	Map()
	{
		int i;
		int height;
		int px=0;
		this->speed = 2;
		for(i=0; i<10; i++)
		{
			height = (random()%40) + 15;
			obstacles[i] = Rectangle(10, height);
			px = (random() % 400)+px+100;

			obstacles[i].setColor({255,0,255,255});
			obstacles[i].setPosition(px+400, 250 - height);
			cout<<"Obstacle "<<i<<" In position ("<<obstacles[i].getX()<<","<<obstacles[i].getY()<<")"<<endl;
		}
	}

	bool collided(Image *player)
	{
		int i;
		for(i=0;i<10; i++)
		{
			if(obstacles[i].getX()>50)
			{
				if(player->getX()+player->getWidth()-5 >= obstacles[i].getX())
				{
					if(player->getY()+player->getHeight()-5 >= obstacles[i].getY())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	void setSpeed(int x) { this->speed = x; }

	void update(Window *window)
	{
		int i,j;
		Rectangle aux;
		for(i=0; i<10; i++)
		{
			obstacles[i].setPosition(obstacles[i].getX()-this->speed, obstacles[i].getY());
			if(obstacles[0].getX() < -10)
			{
				aux = obstacles[i];
				for(j=0;j<9;j++)
				{
					obstacles[j] = obstacles[j+1];
				}
				obstacles[9] = aux;
				obstacles[9].setPosition(900,obstacles[9].getY());
				i-=1;
			}
			
		}
	}

	void print(Window *window)
	{
		int i;
		for(i=0; i<10; i++)
		{
			obstacles[i].printFilled(window);
		}
	}
};
