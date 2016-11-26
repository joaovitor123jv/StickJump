#include<iostream>
#include<string>

class Retangulo
{
	int width;
	int height;
public:
//Construtores
	Retangulo();
	Retangulo(int width, int height);

	//Setters
	bool setWidth(int width);
	bool setHeight(int height);

	//Comandos
	std::string toString();
	
};
