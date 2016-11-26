#include<iostream>
#include"Retangulo.hpp"
using namespace std;

int main()
{
	cout<<"Entrou na main"<<endl;
	Retangulo ret1;
	Retangulo ret2(10,10);
	Retangulo ret3;
	ret3.setWidth(20);
	ret3.setHeight(20);
	cout<<"Retangulo 1 "<<ret1.toString()<<endl;
	cout<<"Retangulo 2 "<<ret2.toString()<<endl;
	cout<<"Retangulo 3 "<<ret3.toString()<<endl;
	return 0;
}
