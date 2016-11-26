#include<iostream>
#include<string>
#include"Retangulo.hpp"


Retangulo::Retangulo()
{
	this->width = 0;
	this->height = 0;
}

Retangulo::Retangulo(int width, int height)
{
	this->width = width;
	this->height=height;
}

std::string Retangulo::toString()
{
	return "Retangulo: Wodth: "+ std::to_string(this->width) + "   Height: "+ std::to_string(this->height);
}

bool Retangulo::setWidth(int width)
{
	this->width = width;
	return true;
}

bool Retangulo::setHeight(int height)
{
	this->height = height;
	return true;
}
