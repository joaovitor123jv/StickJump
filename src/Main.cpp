#include"Includes.hpp"

int main( int argc, char* argv[] )
{
	bool close;
	Screen tela("Tela de Teste", 600, 400);
//	tela.setVisible(true);
	tela.setDrawColor({255,255,255,255});
//	tela.setLogs(true);
	Uint8 r=100, g=25, b=255, a=255;

	Rectangle ret1;
	ret1.setColor({r,g,b,a});
	ret1.setSize(300, 100);
	ret1.setPosition(100,100);


	Button botao;
	botao.setLogs(true);
	botao.setScreen(&tela);
	botao.setText("Texto de teste");
	botao.setPosition(200,200);


	Text texto;
	texto.setLogs(true);
	texto.setScreen(&tela);
	//texto.setPosition(0,0);
	texto.setFont("font/test.ttf", 30);
	texto.setText("Qualquer coisa, é só um teste");
	texto.setColor({255,255,255,255});

	while(!close)
	{
		while(tela.getEvent())
		{
			close = tela.getExit();
			r++;
			if(r > 255) r=0;
			g++;
			if(g > 255) g=0;
			b++;
			if(b > 255) b=0;
			ret1.setColor({ r,g,b,a });
			botao.listener();
		}
		texto.print();
		ret1.printFilled(&tela);
		botao.print();
		tela.update();
	}

	return 0;
}
