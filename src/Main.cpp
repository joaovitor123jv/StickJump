#include"Includes.hpp"

int main( int argc, char* argv[] )
{
	bool close;
	Screen tela("Tela de Teste", 600, 400);
//	tela.setVisible(true);
	tela.setDrawColor({255,255,255,255});
	tela.setLogs(true);
	while(!close)
	{
		while(tela.getEvent())
		{
			close = tela.getExit();
		}
		tela.update();
	}

//	~tela;
	return 0;
}
