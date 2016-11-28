#include"Includes.hpp"

int main( int argc, char* argv[] )
{
	bool close;
	Screen tela("Tela de Teste", 600, 400);
//	tela.setVisible(true);
	tela.setDrawColor({255,255,255,0});
//	tela.setLogs(true);


	Image testImage;
	testImage.setScreen(&tela);
	testImage.loadImage("img/background.png");
	testImage.setPosition(0,0);
	testImage.setSize(tela.getWidth(), tela.getHeight());

	Button btSair;
	btSair.setScreen(&tela);
	btSair.setText("Sair");
	btSair.setPosition(400,300);




	Animation animacao;
	animacao.setLogs(true);
	animacao.setJumpPauseSprite(true);
	animacao.setScreen(&tela);
	animacao.loadSpriteSheet("img/spritesheet.png",4,4);
	animacao.setLineFixed(true);
	animacao.setPauseSprite(2);
	animacao.setUp((short int)4);
	animacao.setDown((short int)1);
	animacao.setUp(false);
	animacao.setDown(true);
	animacao.run();
	//animacao.pause();







	int i=tela.getWidth(), j=tela.getHeight();
	bool aumentando = true;

	while(!close)
	{
		while(tela.getEvent())
		{
			close = tela.getExit();
			if(!close)
			{
				close=btSair.listener();
			}
		}

		testImage.print();
		animacao.print();
		btSair.print();
		tela.update();
	}

	return 0;
}
